// Klatch - a DICT client for KDE
// Copyright © 2012 Frank S. Thomas <frank@timepit.eu>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "dict/DictClient.h"
#include <QAbstractSocket>
#include <QList>
#include <QMap>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QTcpSocket>
#include <QTextStream>
#include <QtDebug>
#include "dict/DatabaseInfo.h"
#include "dict/Definition.h"
#include "dict/Matches.h"
#include "dict/codes.h"
#include "utility/stream.h"
#include "utility/string.h"
#include "KlatchData.h"

DictClient::DictClient(QObject* parent)
  : DictClient{"localhost", defaultPort(), parent} {}

DictClient::DictClient(const QString &hostname, QObject *parent)
  : DictClient{hostname, defaultPort(), parent} {}

DictClient::DictClient(const QString& hostname, quint16 port,
                       QObject* parent) : QObject{parent} {
  hostname_ = hostname;
  port_ = port;

  stream_.setDevice(&socket_);
  stream_.setCodec("UTF-8");

  connect(&socket_, SIGNAL(readyRead()),
    this, SLOT(readData()));
  connect(&socket_, SIGNAL(error(QAbstractSocket::SocketError)),
    this, SLOT(handleError(QAbstractSocket::SocketError)));
  connect(&socket_, SIGNAL(disconnected()),
    this, SLOT(resetCache()));
}

QString DictClient::peerName() const {
  return hostname_;
}

void DictClient::setPeerName(const QString& name) {
  if (hostname_ != name) {
    hostname_ = name;
    socket_.disconnectFromHost();
  }
}

quint16 DictClient::peerPort() const {
  return port_;
}

void DictClient::setPeerPort(quint16 port) {
  if (port_ != port) {
    port_ = port;
    socket_.disconnectFromHost();
  }
}

quint16 DictClient::defaultPort() {
  return 2628;
}

int DictClient::maxLineLength() {
  return 1024 - 2;
}

QMap<QString, QString> DictClient::databases() const {
  return databases_;
}

QMap<QString, QString> DictClient::searchStrategies() const {
  return search_strategies_;
}

void DictClient::sendClient() {
  stream_ << "CLIENT " << KlatchData::displayNameSlashVersion() << crlf;
}

void DictClient::sendDefine(const QString& word, const QString& database) {
  const QString cmd = QString{"DEFINE \"%1\" \"%2\""}.arg(database, word);
  sendRawCommand(sanitizeCmd(cmd));
}

void DictClient::sendHelp() {
  sendRawCommand("HELP");
}

void DictClient::sendMatch(const QString& word, const QString& strategy,
                           const QString& database) {
  const QString cmd =
    QString{"MATCH \"%1\" \"%2\" \"%3\""}.arg(database, strategy, word);
  sendRawCommand(sanitizeCmd(cmd));
}

void DictClient::sendOptionMime() {
  sendRawCommand("OPTION MIME");
}

void DictClient::sendQuit() {
  stream_ << "QUIT" << crlf;
}

void DictClient::sendShowDatabases() {
  sendRawCommand("SHOW DB");
}

void DictClient::sendShowInfo(const QString& database) {
  const QString cmd = QString{"SHOW INFO \"%1\""}.arg(database);
  sendRawCommand(sanitizeCmd(cmd));
}

void DictClient::sendShowServer() {
  sendRawCommand("SHOW SERVER");
}

void DictClient::sendShowStrategies() {
  sendRawCommand("SHOW STRAT");
}

void DictClient::sendStatus() {
  sendRawCommand("STATUS");
}

void DictClient::connectIfDisconnected() {
  const QAbstractSocket::SocketState state = socket_.state();

  if (state == QAbstractSocket::UnconnectedState ||
      state == QAbstractSocket::ClosingState) {
    socket_.connectToHost(peerName(), peerPort());
    sendClient();
    sendShowDatabases();
    sendShowStrategies();
  }
}

void DictClient::sendRawCommand(const QString& command) {
  connectIfDisconnected();
  stream_ << command << crlf;
}

