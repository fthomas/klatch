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

#include "results/ResultView.h"
#include <QMenu>
#include <QPoint>
#include <QWidget>
#include <Qt>

#include <QDebug>

ResultView::ResultView(QWidget* parent) : QListView{parent} {
  setContextMenuPolicy(Qt::CustomContextMenu);

  createConnections();
  createContextMenu();
}

void ResultView::showContextMenu(const QPoint& point) {
  if (!context_menu_->isEmpty()) {
    context_menu_->exec(viewport()->mapToGlobal(point));
  }
}

void ResultView::runCustomAction() {
  qDebug() << "runCustomAction";
}

void ResultView::createConnections() {
  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
    this, SLOT(showContextMenu(QPoint)));
}

void ResultView::createContextMenu() {
  context_menu_ = new QMenu{this};

  const auto& actions = custom_actions_.actions();
  for (auto it = actions.begin(); it != actions.end(); ++it) {
    auto qaction =
      context_menu_->addAction(it.key(), this, SLOT(runCustomAction()));
    qaction->setData(QVariant::fromValue(it.value()));
  }
}
