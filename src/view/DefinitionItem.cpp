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
#include "dict/Definition.h"
#include "ui_DefinitionItem.h"

DefinitionItem::DefinitionItem(QWidget* parent)
    : DefinitionItem{Definition{}, parent} {
}

DefinitionItem::DefinitionItem(const Definition& def, QWidget* parent)
    : QFrame{parent}, ui_{new Ui::DefinitionItem}, def_{def} {
  ui_->setupUi(this);
  updateUi();
}

DefinitionItem::~DefinitionItem() {
  delete ui_;
}

Definition DefinitionItem::definition() const {
  return def_;
}

void DefinitionItem::setDefinition(const Definition& def) {
  def_ = def;
  updateUi();
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

void DefinitionItem::updateUi() {
  if(def_.isEmpty()) {
    ui_->word->clear();
    ui_->database->clear();
    ui_->text->clear();
  } else {
    const QString db_text = !def_.databaseDescription().isEmpty() ?
      def_.databaseDescription() : def_.database();

    ui_->word->setText(def_.text());
    ui_->database->setText(db_text);
    ui_->text->setPlainText(def_.text());
  }
}
