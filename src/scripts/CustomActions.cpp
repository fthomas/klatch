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

#include "scripts/CustomActions.h"
#include <QDebug>
#include <QFile>
#include <QScriptValue>
#include <QString>
#include <QStringList>
#include <KGlobal>
#include <KLocalizedString>
#include <KMessageBox>
#include <KStandardDirs>

CustomActions::CustomActions() {
  loadAllScripts();
}

const CustomActions::map_type &CustomActions::actions() const {
  return actions_;
}

void CustomActions::loadAllScripts() {
  QStringList filenames = KGlobal::dirs()->
    findAllResources("appdata", "*.js", KStandardDirs::Recursive);

  for (const QString& filename : filenames) {
    loadScript(filename);
  }
}

bool CustomActions::loadScript(const QString& filename) {
  QFile file{filename};
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning() << file.errorString() << filename;
    return false;
  }

  const QString content = file.readAll();
  file.close();

  QScriptContext* const context = engine_.pushContext();
  engine_.evaluate(content, filename);
  engine_.popContext();

  if (engine_.hasUncaughtException()) {
    const QString exception = engine_.uncaughtException().toString();
    const QString backtrace =
      engine_.uncaughtExceptionBacktrace().join("\n");

    qWarning() << exception;
    qWarning() << backtrace;
    KMessageBox::error(0, exception + "\n" + backtrace,
      ki18n("Qt Script Exception").toString());
    return false;
  }

  insertActions(context->activationObject());
  return true;
}

void CustomActions::insertActions(const QScriptValue& script) {
  const auto insert = [&](const QScriptValue& action) {
    if (!action.isObject()) {
      return;
    }

    const QString text = action.property("text").toString();
    if (text.isEmpty()) {
      return;
    }

    actions_.insert(text, action);
  };

  insert(script.property("action"));

  const QScriptValue actions = script.property("actions");
  if (actions.isArray()) {
    for (int i = 0; i < actions.property("length").toInt32(); ++i) {
      insert(actions.property(i));
    }
  }
}
