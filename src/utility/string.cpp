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
#include <QList>
#include <QString>
#include <QStringList>

QString indent(const QString& str, int count, QChar indent_char) {
  QString retval = str;
  const QString prefix = QString{count, indent_char};
  retval.prepend(prefix);
  retval.replace('\n', QString{"\n"} + prefix);
  return retval;
}

QList<QStringList> parse_table(const QString& multiline_str) {
  const QStringList lines =
    multiline_str.split('\n', QString::SkipEmptyParts);

  QList<QStringList> table;
  table.reserve(lines.size());

  for (const QString& line : lines) {
    if (!line.trimmed().isEmpty()) {
      table << split_arguments(line);
    }
  }
  return table;
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

QStringList split_arguments(const QString& str) {
  QStringList retval;

  QChar quote;
  QString arg;
  arg.reserve(str.length());

  for (int i = 0; i < str.length(); ++i) {
    const QChar c = str.at(i);
    const bool escaped = (i > 0) && (str.at(i-1) == '\\');
    const bool opening_quote =
      (c == '"' || c == '\'') && !escaped && quote.isNull();

    if (opening_quote) {
      quote = c;
      continue;
    }

    const bool closing_quote = (c == quote) && !escaped && !quote.isNull();
    const bool unquoted_space = c.isSpace() && quote.isNull();

    if (!closing_quote && !unquoted_space) {
      arg.append(c);
      continue;
    }
    if (arg.length() > 0) {
      retval << arg;

      quote = QChar();
      arg.clear();
    }
  }
  if (arg.length() > 0) retval << arg;
  return retval;
}

QString trimmed_left(const QString& str) {
  QString retval = str;
  while (retval.length() > 0 && retval.at(0).isSpace()) {
    retval.remove(0, 1);
  }
  return retval;
}
