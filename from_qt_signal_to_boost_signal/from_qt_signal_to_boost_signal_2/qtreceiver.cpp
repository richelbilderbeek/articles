#include <iostream>
#include "qtreceiver.h"

void QtReceiver::OnReceive()
{
  std::clog << "QtReceiver: received signal\n";
}

