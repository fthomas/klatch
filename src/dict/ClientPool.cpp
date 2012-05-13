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

#include "dict/ClientPool.h"
#include <QString>
#include <QtAlgorithms>
#include <QtGlobal>
#include "config/DictServerItem.h"
#include "config/DictServerList.h"
#include "dict/AbstractDictClient.h"
#include "dict/Definition.h"
#include "dict/DictClient.h"
#include "dict/Matches.h"

ClientPool::ClientPool(DictServerList* list, QObject* parent)
    : AbstractDictClient{parent}, server_list_{list} {
  Q_ASSERT(server_list_);

  createConnections();
  createClients();
}

ClientPool::~ClientPool() {
  clearClients();
}

void ClientPool::sendDefine(const QString& word, const QString& database) {
  for (DictClient* const client : clients_) {
    client->sendDefine(word, database);
  }
}

void ClientPool::sendMatch(const QString& word, const QString& strategy,
                           const QString& database) {
  for (DictClient* const client : clients_) {
    client->sendMatch(word, strategy, database);
  }
}

void ClientPool::createConnections() {
  connect(server_list_, SIGNAL(contentChanged()),
    this, SLOT(recreateClients()));
}

void ClientPool::createClients() {
  for (int row = 0; row < server_list_->rowCount(); ++row) {
    const DictServerItem& server = (*server_list_)[row];
    DictClient* client = new DictClient{server.hostName(), server.port()};

    clients_ << client;
    connect(client, SIGNAL(definitionReceived(Definition)),
      this, SIGNAL(definitionReceived(Definition)));
    connect(client, SIGNAL(matchesReceived(Matches)),
      this, SIGNAL(matchesReceived(Matches)));
  }
}

void ClientPool::clearClients() {
  qDeleteAll(clients_);
  clients_.clear();
}

void ClientPool::recreateClients() {
  clearClients();
  createClients();
}
