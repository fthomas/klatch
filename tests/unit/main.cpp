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

#include <cstdlib>
#include <QCoreApplication>
#include <QtTest/QtTest>
#include "dict/DatabaseInfo_t.h"
#include "dict/Matches_t.h"
#include "utility/string_t.h"

int g_argc;
char** g_argv;

template<class TestClass>
void exec() {
  TestClass test;
  const int retval = QTest::qExec(&test, g_argc, g_argv);

  if (retval != 0) {
    std::exit(EXIT_FAILURE);
  }
}

int main(int argc, char* argv[]) {
  g_argc = argc;
  g_argv = argv;

  QCoreApplication app{argc, argv};
  exec<test_DatabaseInfo>();
  exec<test_Matches>();
  exec<test_string>();

  std::exit(EXIT_SUCCESS);
}
