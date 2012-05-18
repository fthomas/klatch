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

#ifndef DICT_DEFINITION_H
#define DICT_DEFINITION_H

#include <QMetaType>
#include <QScriptValue>
#include <QString>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QScriptEngine;
QT_END_NAMESPACE

class Definition {
 public:
  Definition();
  Definition(const QString& status, const QString& text);

  QString word() const;
  QString database() const;
  QString databaseDescription() const;
  QString text() const;

  bool isEmpty() const;

  static QScriptValue toScriptValue(QScriptEngine* engine,
                                    const Definition& def);
  static void fromScriptValue(const QScriptValue& obj, Definition& def);

 private:
  void parseStatusLine(const QString& line);

 private:
  QString word_;
  QString database_;
  QString db_description_;
  QString text_;
  bool empty_ = true;
};

Q_DECLARE_METATYPE(Definition)

#endif // DICT_DEFINITION_H
