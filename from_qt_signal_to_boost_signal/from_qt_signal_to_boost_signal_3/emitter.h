#ifndef EMITTER_H
#define EMITTER_H

#include <boost/signals2.hpp>

struct Emitter
{
  void DoEmit();
  boost::signals2::signal<void ()> m_signal;
};

#endif // EMITTER_H
