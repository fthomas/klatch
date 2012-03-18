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

#ifndef CONFIG_DICTSERVERLIST_H
#define CONFIG_DICTSERVERLIST_H

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QObject>
#include <QVariant>
#include <Qt>
#include <KGlobal>
#include <KSharedConfig>
#include "config/DictServerItem.h"

class KConfig;

class DictServerList : public QAbstractListModel {
  Q_OBJECT

 public:
  explicit DictServerList(KSharedConfigPtr config = KGlobal::config(),
                          QObject* parent = 0);

  DictServerItem& at(const QModelIndex& index);
  void emitDataChanged(const QModelIndex& index);

  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;

  int rowCount(const QModelIndex& parent = QModelIndex{}) const;
  int columnCount(const QModelIndex& parent = QModelIndex{}) const;

  bool appendServer(const DictServerItem& server);
  bool removeRows(int row, int count,
                  const QModelIndex& parent = QModelIndex{});

  void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

 private:
  void readConfig();
  QString newSubgroupName() const;

 private:
  KSharedConfigPtr config_;
  QList<DictServerItem> servers_;

  const QString dict_name_ = "Dict";
  const QString server_prefix_ = "Server";
};

#endif // CONFIG_DICTSERVERLIST_H
