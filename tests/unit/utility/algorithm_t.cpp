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

#include "utility/algorithm_t.h"
#include <QList>
#include <QtTest/QtTest>
#include "utility/algorithm.h"

void test_algorithm::test_erase_if() {
  QList<int> l1; l1 << 1 << 2 << 3 << 4;

  erase_if(l1, [](int i) { return i > 2; });
  QCOMPARE(l1, (QList<int>{} << 1 << 2));

  erase_if(l1, [](int i) { return i > 0; });
  QCOMPARE(l1, QList<int>{});

  erase_if(l1, [](int i) { return i > 0; });
  QCOMPARE(l1, QList<int>{});
}
