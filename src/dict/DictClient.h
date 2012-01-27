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

#ifndef DICT_DICTCLIENT_H
#define DICT_DICTCLIENT_H

#include <QMap>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QTextStream>
#include <QtGlobal>

class Definition;
class Matches;

/**
 * https://tools.ietf.org/html/rfc2229
 */
class DictClient : public QObject {
  Q_OBJECT

 public:
  explicit DictClient(QObject* parent = 0);
  explicit DictClient(const QString& hostname, QObject* parent = 0);
  DictClient(const QString& hostname, quint16 port, QObject* parent = 0);

  QString peerName() const;
  void setPeerName(const QString& name);

  quint16 peerPort() const;
  void setPeerPort(quint16 port);

  static quint16 defaultPort();
  static int maxLineLength();

  QMap<QString, QString> databases() const;
  QMap<QString, QString> searchStrategies() const;

 signals:
  void definitionsFound(int count);
  void matchesFound(int count);

  void definitionReceived(const Definition& def);
  void matchesReceived(const Matches& matches);

 public slots:
  void sendClient();
  void sendDefine(const QString& word, const QString& database = "*");
  void sendHelp();
  void sendMatch(const QString& word, const QString& strategy = "prefix",
                 const QString& database = "*");
  void sendOptionMime();
  void sendQuit();
  void sendShowDatabases();
  void sendShowInfo(const QString& database);
  void sendShowServer();
  void sendShowStrategies();
  void sendStatus();

 private:
  void connectIfDisconnected();
  void sendRawCommand(const QString& command);

  bool readStatusLine(const QString& line);
  void parseStatusResponse(int code, const QString& line);
  void parseTextResponse(const QString& text);
  void resetTextBuffer();

  void parseDatabaseList(const QString& text);
  void parseStrategyList(const QString& text);

  static QString sanitizeCmd(const QString& cmd);
  static bool awaitingText(int status_code);

 private slots:
  void readData();
  void handleError(QAbstractSocket::SocketError error);
  void resetCache();

 private:
  QString hostname_;
  quint16 port_;

  QTcpSocket socket_;
  QTextStream stream_;

  int last_status_code_;
  QString last_status_line_;

  bool awaiting_text_ = false;
  QString text_buffer_;

  QMap<QString, QString> databases_;
  QMap<QString, QString> search_strategies_;
};

#endif // DICT_DICTCLIENT_H
