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

#ifndef CONFIG_DICTSERVERDIALOG_H
#define CONFIG_DICTSERVERDIALOG_H

#include <QObject>
#include <QSize>
#include <QtGlobal>
#include <KDialog>
#include "ui_DictServerDialog.h"

QT_BEGIN_NAMESPACE
class QEvent;
class QString;
class QWidget;
QT_END_NAMESPACE

class DictServerItem;

class DictServerDialog : public KDialog {
  Q_OBJECT

 public:
  explicit DictServerDialog(QWidget* parent = 0);
  ~DictServerDialog();

  void readServerItem(const DictServerItem& server);
  void writeServerItem(DictServerItem& server) const;

  QSize sizeHint() const;

 protected:
  void changeEvent(QEvent* event);

 private slots:
  void hostNameChangedSlot(const QString& hostname);

 private:
  Ui::DictServerDialog ui_;
};

#endif // CONFIG_DICTSERVERDIALOG_H
