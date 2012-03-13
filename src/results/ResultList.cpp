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

#include "results/ResultList.h"
#include <QModelIndex>
#include <QObject>
#include <QString>
#include <QVariant>
#include <Qt>
#include "dict/Definition.h"
#include "utility/algorithm.h"
#include "utility/string.h"

ResultList::ResultList(QObject* parent) : QAbstractListModel{parent} {
}

QVariant ResultList::data(const QModelIndex& index, int role) const {
  if (!index.isValid() || index.row() >= definitions_.size()) {
    return QVariant{};
  }

  if  (role == Qt::DisplayRole) {
    const Definition& def = definitions_.at(index.row());

    return QString{"%1 %2 [%3]:\n\n%4\n"}
      .arg(tr("From"))
      .arg(def.databaseDescription())
      .arg(def.database())
      .arg(indent(def.text().trimmed()));
  }
  return QVariant{};
}

int ResultList::rowCount(const QModelIndex& parent) const {
  return parent.isValid() ? 0 : definitions_.size();
}

QString ResultList::word() const {
  return word_;
}

void ResultList::setWord(const QString& word) {
  if (word == word_) return;

  word_ = word;
  removeNonMatchingResults();
}

bool ResultList::appendResult(const Definition& def) {
  if (def.word().compare(word_, Qt::CaseInsensitive) != 0) {
    return false;
  }

  const int row = definitions_.size();
  beginInsertRows(QModelIndex{}, row, row);
  definitions_ << def;
  endInsertRows();

  return true;
}

void ResultList::removeNonMatchingResults() {
  if (definitions_.isEmpty()) return;

  const auto def_does_not_match = [&](const Definition& def) {
    return def.word().compare(word_, Qt::CaseInsensitive) != 0;
  };

  beginResetModel();
  erase_if(definitions_, def_does_not_match);
  endResetModel();
}
