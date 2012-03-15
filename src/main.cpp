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

#include <KAboutData>
#include <KApplication>
#include <KCmdLineArgs>
#include <KCmdLineOptions>
#include <KLocale>
#include "KlatchData.h"
#include "MainWindow.h"

int main(int argc, char* argv[]) {
  KAboutData about = KlatchData::aboutData();
  KCmdLineOptions options;
  options.add("+[word]", ki18n("Word to lookup in dictionaries"));

  KCmdLineArgs::init(argc, argv, &about);
  KCmdLineArgs::addCmdLineOptions(options);

  KApplication app;

  auto window = new MainWindow;
  window->show();

  return app.exec();
}
