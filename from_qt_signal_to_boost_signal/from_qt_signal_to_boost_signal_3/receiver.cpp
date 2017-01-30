#include <iostream>
#include "receiver.h"

void Receiver::OnReceive()
{
  std::clog << "Receiver: received signal\n";
}

