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

#ifndef DICTCLIENT_H
#define DICTCLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QTextStream>
#include <QtGlobal>

/**
 * https://tools.ietf.org/html/rfc2229
 */
class DictClient : public QObject {
  Q_OBJECT

 public:
  explicit DictClient(QObject* parent = 0);

  void connectToHost(const QString& hostname, quint16 port = kDefaultPort);
  void close();

 public:
  static const quint16 kDefaultPort = 2628;

 signals:

 public slots:

 private:
  void sendClient();
  void sendDefine(const QString& word, const QString& database = "*");
  void sendHelp();
  void sendMatch(const QString& word, const QString& strategy = "exact",
                 const QString& database = "*");
  void sendOptionMime();
  void sendQuit();
  void sendShowDatabases();
  void sendShowInfo(const QString& database);
  void sendShowServer();
  void sendShowStrategies();
  void sendStatus();

  void createConnections();
  bool readStatusLine(const QString& line);

  void parseStatusResponse(int code, const QString& line);
  void parseTextResponse(const QString& text);

  static QString sanitizeCmd(const QString& cmd);
  static bool awaitingText(int status_code);

 private slots:
  void readData();
  void handleError(QAbstractSocket::SocketError error);

 private:
  QTcpSocket socket_;
  QTextStream stream_;

  int last_status_code_;
  QString last_status_line_;

  static const int kMaxLineLength = 1024 - 2;
};

#endif // DICTCLIENT_H
