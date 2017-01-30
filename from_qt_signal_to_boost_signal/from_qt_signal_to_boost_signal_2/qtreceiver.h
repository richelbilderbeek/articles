#ifndef QTRECEIVER_H
#define QTRECEIVER_H

#include <QObject>

class QtReceiver : public QObject
{
  Q_OBJECT
public slots:
  void OnReceive();
};

#endif // QTRECEIVER_H
