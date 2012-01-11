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

#include "LookupWidget.h"
#include <QClipboard>
#include <QEvent>
#include <QString>
#include <QWidget>
#include <KApplication>
#include <KCmdLineArgs>
#include "ui_LookupWidget.h"

LookupWidget::LookupWidget(QWidget* parent)
    : QWidget(parent), ui_(new Ui::LookupWidget) {
  ui_->setupUi(this);
  ui_->klineedit->setText(getInitialWord());

  // change the text color to red when no definitions are found?
}

LookupWidget::~LookupWidget() {
  delete ui_;
}

void LookupWidget::changeEvent(QEvent* event) {
  QWidget::changeEvent(event);
  switch (event->type()) {
    case QEvent::LanguageChange:
      ui_->retranslateUi(this);
      break;
    default:
      break;
  }
}

QString LookupWidget::getInitialWord() {
  const auto args = KCmdLineArgs::parsedArgs();

  return (args->count()) ? args->arg(0)
    : KApplication::clipboard()->text(QClipboard::Selection);
}
