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

#ifndef SCRIPTS_CUSTOMACTIONS_H
#define SCRIPTS_CUSTOMACTIONS_H

#include <QList>
#include <QMap>
#include <QScriptEngine>
#include <QScriptValue>
#include <QString>
#include "dict/Definition.h"

class CustomActions {
 public:
  typedef QMap<QString, QScriptValue> map_type;

 public:
  CustomActions();

  const map_type& actions() const;
  void setResults(const QList<Definition>& definitions);
  void runAction(const QString& key);

 private:
  void loadAllScripts();
  bool loadScript(const QString& filename);
  void insertActions(const QScriptValue& script);

 private:
  QScriptEngine engine_;
  map_type actions_;
};

#endif // SCRIPTS_CUSTOMACTIONS_H
