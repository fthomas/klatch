// Klatch - a DICT client for KDE
// Copyright © 2011 Frank S. Thomas <frank@timepit.eu>
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

#include "MainWindow.h"
#include <QClipboard>
#include <QString>
#include <QWidget>
#include <KApplication>
#include <KCmdLineArgs>

MainWindow::MainWindow(QWidget* parent) : KXmlGuiWindow(parent) {
  setupGUI();
}

QString MainWindow::getInitialWord() {
  auto args = KCmdLineArgs::parsedArgs();
  if (args->count()) {
    return args->arg(0);
  } else {
    return KApplication::clipboard()->text(QClipboard::Selection);
  }
}
