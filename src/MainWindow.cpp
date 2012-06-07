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

#include "MainWindow.h"
#include <QWidget>
#include <KAction>
#include <KActionCollection>
#include <KApplication>
#include <KConfigDialog>
#include <KLocalizedString>
#include <KMenuBar>
#include <KStandardAction>
#include <KToggleAction>
#include "config/DictPage.h"
#include "config/DictServerList.h"
#include "LookupWidget.h"
#include "klatchconfig.h"

MainWindow::MainWindow(QWidget* parent) : KXmlGuiWindow{parent},
    server_list_{new DictServerList{this}},
    lookup_{new LookupWidget{server_list_, this}} {
  setupActions();
  setCentralWidget(lookup_);
}

void MainWindow::setupActions() {
  KStandardAction::preferences(this, SLOT(showPreferences()),
    actionCollection());
  KStandardAction::quit(kapp, SLOT(quit()),
    actionCollection());

  KToggleAction* const show_menubar =
    KStandardAction::showMenubar(this, SLOT(toggleMenuBar()),
      actionCollection());

  KToggleAction* const show_dicts =
    new KToggleAction(i18n("Show Dictionaries"), this);
  actionCollection()->addAction("showDicts", show_dicts);

  setupGUI();

  show_menubar->setChecked(menuBar()->isVisibleTo(this));
}

void MainWindow::toggleMenuBar() {
  menuBar()->setVisible(menuBar()->isHidden());
}

void MainWindow::showPreferences() {
  const QString preferences = "preferences";
  if (KConfigDialog::showDialog(preferences)) return;

  KConfigDialog* const dialog =
    new KConfigDialog{this, preferences, KlatchConfig::self()};

  DictPage* const dict_page = new DictPage{server_list_};
  dialog->addPage(dict_page, i18n("DICT"), "accessories-dictionary",
    i18n("Manage Servers"));

  dialog->show();
}
