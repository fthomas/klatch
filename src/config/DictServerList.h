#ifndef CONFIG_DICTSERVERLIST_H
#define CONFIG_DICTSERVERLIST_H

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QObject>
#include <QVariant>
#include <Qt>
#include "config/DictServerItem.h"

class KConfig;

class DictServerList : public QAbstractListModel {
  Q_OBJECT

 public:
  explicit DictServerList(KConfig* config, QObject* parent = 0);

  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  int rowCount(const QModelIndex& parent = QModelIndex{}) const;
  int columnCount(const QModelIndex& parent = QModelIndex{}) const;

 private:
  void readConfig();

 private:
  KConfig* config_;
  QList<DictServerItem> servers_;
};

#endif // CONFIG_DICTSERVERLIST_H
