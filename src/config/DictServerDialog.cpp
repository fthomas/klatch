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

#include "config/DictServerDialog.h"
#include <QEvent>
#include <QSize>
#include <QString>
#include <QWidget>
#include <Qt>
#include <KLocalizedString>
#include "config/DictServerItem.h"

DictServerDialog::DictServerDialog(QWidget* parent) : KDialog{parent} {
  QWidget* main_widget = new QWidget{this};
  ui_.setupUi(main_widget);
  ui_.hostname->setFocus(Qt::PopupFocusReason);

  setCaption(i18n("Configure DICT Server"));
  setMainWidget(main_widget);

  connect(ui_.hostname, SIGNAL(textChanged(QString)),
    this, SLOT(hostNameChangedSlot(QString)));
}

void DictServerDialog::readServerItem(const DictServerItem& server) {
  ui_.hostname->setText(server.hostName());
  ui_.port->setValue(server.port());
}

void DictServerDialog::writeServerItem(DictServerItem& server) const {
  server.setHostName(ui_.hostname->text());
  server.setPort(ui_.port->value());
}

QSize DictServerDialog::sizeHint() const {
  return QSize{360, 120};
}

void DictServerDialog::changeEvent(QEvent* event) {
  KDialog::changeEvent(event);
  switch (event->type()) {
    case QEvent::LanguageChange:
      ui_.retranslateUi(this);
      break;
    default:
      break;
  }
}

void DictServerDialog::hostNameChangedSlot(const QString& hostname) {
  enableButtonOk(!hostname.isEmpty());
}
