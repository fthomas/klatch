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

#include "dict/Matches.h"
#include <QString>
#include <QStringList>
#include "utility/string.h"

Matches::Matches(const QString& status, const QString& text) {
  parseStatusLine(status);
  parseText(text);
}

QStringList Matches::words() const {
  return matches_.values();
}

void Matches::parseStatusLine(const QString& line) {
  count_ = line.section(' ', 0, 0).toInt();
}

void Matches::parseText(const QString& text) {
  const QStringList lines = text.split("\r\n", QString::SkipEmptyParts);
  foreach (const QString line, lines) {
    const QStringList args = split_arguments(line);

    if (args.size() >= 2) {
      matches_.insert(args.at(0), args.at(1));
    }
  }
}
