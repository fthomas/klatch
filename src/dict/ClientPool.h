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

#ifndef DICT_CLIENTPOOL_H
#define DICT_CLIENTPOOL_H

#include <QObject>

class DictClient;
class DictServerList;



 /*
 - anfragen an den CP werden an clients weitergeleitet und von diesem gesammelt
 - alle clients werden hinter dem CP versteckt
 - wenn ein client not found zurücksendet, schicken wir ein match
 - die ergebnisse und matches werden direkt weitergeleitet
 - reagiere darauf, dass die zu benutzenden server geändert werden
 */



class ClientPool : public QObject {
  Q_OBJECT

 public:
  explicit ClientPool(DictServerList* list, QObject* parent = 0);

 private:
  void createClients();
  void clearClients();

 private:
  DictServerList* const server_list_;
  QList<DictClient*> clients_;
};

#endif // DICT_CLIENTPOOL_H
