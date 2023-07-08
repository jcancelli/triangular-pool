#ifndef UTIL_LISTENERS_INL
#define UTIL_LISTENERS_INL

#include "listeners.hpp"

namespace pool {

namespace util {

template <class... T>
unsigned Listeners<T...>::add(Listener const& listener) {
  unsigned id = m_NextID++;
  m_Listeners[id] = listener;
  return id;
}

template <class... T>
void Listeners<T...>::remove(unsigned listenerID) {
  auto pos = m_Listeners.find(listenerID);
  if (pos != m_Listeners.end()) {
    m_Listeners.erase(pos);
  }
}

template <class... T>
void Listeners<T...>::notify(T... values) const {
  for (auto const& [listenerID, listener] : m_Listeners) {
    listener(values...);
  }
}

}  // namespace util

}  // namespace pool

#endif