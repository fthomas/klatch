// Klatch - a DICT client for KDE
// Copyright © 2011 Frank S. Thomas <frank@timepit.eu>
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
#include "KlatchData.h"

#include <QtDebug>

DictClient::DictClient(QObject* parent) : QObject(parent) {
  stream_.setDevice(&socket_);
  stream_.setCodec("UTF-8");

  createConnections();



  socket_.connectToHost("localhost", kDefaultPort);
  sendShowDatabases();
  sendShowServer();
  sendShowInfo("fd-deu-eng");
  sendShowStrategies();
  sendStatus();
  sendClient();
  sendHelp();
  sendOptionMime();

  sendQuit();
}

void DictClient::createConnections() {
  connect(&socket_, SIGNAL(readyRead()),
    this, SLOT(readData()));
  connect(&socket_, SIGNAL(error(QAbstractSocket::SocketError)),
    this, SLOT(handleError(QAbstractSocket::SocketError)));
}

void DictClient::sendClient() {
  stream_ << "CLIENT " << KlatchData::displayNameSlashVersion() << endl;
}

void DictClient::sendHelp() {
  stream_ << "HELP" << endl;
}

void DictClient::sendOptionMime() {
  stream_ << "OPTION MIME" << endl;
}

void DictClient::sendQuit() {
  stream_ << "QUIT" << endl;
}

void DictClient::sendShowDatabases() {
  stream_ << "SHOW DB" << endl;
}

void DictClient::sendShowInfo(const QString& database) {
  auto cmd = QString("SHOW INFO \"%1\"").arg(database);
  // entferne lf cr aus datbase
  cmd.truncate(kMaxLineLength);

  stream_ << cmd << endl;
}

void DictClient::sendShowServer() {
  stream_ << "SHOW SERVER" << endl;
}

void DictClient::sendShowStrategies() {
  stream_ << "SHOW STRAT" << endl;
}

void DictClient::sendStatus() {
  stream_ << "STATUS" << endl;
}

void DictClient::readData() {

  while (!socket_.atEnd()) {
    qDebug() << socket_.readLine().trimmed();
  }

}

void DictClient::handleError(QAbstractSocket::SocketError) {
}
