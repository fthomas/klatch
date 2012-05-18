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

#ifndef CONFIG_DICTPAGE_H
#define CONFIG_DICTPAGE_H

#include <QModelIndex>
#include <QObject>
#include <QWidget>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QEvent;
class QItemSelection;
class QItemSelectionModel;
QT_END_NAMESPACE

namespace Ui {
  class DictPage;
}

class DictServerList;

class DictPage : public QWidget {
  Q_OBJECT

 public:
  explicit DictPage(DictServerList* list, QWidget* parent = 0);
  ~DictPage();

 protected:
  void changeEvent(QEvent* event);

 private slots:
  void updateButtons(const QItemSelection& selected);

  void addServer();
  void modifyServer();
  void removeServer();

 private:
  QModelIndex selectedIndex() const;
  void createConnections();

 private:
  Ui::DictPage* ui_;
  DictServerList* const server_list_;
  QItemSelectionModel* server_selection_;
};

#endif // CONFIG_DICTPAGE_H
