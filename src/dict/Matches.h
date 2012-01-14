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

#ifndef DICT_MATCHES_H
#define DICT_MATCHES_H

#include <QMultiMap>
#include <QString>
#include <QStringList>

class Matches {
 public:
  Matches(const QString& status, const QString& text);

  QStringList words() const;

 private:
  void parseStatusLine(const QString& line);
  void parseText(const QString& text);

 private:
  int count_ = 0;
  QMultiMap<QString, QString> matches_;
};

#endif // DICT_MATCHES_H
