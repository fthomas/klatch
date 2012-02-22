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

#include "view/DefinitionItem.h"
#include <QEvent>
#include <QFrame>
#include <QWidget>
#include "ui_DefinitionItem.h"

DefinitionItem::DefinitionItem(QWidget* parent)
    : QFrame{parent}, ui_{new Ui::DefinitionItem} {
  ui_->setupUi(this);
}

DefinitionItem::~DefinitionItem() {
  delete ui_;
}

void DefinitionItem::changeEvent(QEvent* event) {
  QFrame::changeEvent(event);
  switch (event->type()) {
    case QEvent::LanguageChange:
      ui_->retranslateUi(this);
      break;
    default:
      break;
  }
}
