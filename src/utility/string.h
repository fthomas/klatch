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

#ifndef UTILITY_STRING_H
#define UTILITY_STRING_H

#include <QChar>
#include <QList>
#include <QString>
#include <QStringList>

QString indent(const QString& str, int count = 2, QChar indent_char = ' ');

QList<QStringList> parse_table(const QString& multiline_str);

QString remove_quotes(const QString& str);

QStringList split_arguments(const QString& str);

QString trimmed_left(const QString& str);

#endif // UTILITY_STRING_H
