// Klatch - a DICT client for KDE
// Copyright © 2011-2012 Frank S. Thomas <frank@timepit.eu>
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QtGlobal>
#include <KXmlGuiWindow>
#include "config/DictServerList.h"

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

class LookupWidget;

class MainWindow : public KXmlGuiWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);

 private slots:
  void toggleMenuBar();
  void showPreferences();

 private:
  void setupActions();

 private:
  DictServerList server_list_;
  LookupWidget* lookup_;
};

#endif // MAINWINDOW_H
