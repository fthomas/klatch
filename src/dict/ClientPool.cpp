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
#include <QtAlgorithms>
#include <QtGlobal>
#include "config/DictServerList.h"
#include "dict/DictClient.h"

ClientPool::ClientPool(DictServerList* list, QObject* parent)
    : QObject{parent}, server_list_{list} {
  Q_ASSERT(server_list_);

  createClients();
}

void ClientPool::createClients() {
  for (int row = 0; row < server_list_->rowCount(); ++row) {
    const DictServerItem& server = (*server_list_)[row];
    clients_ << new DictClient{server.hostName(), server.port()};
  }
}

void ClientPool::clearClients() {
  qDeleteAll(clients_);
  clients_.clear();
}
