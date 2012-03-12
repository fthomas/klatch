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

#include "config/DictServerItem_t.h"
#include <QCoreApplication>
#include <QtTest/QtTest>
#include <KConfig>
#include <KConfigGroup>
#include "config/DictServerItem.h"

void test_DictServerItem::initTestCase() {
  rcfile_ = QCoreApplication::applicationDirPath()
    + "/test_DictServerItem.rc";
  QFile::remove(rcfile_);
}

void test_DictServerItem::test_setConfigGroup() {
  KConfig config{rcfile_, KConfig::SimpleConfig};
  KConfigGroup group = config.group("Server0");

  DictServerItem item{"test0", 4711};
  item.setConfigGroup(group);

  QCOMPARE(group.readEntry("Hostname"), QString{"test0"});
  QCOMPARE(group.readEntry("Port"), QString{"4711"});
}

void test_DictServerItem::test_readConfigGroup() {
  KConfig config{rcfile_, KConfig::SimpleConfig};
  KConfigGroup group = config.group("Server1");

  group.writeEntry("Hostname", "test1");
  group.writeEntry("Port", 1234);

  DictServerItem item{group};
  QCOMPARE(item.hostName(), QString{"test1"});
  QCOMPARE(item.port(), quint16{1234});
}

void test_DictServerItem::test_setters() {
  KConfig config{rcfile_, KConfig::SimpleConfig};
  KConfigGroup group = config.group("Server2");

  DictServerItem item{group};
  item.setHostName("test2");
  item.setPort(2001);

  QCOMPARE(item.hostName(), QString{"test2"});
  QCOMPARE(group.readEntry("Hostname"), QString{"test2"});

  QCOMPARE(item.port(), quint16{2001});
  QCOMPARE(group.readEntry("Port"), QString{"2001"});
}