void DictClient::readData() {
  while (socket_.canReadLine()) {
    QString line = QString::fromUtf8(socket_.readLine());

    if (!awaiting_text_) {
      if (!readStatusLine(line)) {
        qWarning() << "Failed to read status response:" << line.trimmed();
      }
      parseStatusResponse(last_status_code_, last_status_line_);
      awaiting_text_ = awaitingText(last_status_code_);
    } else {
      if (line == ".\r\n") {
        parseTextResponse(text_buffer_);
        resetTextBuffer();
      } else {
        if (line.startsWith("..")) line.remove(0, 1);
        text_buffer_.append(line);
      }
    }
  }
}

bool DictClient::readStatusLine(const QString& line) {
  const int code_length = 3;
  bool retval = false;

  if (line.length() < code_length) {
    last_status_code_ = 0;
    last_status_line_ = line.trimmed();
  } else {
    last_status_code_ = line.left(code_length).toInt(&retval);
    last_status_line_ = line.mid(code_length).trimmed();
  }
  return retval;
}

void DictClient::parseStatusResponse(int code, const QString& line) {
  qDebug() << code << line;

  switch (code) {
    case CODE_DEFINITIONS_FOUND: {
        const int count = line.section(' ', 0, 0).toInt();
        emit definitionsFound(count);
      }
      break;

    case CODE_MATCHES_FOUND: {
        const int count = line.section(' ', 0, 0).toInt();
        emit matchesFound(count);
      }
      break;
  }
}

void DictClient::parseTextResponse(const QString& text) {
  qDebug() << text;

  switch (last_status_code_) {
    case CODE_DATABASE_LIST:
      parseDatabaseList(text);
      break;

    case CODE_STRATEGY_LIST:
      parseStrategyList(text);
      break;

    case CODE_DATABASE_INFO:
      emit databaseInfoReceived(DatabaseInfo{last_status_line_, text});
      break;

    case CODE_HELP:
      emit helpTextReceived(text);
      break;

    case CODE_SERVER_INFO:
      emit serverInfoReceived(text);
      break;

    case CODE_DEFINITION_FOLLOWS:
      emit definitionReceived(Definition{last_status_line_, text});
      break;

    case CODE_MATCHES_FOUND:
      emit matchesReceived(Matches{last_status_line_, text});
      break;
  }
}

void DictClient::parseDatabaseList(const QString& text) {
  const QList<QStringList> databases = parse_table(text);
  for (const QStringList& args : databases) {
    if (args.size() >= 2) {
      databases_.insert(args.at(0), args.at(1));
    }
  }
}

void DictClient::parseStrategyList(const QString& text) {
  const QList<QStringList> strategies = parse_table(text);
  for (const QStringList& args : strategies) {
    if (args.size() >= 2) {
      search_strategies_.insert(args.at(0), args.at(1));
    }
  }
}

void DictClient::handleError(QAbstractSocket::SocketError error) {
  qDebug() << "QAbstractSocket::SocketError:" << error;
  qDebug() << "QAbstractSocket::errorString():" << socket_.errorString();
}

void DictClient::resetTextBuffer() {
  awaiting_text_ = false;
  text_buffer_.clear();
}

void DictClient::resetCache() {
  resetTextBuffer();
  databases_.clear();
  search_strategies_.clear();
}

QString DictClient::sanitizeCmd(const QString& cmd) {
  QString retval = cmd;
  retval.truncate(maxLineLength());
  retval.remove('\r').remove('\n');
  return retval;
}

bool DictClient::awaitingText(int status_code) {
  switch (status_code) {
    case CODE_DATABASE_LIST:
    case CODE_STRATEGY_LIST:
    case CODE_DATABASE_INFO:
    case CODE_HELP:
    case CODE_SERVER_INFO:
    case CODE_DEFINITION_FOLLOWS:
    case CODE_MATCHES_FOUND:
      return true;
    default:
      return false;
  }
}
