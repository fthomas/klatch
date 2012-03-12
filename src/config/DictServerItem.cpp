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

#include "config/DictServerItem.h"
#include <QString>
#include <QtGlobal>
#include <KConfigGroup>
#include "dict/DictClient.h"


DictServerItem::DictServerItem(const QString& hostname, quint16 port)
    : hostname_{hostname}, port_{port} {
}

DictServerItem::DictServerItem(KConfigGroup group) : group_{group} {
  readConfigGroup();
}

KConfigGroup DictServerItem::configGroup() const {
  return group_;
}

void DictServerItem::setConfigGroup(KConfigGroup group) {
  group_ = group;
  setHostName(hostname_);
  setPort(port_);
}

void DictServerItem::readConfigGroup() {
  hostname_ = group_.readEntry(hostname_key_, QString{});
  port_ = group_.readEntry(port_key_, int{DictClient::defaultPort()});
}

QString DictServerItem::hostName() const {
  return hostname_;
}

void DictServerItem::setHostName(const QString& name) {
  hostname_ = name;
  if (group_.isValid()) {
    group_.writeEntry(hostname_key_, hostname_);
    group_.sync();
  }
}

quint16 DictServerItem::port() const {
  return port_;
}

void DictServerItem::setPort(quint16 port) {
  port_ = port;
  if (group_.isValid()) {
    group_.writeEntry(port_key_, int{port_});
    group_.sync();
  }
}
