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

#ifndef DICT_ABSTRACTDICTCLIENT_H
#define DICT_ABSTRACTDICTCLIENT_H

#include <QObject>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class Definition;
class Matches;

class AbstractDictClient : public QObject {
  Q_OBJECT

 public:
  explicit AbstractDictClient(QObject* parent = 0);

 signals:
  void definitionReceived(const Definition& def);
  void matchesReceived(const Matches& matches);

 public slots:
  virtual void sendDefine(const QString& word,
                          const QString& database = "*") = 0;
  virtual void sendMatch(const QString& word,
                         const QString& strategy = "prefix",
                         const QString& database = "*") = 0;
};

#endif // DICT_ABSTRACTDICTCLIENT_H
