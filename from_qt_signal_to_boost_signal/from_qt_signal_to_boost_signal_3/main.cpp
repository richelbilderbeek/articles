#include "emitter.h"
#include "receiver.h"

int main()
{
  //Create emitter
  Emitter e;
  //Create receiver
  Receiver r;
  //Connect emitter's signal to receiver
  e.m_signal.connect(
    boost::bind(
      &Receiver::OnReceive,
      r));
  //Let emitter emit its signal
  e.DoEmit();
}
