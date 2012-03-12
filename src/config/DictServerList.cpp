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
#include <KLocalizedString>
#include "config/DictServerItem.h"

DictServerList::DictServerList(KConfig* config, QObject* parent)
    : QAbstractListModel{parent}, config_{config} {
  readConfig();
}

QVariant DictServerList::data(const QModelIndex& index, int role) const {
  if (!index.isValid() || index.row() >= servers_.size()) {
    return QVariant{};
  }

  if (role == Qt::DisplayRole && index.column() < 2) {
    const DictServerItem& server = servers_.at(index.row());

    switch (index.column()) {
      case 0: return server.hostName();
      case 1: return server.port();
    }
  }
  return QVariant{};
}

QVariant DictServerList::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
    return QVariant{};
  }

  switch (section) {
    case 0: return i18n("Hostname");
    case 1: return i18n("Port");
  }
  return QVariant{};
}

int DictServerList::rowCount(const QModelIndex& parent) const {
  return parent.isValid() ? 0 : servers_.size();
}

int DictServerList::columnCount(const QModelIndex&) const {
  return 2;
}

bool DictServerList::insertRow(const DictServerItem& server) {
  KConfigGroup subgroup =
    config_->group(dict_name_).group(newSubgroupName());

  DictServerItem my_server = server;
  my_server.setConfigGroup(subgroup);

  const int new_row = servers_.size();
  beginInsertRows(QModelIndex{}, new_row, new_row);
  servers_ << my_server;
  endInsertRows();

  return true;
}

void DictServerList::readConfig() {
  servers_.clear();

  KConfigGroup dict_group = config_->group(dict_name_);
  if (!dict_group.exists()) return;

  const QStringList subgroups = dict_group.groupList();
  for (const QString& subgroup : subgroups) {
    if (subgroup.startsWith(server_prefix_)) {
      servers_ << DictServerItem(dict_group.group(subgroup));
    }
  }
}

QString DictServerList::newSubgroupName() const {
  KConfigGroup dict_group = config_->group(dict_name_);

  QString name;
  int i = 0;

  do {
    name = QString{"%1%2"}.arg(server_prefix_).arg(i++);
  } while (dict_group.hasGroup(name));
  return name;
}
