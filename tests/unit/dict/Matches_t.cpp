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

#include "dict/Matches_t.h"
#include <QString>
#include <QStringList>
#include <QtTest/QtTest>
#include "dict/Matches.h"

using QTest::addColumn;
using QTest::newRow;

void test_Matches::test_words() {
  QFETCH(QString, input);
  QFETCH(QStringList, result);

  QCOMPARE(Matches{input}.words(), result);
}

void test_Matches::test_words_data() {
  addColumn<QString>("input");
  addColumn<QStringList>("result");

  newRow("no matches") << ""
    << QStringList{};
  newRow("one match") << "key0 value0"
    << (QStringList{} << "value0");
  newRow("two matches") << " \n key0 value0 \n key1 value1 \n "
    << (QStringList{} << "value0" << "value1");
}

void test_Matches::test_isEmpty() {
  Matches matches0;
  QVERIFY(matches0.isEmpty());

  Matches matches1{""};
  QVERIFY(matches1.isEmpty());

  Matches matches2{"test"};
  QVERIFY(matches2.isEmpty());

  Matches matches3{"test test"};
  QVERIFY(!matches3.isEmpty());
}
