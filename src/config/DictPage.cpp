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

#include "config/DictPage.h"
#include <QEvent>
#include <QItemSelection>
#include <QWidget>
#include <KIcon>
#include "ui_DictPage.h"

DictPage::DictPage(QWidget* parent)
    : QWidget{parent}, ui_{new Ui::DictPage} {
  ui_->setupUi(this);

  ui_->add->setIcon(KIcon("list-add"));
  ui_->modify->setIcon(KIcon("configure"));
  ui_->remove->setIcon(KIcon("list-remove"));

  server_selection_ = ui_->servers_view->selectionModel();
  createConnections();
}

DictPage::~DictPage() {
  delete ui_;
}

void DictPage::changeEvent(QEvent* event) {
  QWidget::changeEvent(event);
  switch (event->type()) {
    case QEvent::LanguageChange:
      ui_->retranslateUi(this);
      break;
    default:
      break;
  }
}

void DictPage::updateButtons(const QItemSelection& selected) {
  const bool enable = !selected.isEmpty();

  ui_->modify->setEnabled(enable);
  ui_->remove->setEnabled(enable);
}

void DictPage::removeSelected() {
  const QModelIndexList selected = server_selection_->selectedRows();
  if (selected.isEmpty()) return;

  const QModelIndex& index = selected[0];
  if (!index.isValid()) return;

  ui_->servers_view->model()->removeRow(index.row());
}

void DictPage::createConnections() {
  connect(server_selection_,
      SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
    this, SLOT(updateButtons(QItemSelection)));

  connect(ui_->remove, SIGNAL(clicked()),
    this, SLOT(removeSelected()));
}
