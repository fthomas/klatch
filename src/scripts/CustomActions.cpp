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
#include <QFile>
#include <QList>
#include <QScriptValue>
#include <QString>
#include <QStringList>
#include <KGlobal>
#include <KLocalizedString>
#include <KMessageBox>
#include <KStandardDirs>
#include "dict/Definition.h"

CustomActions::CustomActions() {
  qScriptRegisterMetaType(&engine_,
    Definition::toScriptValue, Definition::fromScriptValue);

  loadAllScripts();
}

const CustomActions::map_type &CustomActions::actions() const {
  return actions_;
}

void CustomActions::setResults(const QList<Definition>& definitions) {
  QScriptValue array = engine_.newArray(definitions.length());

  for (int i = 0; i < definitions.length(); ++i) {
    array.setProperty(i, engine_.toScriptValue(definitions.at(i)));
  }
  engine_.globalObject().setProperty("results", array);
}

bool CustomActions::runAction(const QString& key) {
  if (!actions_.contains(key)) {
    // error
    return false;
  }

  QScriptValue run = actions_.value(key).property("run");
  if (!run.isFunction()) {
    // error
    return false;
  }

  run.call();
  return showScriptException();
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
    // error
    return false;
  }

  const QString content = file.readAll();
  file.close();

  QScriptContext* const context = engine_.pushContext();
  engine_.evaluate(content, filename);
  engine_.popContext();

  if (showScriptException()) return false;

  insertActions(context->activationObject());
  return true;
}

void CustomActions::insertActions(const QScriptValue& script) {
  const auto insert = [&](const QScriptValue& action) {
    if (!action.isObject()) return;

    const QString text = action.property("text").toString();
    if (text.isEmpty()) {
      // error
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

bool CustomActions::showScriptException() const {
  if (!engine_.hasUncaughtException()) return false;

  const QString exception = engine_.uncaughtException().toString();
  const QString backtrace = engine_.uncaughtExceptionBacktrace().join("\n");

  KMessageBox::error(0, exception + "\n" + backtrace,
    ki18n("Qt Script Exception").toString());
  return true;
}
