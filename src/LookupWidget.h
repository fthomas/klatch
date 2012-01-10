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

#ifndef LOOKUPWIDGET_H
#define LOOKUPWIDGET_H

#include <QObject>
#include <QString>
#include <QWidget>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QEvent;
QT_END_NAMESPACE

namespace Ui {
  class LookupWidget;
}

class LookupWidget : public QWidget {
  Q_OBJECT

 public:
  explicit LookupWidget(QWidget* parent = 0);
  ~LookupWidget();

 protected:
  void changeEvent(QEvent* event);

 private:
  static QString getInitialWord();

 private:
  Ui::LookupWidget* ui_;
};

#endif // LOOKUPWIDGET_H