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

#ifndef DICT_CLIENTPOOL_H
#define DICT_CLIENTPOOL_H

#include <QObject>
#include <QList>
#include <QtGlobal>
#include "dict/AbstractDictClient.h"

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class DictClient;
class DictServerList;

class ClientPool : public AbstractDictClient {
  Q_OBJECT

 public:
  explicit ClientPool(DictServerList* list, QObject* parent = 0);
  ~ClientPool();

 public slots:
  void sendDefine(const QString& word, const QString& database = "*");
  void sendMatch(const QString& word, const QString& strategy = "prefix",
                 const QString& database = "*");

 private:
  void createConnections();

  void createClients();
  void clearClients();

 private slots:
  void recreateClients();

 private:
  DictServerList* const server_list_;
  QList<DictClient*> clients_;
};

#endif // DICT_CLIENTPOOL_H
