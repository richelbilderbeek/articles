#include "qtemitter.h"
#include "qtreceiver.h"

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
