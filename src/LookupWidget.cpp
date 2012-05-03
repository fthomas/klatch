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
#include <QString>
#include <QWidget>
#include <KApplication>
#include <KCmdLineArgs>
#include <KCompletion>
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
}

LookupWidget::~LookupWidget() {
  delete ui_;
}

void LookupWidget::lookupWord(const QString& word) {
  results_->setWord(word);
  if (word.isEmpty()) return;
  // do not call sendMatch if the last word was a prefix of  word
  //if (word.length() >= 3) dict_->sendMatch(word);
  //dict_->sendDefine(word);
}

void LookupWidget::setCompletionItems(const Matches& matches) {
  ui_->word_input->completionObject()->setItems(matches.words());
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

void LookupWidget::createConnections() {
  connect(ui_->word_input, SIGNAL(textChanged(QString)),
    this, SLOT(lookupWord(QString)));

  //connect(dict_, SIGNAL(definitionReceived(Definition)),
  //  results_, SLOT(appendResult(Definition)));

  //connect(dict_, SIGNAL(matchesReceived(Matches)),
  //  this, SLOT(setCompletionItems(Matches)));
}

void LookupWidget::initWordInput() {
  ui_->word_input->setMaxLength(DictClient::maxLineLength());
  ui_->word_input->setText(getInitialWord());
  ui_->word_input->selectAll();
}

void LookupWidget::initResultView() {
  ui_->result_view->setModel(results_);
}

QString LookupWidget::getInitialWord() {
  const auto args = KCmdLineArgs::parsedArgs();

  const auto retval = (args->count()) ? args->arg(0)
    : KApplication::clipboard()->text(QClipboard::Selection);

  return retval.trimmed();
}
