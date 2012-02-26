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

#include "results/ResultList_t.h"
#include <QtTest/QtTest>
#include "dict/Definition.h"
#include "results/ResultList.h"

void test_ResultList::test_rowCount() {
  ResultList list;
  QCOMPARE(list.rowCount(), 0);

  list.appendResult(Definition{});
  QCOMPARE(list.rowCount(), 1);

  list.appendResult(Definition{});
  QCOMPARE(list.rowCount(), 2);

  list.setWord("test");
  QCOMPARE(list.rowCount(), 0);
}

void test_ResultList::test_setWord() {
  ResultList list;
  QCOMPARE(list.word(), QString{});

  list.setWord("test");
  QCOMPARE(list.word(), QString{"test"});
}

void test_ResultList::test_appendResult() {
  ResultList list;
  QCOMPARE(list.rowCount(), 0);

  list.appendResult(Definition{"word", "text"});
  QCOMPARE(list.rowCount(), 0);

  list.setWord("word");

  list.appendResult(Definition{"word", "text"});
  QCOMPARE(list.rowCount(), 1);

  list.appendResult(Definition{"WORD", "text"});
  QCOMPARE(list.rowCount(), 2);
}
