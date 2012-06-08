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

#include "LookupWidget.h"
#include <QClipboard>
#include <QEvent>
#include <QMap>
#include <QString>
#include <QWidget>
#include <KApplication>
#include <KCmdLineArgs>
#include <KCompletion>
#include <KLocalizedString>
#include "config/DictServerList.h"
#include "dict/ClientPool.h"
#include "dict/Definition.h"
#include "dict/Matches.h"
#include "results/ResultList.h"
#include "ui_LookupWidget.h"

LookupWidget::LookupWidget(DictServerList* list, QWidget* parent)
    : QWidget{parent},
      ui_{new Ui::LookupWidget},
      client_pool_{new ClientPool{list, this}},
      results_{new ResultList{this}} {
  ui_->setupUi(this);

  createConnections();
  initWordInput();
  initResultView();

  ui_->database_selector->addItem(
    QString{"%1 (*)"}.arg(i18n("All Dictionaries")), "*");
}

LookupWidget::~LookupWidget() {
  delete ui_;
}

void LookupWidget::lookupWord(const QString& word) {
  results_->setWord(word);
  if (word.isEmpty()) return;

  const auto database = selectedDatabase();

  if (word.length() >= 3) client_pool_->sendMatch(word, "prefix", database);
  client_pool_->sendDefine(word, database);
}

void LookupWidget::repeatLookup() {
  results_->setWord(QString{});
  lookupWord(ui_->word_input->text());
}

void LookupWidget::showDatabaseSelector(bool show) {
  ui_->database_selector->setVisible(show);
}

void LookupWidget::changeEvent(QEvent* event) {
  QWidget::changeEvent(event);
  switch (event->type()) {
    case QEvent::LanguageChange:
      ui_->retranslateUi(this);
      break;
    default:
      break;
  }
}

void LookupWidget::setCompletionItems(const Matches& matches) {
  ui_->word_input->completionObject()->setItems(matches.words());
}

void LookupWidget::updateDatabaseSelector() {
  const int rows = ui_->database_selector->model()->rowCount();
  ui_->database_selector->model()->removeRows(1, rows - 1);

  const auto databases = client_pool_->databases();
  QMap<QString, QString> sorted_dbs;

  const auto key_format = QString{"%1 (%2)"};
  for (auto it = databases.begin(); it != databases.end(); ++it) {
    sorted_dbs.insert(key_format.arg(it.value(), it.key()), it.key());
  }

  for (auto it = sorted_dbs.begin(); it != sorted_dbs.end(); ++it) {
    ui_->database_selector->addItem(it.key(), it.value());
  }
}

void LookupWidget::createConnections() {
  connect(ui_->word_input, SIGNAL(textChanged(QString)),
    this, SLOT(lookupWord(QString)));

  connect(ui_->database_selector, SIGNAL(currentIndexChanged(int)),
    this, SLOT(repeatLookup()));

  connect(client_pool_, SIGNAL(definitionReceived(Definition)),
    results_, SLOT(appendResult(Definition)));

  connect(client_pool_, SIGNAL(matchesReceived(Matches)),
    this, SLOT(setCompletionItems(Matches)));

  connect(client_pool_, SIGNAL(databaseListReceived()),
    this, SLOT(updateDatabaseSelector()));
}

void LookupWidget::initWordInput() {
  ui_->word_input->setMaxLength(DictClient::maxLineLength());
  ui_->word_input->setText(getInitialWord());
  ui_->word_input->selectAll();
}

void LookupWidget::initResultView() {
  ui_->result_view->setModel(results_);
}

QString LookupWidget::selectedDatabase() const {
  auto db = ui_->database_selector->itemData(
    ui_->database_selector->currentIndex()).toString();

  if (db.isEmpty()) db = "*";
  return db;
}

QString LookupWidget::getInitialWord() {
  const auto args = KCmdLineArgs::parsedArgs();

  const auto retval = (args->count()) ? args->arg(0)
    : KApplication::clipboard()->text(QClipboard::Selection);

  return retval.trimmed();
}
