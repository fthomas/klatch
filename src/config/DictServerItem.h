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

#ifndef CONFIG_DICTSERVERITEM_H
#define CONFIG_DICTSERVERITEM_H

#include <QString>
#include <QtGlobal>
#include <KConfigGroup>
#include "dict/DictClient.h"

class DictServerItem {
 public:
  explicit DictServerItem(KConfigGroup group);
  explicit DictServerItem(const QString& hostname = "localhost",
                          quint16 port = DictClient::defaultPort());

  KConfigGroup configGroup() const;
  void setConfigGroup(KConfigGroup group);
  void readConfigGroup();

  QString hostName() const;
  void setHostName(const QString& name);

  quint16 port() const;
  void setPort(quint16 port);

  static bool lessByHostName(
    const DictServerItem& a, const DictServerItem& b);
  static bool greaterByHostName(
    const DictServerItem& a, const DictServerItem& b);

  static bool lessByPort(
    const DictServerItem& a, const DictServerItem& b);
  static bool greaterByPort(
    const DictServerItem& a, const DictServerItem& b);

 private:
  KConfigGroup group_;

  QString hostname_;
  QString hostname_key_ = "Hostname";

  quint16 port_;
  QString port_key_ = "Port";
};

#endif // CONFIG_DICTSERVERITEM_H
