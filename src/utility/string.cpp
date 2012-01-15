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

#include "utility/string.h"
#include <QChar>
#include <QString>

QString left_trimmed(const QString& str) {
  QString retval = str;
  while (retval.length() > 0 && retval.at(0).isSpace()) {
    retval.remove(0, 1);
  }
  return retval;
}

QString cut_section(QString& str, QChar sep) {
  while (str.startsWith(sep)) str.remove(0, 1);

  const int section_length = str.indexOf(sep);
  const QString section = str.left(section_length);

  if (!section.isEmpty()) str.remove(0, section_length);
  return section;
}

QString remove_quotes(const QString& str) {
  static const auto remove_enclosing = [](QChar c, QString& s) {
    if (s.startsWith(c) && s.endsWith(c)) {
      s.remove(0, 1);
      s.chop(1);
    }
  };

  QString retval = str;
  remove_enclosing('"', retval);
  remove_enclosing('\'', retval);
  return retval;
}
