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
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;

  int rowCount(const QModelIndex& parent = QModelIndex{}) const;
  int columnCount(const QModelIndex& parent = QModelIndex{}) const;

  bool insertRow(const DictServerItem& server);

 private:
  void readConfig();
  QString newSubgroupName() const;

 private:
  KConfig* config_;
  QList<DictServerItem> servers_;

  const QString dict_name_ = "Dict";
  const QString server_prefix_ = "Server";
};

#endif // CONFIG_DICTSERVERLIST_H
