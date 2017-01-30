#ifndef QTEMITTER_H
#define QTEMITTER_H

#include <QObject>

class QtEmitter : public QObject
{
  Q_OBJECT
public:
  void DoEmit();
signals:
  void signal_emit();
};

#endif // QTEMITTER_H
