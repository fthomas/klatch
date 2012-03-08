#ifndef DICT_CLIENTPOOL_H
#define DICT_CLIENTPOOL_H

#include <QObject>

class DictClient;

class ClientPool : public QObject {
  Q_OBJECT

 public:
  explicit ClientPool(QObject* parent = 0);
};

#endif // DICT_CLIENTPOOL_H
