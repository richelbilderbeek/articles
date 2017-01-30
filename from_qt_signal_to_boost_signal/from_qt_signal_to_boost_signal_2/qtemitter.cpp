#include <iostream>
#include "qtemitter.h"

void QtEmitter::DoEmit()
{
  std::clog << "QtEmitter: emitting signal\n";
  emit signal_emit();
}
