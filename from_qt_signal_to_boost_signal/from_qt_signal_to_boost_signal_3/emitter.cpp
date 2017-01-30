#include <iostream>
#include "emitter.h"

void Emitter::DoEmit()
{
  std::clog << "Emitter: emitting signal\n";
  m_signal();
}
