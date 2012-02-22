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

#ifndef VIEW_DEFINITIONITEM_H
#define VIEW_DEFINITIONITEM_H

#include <QFrame>
#include <QtGlobal>
#include "dict/Definition.h"

QT_BEGIN_NAMESPACE
class QEvent;
class QWidget;
QT_END_NAMESPACE

namespace Ui {
  class DefinitionItem;
}

class DefinitionItem : public QFrame {
  Q_OBJECT

 public:
  explicit DefinitionItem(QWidget* parent = 0);
  explicit DefinitionItem(const Definition& def, QWidget* parent = 0);
  ~DefinitionItem();

  Definition definition() const;
  void setDefinition(const Definition& def);

 protected:
  void changeEvent(QEvent* event);

 private:
  void updateUi();

 private:
  Ui::DefinitionItem* ui_;
  Definition def_;
};

#endif // VIEW_DEFINITIONITEM_H
