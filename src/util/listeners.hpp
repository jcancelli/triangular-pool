#ifndef UTIL_LISTENERS_HPP
#define UTIL_LISTENERS_HPP

#include <functional>
#include <map>
#include <type_traits>

namespace pool {

namespace util {

template <class... T>
class Listeners {
 public:
  using Listener = std::function<void(T...)>;

 private:
  unsigned m_NextID;
  std::map<unsigned, Listener> m_Listeners;

 public:
  unsigned add(Listener const& listener);
  void remove(unsigned listenerID);
  void notify(T... values) const;
};

}  // namespace util

}  // namespace pool

#include "listeners.inl"

#endif