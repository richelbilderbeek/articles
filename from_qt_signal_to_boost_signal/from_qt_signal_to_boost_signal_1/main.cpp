#include <iostream>
#include <QObject>

class QtEmitter : public QObject
{
  Q_OBJECT
public:
  void DoEmit()
  {
    std::clog << "QtEmitter: emitting signal\n";
    emit signal_emit();
  }
signals:
  void signal_emit();
};

class QtReceiver : public QObject
{
  Q_OBJECT
public slots:
  void OnReceive()
  {
    std::clog << "QtReceiver: received signal\n";
  }
};

int main()
{
  //Create emitter
  QtEmitter e;
  //Create receiver
  QtReceiver r;
  //Connect emitter's signal to receiver
  QObject::connect(&e,SIGNAL(signal_emit()),&r,SLOT(OnReceive()));
  //Let emitter emit its signal
  e.DoEmit();
}
