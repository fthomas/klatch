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
#include <QtAlgorithms>
#include <QtGlobal>
#include <KConfig>
#include <KConfigGroup>
#include <KGlobal>
#include <KLocalizedString>
#include <KSharedConfig>
#include "config/DictServerItem.h"

DictServerList::DictServerList(QObject* parent)
    : DictServerList{KGlobal::config(), parent} {}

DictServerList::DictServerList(KSharedConfigPtr config, QObject* parent)
    : QAbstractListModel{parent}, config_{config} {
  readConfig();

  connect(this, SIGNAL(rowsInserted(QModelIndex,int,int)),
    this, SIGNAL(contentChanged()));
  connect(this, SIGNAL(rowsRemoved(QModelIndex,int,int)),
    this, SIGNAL(contentChanged()));
  connect(this, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
    this, SIGNAL(contentChanged()));
}

DictServerItem& DictServerList::operator[](int i) {
  return servers_[i];
}

const DictServerItem& DictServerList::operator[](int i) const {
  return servers_[i];
}

DictServerItem& DictServerList::at(const QModelIndex& index) {
  Q_ASSERT(isValidIndex(index));
  return servers_[index.row()];
}

const DictServerItem& DictServerList::at(const QModelIndex& index) const {
  Q_ASSERT(isValidIndex(index));
  return servers_[index.row()];
}

void DictServerList::emitDataChanged(const QModelIndex& index) {
  emit dataChanged(index, index);
}

QVariant DictServerList::data(const QModelIndex& index, int role) const {
  if (!isValidIndex(index)) {
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

bool DictServerList::appendServer(const DictServerItem& server) {
  KConfigGroup subgroup =
    config_->group(dict_name_).group(newSubgroupName());

  DictServerItem my_server = server;
  my_server.setConfigGroup(subgroup);

  const int row = servers_.size();
  beginInsertRows(QModelIndex{}, row, row);
  servers_ << my_server;
  endInsertRows();

  return true;
}

bool DictServerList::removeRows(int row, int count,
                                const QModelIndex& parent) {
  const int last = row + count;
  if (parent.isValid() || count < 1 || last > servers_.size()) {
    return false;
  }

  auto it = servers_.begin() + row;

  beginRemoveRows(QModelIndex{}, row, last - 1);
  for (int i = 0; i < count; ++i) {
    it->configGroup().deleteGroup();
    it = servers_.erase(it);
  }
  endRemoveRows();
  config_->sync();

  return true;
}

void DictServerList::sort(int column, Qt::SortOrder order) {
  auto comp_fn = DictServerItem::lessByHostName;

  if (column == 0) {
    if (order == Qt::DescendingOrder) {
      comp_fn = DictServerItem::greaterByHostName;
    }
  } else if (column == 1) {
    if (order == Qt::AscendingOrder) {
      comp_fn = DictServerItem::lessByPort;
    }
    else if (order == Qt::DescendingOrder) {
      comp_fn = DictServerItem::greaterByPort;
    }
  }

  emit layoutAboutToBeChanged();
  qSort(servers_.begin(), servers_.end(), comp_fn);
  emit layoutChanged();
}

void DictServerList::readConfig() {
  servers_.clear();

  KConfigGroup dict_group = config_->group(dict_name_);
  if (!dict_group.exists()) return;

  const QStringList subgroups = dict_group.groupList();
  for (const QString& subgroup : subgroups) {
    if (subgroup.startsWith(server_prefix_)) {
      servers_ << DictServerItem{dict_group.group(subgroup)};
    }
  }
}

QString DictServerList::newSubgroupName() const {
  KConfigGroup dict_group = config_->group(dict_name_);

  QString name;
  int i = -1;

  do {
    name = QString{"%1%2"}.arg(server_prefix_).arg(++i);
  } while (dict_group.hasGroup(name));
  return name;
}

bool DictServerList::isValidIndex(const QModelIndex& index) const {
  return index.isValid() && index.row() < servers_.size();
}
