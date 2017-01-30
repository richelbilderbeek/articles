#include <iostream>
#include <boost/signals2.hpp>

struct Emitter
{
  void DoEmit()
  {
    std::clog << "Emitter: emitting signal\n";
    m_signal();
  }
  boost::signals2::signal<void ()> m_signal;
};

struct Receiver
{
  void OnReceive()
  {
    std::clog << "Receiver: received signal\n";
  }
};

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
      r));  //Let emitter emit its signal
  e.DoEmit();
}
