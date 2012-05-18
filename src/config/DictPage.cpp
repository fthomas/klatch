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
#include <QtGlobal>
#include <KIcon>
#include "config/DictServerDialog.h"
#include "config/DictServerItem.h"
#include "config/DictServerList.h"
#include "ui_DictPage.h"

DictPage::DictPage(DictServerList* list, QWidget* parent)
    : QWidget{parent}, ui_{new Ui::DictPage}, server_list_{list} {
  Q_ASSERT(server_list_);

  ui_->setupUi(this);

  ui_->add->setIcon(KIcon("list-add"));
  ui_->modify->setIcon(KIcon("configure"));
  ui_->remove->setIcon(KIcon("list-remove"));

  ui_->servers_view->setModel(server_list_);
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

void DictPage::addServer() {
  DictServerItem server;
  DictServerDialog dialog;
  dialog.readServerItem(server);

  if (dialog.exec() && server_list_) {
    dialog.writeServerItem(server);
    server_list_->appendServer(server);
  }
}

void DictPage::modifyServer() {
  const QModelIndex index = selectedIndex();
  if (!index.isValid() || !server_list_) return;

  DictServerItem& server = server_list_->at(index);
  DictServerDialog dialog;
  dialog.readServerItem(server);

  if (dialog.exec()) {
    dialog.writeServerItem(server);
    server_list_->emitDataChanged(index);
  }
}

void DictPage::removeServer() {
  const QModelIndex index = selectedIndex();
  if (index.isValid() && server_list_) {
    server_list_->removeRow(index.row());
  }
}

QModelIndex DictPage::selectedIndex() const {
  const QModelIndexList selected = server_selection_->selectedRows();
  if (selected.isEmpty()) return QModelIndex{};

  return selected.at(0);
}

void DictPage::createConnections() {
  connect(server_selection_,
      SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
    this, SLOT(updateButtons(QItemSelection)));

  connect(ui_->add,    SIGNAL(clicked()), this, SLOT(addServer()));
  connect(ui_->modify, SIGNAL(clicked()), this, SLOT(modifyServer()));
  connect(ui_->remove, SIGNAL(clicked()), this, SLOT(removeServer()));
}
