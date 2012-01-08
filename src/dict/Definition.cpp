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

#include "dict/Definition.h"
#include <QString>
#include "utility/string.h"

Definition::Definition(const QString& status, const QString& text) {
  parseStatusLine(status);
  text_ = text;
}

QString Definition::word() const {
  return word_;
}

QString Definition::database() const {
  return database_;
}

QString Definition::databaseDescription() const {
  return db_description_;
}

QString Definition::text() const {
  return text_;
}

void Definition::parseStatusLine(QString line) {
  word_ = remove_quotes(cut_section(line, ' '));
  database_ = remove_quotes(cut_section(line, ' '));
  db_description_ = remove_quotes(line.trimmed());
}
