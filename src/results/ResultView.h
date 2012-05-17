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

#ifndef RESULTS_RESULTVIEW_H
#define RESULTS_RESULTVIEW_H

#include <QListView>
#include <QWidget>
#include <QtGlobal>
#include "scripts/CustomActions.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QPoint;
QT_END_NAMESPACE

class ResultView : public QListView {
  Q_OBJECT

 public:
  explicit ResultView(QWidget* parent = 0);

 private slots:
  void showContextMenu(const QPoint& point);
  void runCustomAction();

 private:
  void createConnections();
  void createContextMenu();

 private:
  CustomActions custom_actions_;
  QMenu* context_menu_;
};

#endif // RESULTS_RESULTVIEW_H
