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

#include "DictClient.h"
#include <QAbstractSocket>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QTextStream>
#include <QtDebug>
#include "KlatchData.h"

DictClient::DictClient(QObject* parent) : QObject(parent) {
  stream_.setDevice(&socket_);
  stream_.setCodec("UTF-8");

  createConnections();



  connectToHost("localhost");
  sendShowDatabases();
  sendShowServer();
  sendShowInfo("fd-deu-eng");
  sendShowStrategies();
  sendStatus();
  sendClient();
  sendHelp();
  sendOptionMime();
  sendDefine("hallo");
  sendMatch("hal", "prefix");
  sendQuit();
}

void DictClient::connectToHost(const QString& hostname, quint16 port) {
  socket_.connectToHost(hostname, port);
  sendClient();
}

void DictClient::close() {
  sendQuit();
  socket_.close();
}

void DictClient::createConnections() {
  connect(&socket_, SIGNAL(readyRead()),
    this, SLOT(readData()));
  connect(&socket_, SIGNAL(error(QAbstractSocket::SocketError)),
    this, SLOT(handleError(QAbstractSocket::SocketError)));
}

void DictClient::sendClient() {
  stream_ << "CLIENT " << KlatchData::displayNameSlashVersion() << crlf;
}

void DictClient::sendDefine(const QString& word, const QString& database) {
  const QString cmd = QString("DEFINE \"%1\" \"%2\"").arg(database, word);
  stream_ << sanitizeCmd(cmd) << crlf;
}

void DictClient::sendHelp() {
  stream_ << "HELP" << crlf;
}

void DictClient::sendMatch(const QString& word, const QString& strategy,
                           const QString& database) {
  const QString cmd =
    QString("MATCH \"%1\" \"%2\" \"%3\"").arg(database, strategy, word);
  stream_ << sanitizeCmd(cmd) << crlf;
}

void DictClient::sendOptionMime() {
  stream_ << "OPTION MIME" << crlf;
}

void DictClient::sendQuit() {
  stream_ << "QUIT" << crlf;
}

void DictClient::sendShowDatabases() {
  stream_ << "SHOW DB" << crlf;
}

void DictClient::sendShowInfo(const QString& database) {
  const QString cmd = QString("SHOW INFO \"%1\"").arg(database);
  stream_ << sanitizeCmd(cmd) << crlf;
}

void DictClient::sendShowServer() {
  stream_ << "SHOW SERVER" << crlf;
}

void DictClient::sendShowStrategies() {
  stream_ << "SHOW STRAT" << crlf;
}

void DictClient::sendStatus() {
  stream_ << "STATUS" << crlf;
}

void DictClient::readData() {

  while (!socket_.atEnd()) {
    qDebug() << socket_.readLine().trimmed();
  }

}

void DictClient::handleError(QAbstractSocket::SocketError error) {
  qDebug() << "QAbstractSocket::SocketError:" << error;
  qDebug() << "QAbstractSocket::errorString():" << socket_.errorString();
}

QTextStream& DictClient::crlf(QTextStream& stream) {
  return stream << "\r\n" << flush;
}

QString DictClient::sanitizeCmd(const QString& cmd) {
  QString retval = cmd;
  retval.truncate(kMaxLineLength);
  retval.remove('\r').remove('\n');
  return retval;
}
