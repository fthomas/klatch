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

#include "utility/string_t.h"
#include <QList>
#include <QString>
#include <QStringList>
#include <QtTest/QtTest>
#include "utility/string.h"

using QTest::addColumn;
using QTest::newRow;

Q_DECLARE_METATYPE(QList<QStringList>)

void test_string::test_parse_table() {
  QFETCH(QString, input);
  QFETCH(QList<QStringList>, result);

  QCOMPARE(parse_table(input), result);
}

void test_string::test_parse_table_data() {
  addColumn<QString>("input");
  addColumn<QList<QStringList>>("result");

  newRow("empty input") << "" << QList<QStringList>();

  newRow("one cell") << "A"
    << (QList<QStringList>() << (QStringList() << "A"));
  newRow("three cells") << "A B C"
    << (QList<QStringList>() << (QStringList() << "A" << "B" << "C"));

  newRow("two rows") << "A B \n C D"
    << (QList<QStringList>()
      << (QStringList() << "A" << "B")
      << (QStringList() << "C" << "D"));

  newRow("three rows") << "A B \n C D E \n F G H I"
    << (QList<QStringList>()
      << (QStringList() << "A" << "B")
      << (QStringList() << "C" << "D" << "E")
      << (QStringList() << "F" << "G" << "H" << "I"));
}

void test_string::test_split_arguments() {
  QFETCH(QString, input);
  QFETCH(QStringList, result);

  QCOMPARE(split_arguments(input), result);
}

void test_string::test_split_arguments_data() {
  addColumn<QString>("input");
  addColumn<QStringList>("result");

  newRow("one quoted string") << "one two"
    << (QStringList() << "one" << "two");
  newRow("one quoted string") << "'one' two"
    << (QStringList() << "one" << "two");
  newRow("one quoted string") << "\"one\" two"
    << (QStringList() << "one" << "two");

  newRow("two quoted strings") << "\"one\" 'two' 3"
    << (QStringList() << "one" << "two" << "3");
  newRow("two quoted strings") << "one \"two\" '3'"
    << (QStringList() << "one" << "two" << "3");
  newRow("two quoted strings") << "'one' two \"3\""
    << (QStringList() << "one" << "two" << "3");

  newRow("spaces in quotes") << " one \"two 3\""
    << (QStringList() << "one" << "two 3");
  newRow("spaces in quotes") << "\"one two 3\""
    << (QStringList() << "one two 3");
  newRow("spaces in quotes") << " \"one two\"  3  "
    << (QStringList() << "one two" << "3");

  newRow("quotes in quotes") << "\"one 'two'\"  3"
    << (QStringList() << "one 'two'" << "3");
  newRow("quotes in quotes") << "\"'one' 'two'\" 3"
    << (QStringList() << "'one' 'two'" << "3");
  newRow("quotes in quotes") << "\"'one  two'\" 3"
    << (QStringList() << "'one  two'" << "3");

  newRow("escaped sq") << "'one\\'two' 3"
    << (QStringList() << "one\\'two" << "3");
  newRow("escaped dq") << "\"one \\\" two\" 3"
    << (QStringList() << "one \\\" two" << "3");
}

void test_string::test_trimmed_left() {
  QFETCH(QString, input);
  QFETCH(QString, result);

  QCOMPARE(trimmed_left(input), result);
}

void test_string::test_trimmed_left_data() {
  addColumn<QString>("input");
  addColumn<QString>("result");

  newRow("no space") << "test" << "test";
  newRow("one space") << " test" << "test";
  newRow("two spaces") << "  test" << "test";

  newRow("one tab") << "\t test" << "test";
  newRow("two tabs") << "\t\t test" << "test";

  newRow("CR LF") << "\r\n test" << "test";
  newRow("LF CR") << "\n\r test" << "test";

  newRow("one trailing space") << "test " << "test ";
  newRow("two trailing spaces") << "test  " << "test  ";
  newRow("trailing CR LF") << "test\r\n" << "test\r\n";
}
