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

#include "config/DictServerList.h"
#include <QModelIndex>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <KConfig>
#include <KConfigGroup>
#include "config/DictServerItem.h"

DictServerList::DictServerList(KConfig* config, QObject* parent)
    : QAbstractListModel{parent}, config_{config} {
}

QVariant DictServerList::data(const QModelIndex&, int) const {
  return QVariant{};
}

int DictServerList::rowCount(const QModelIndex& parent) const {
  return parent.isValid() ? 0 : servers_.size();
}

int DictServerList::columnCount(const QModelIndex&) const {
  return 2;
}

void DictServerList::readConfig() {
  servers_.clear();

  const KConfigGroup dict_group = config_->group("Dict");
  if (!dict_group.exists()) return;

  const QStringList subgroups = dict_group.groupList();
  for (const QString& subgroup : subgroups) {
    if (subgroup.startsWith("Server")) {
      const KConfigGroup server_group = dict_group.group(subgroup);
      servers_ << DictServerItem(server_group);
    }
  }
}
