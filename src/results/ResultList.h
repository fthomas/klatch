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

#ifndef RESULTS_RESULTLIST_H
#define RESULTS_RESULTLIST_H

#include <QAbstractListModel>
#include <QObject>
#include <QVariant>
#include <Qt>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

class ResultList : public QAbstractListModel {
  Q_OBJECT

 public:
  explicit ResultList(QObject* parent = 0);

  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  int rowCount(const QModelIndex& parent = QModelIndex{}) const;
};

#endif // RESULTS_RESULTLIST_H
