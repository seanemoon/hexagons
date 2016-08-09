#ifndef UTIL_MANAGED_
#define UTIL_MANAGED_

#include <functional>

namespace util {

template <typename T>
class Managed {
 public:
  Managed(T obj, std::function<void(T)> deleter)
   : obj_{obj},  deleter_{deleter} {}
  ~Managed() { deleter_(obj_); }
  T get() { return obj_; }

 private:
  T obj_;
  std::function<void(T)> deleter_;
};

}  // namespace util

#endif  // UTIL_MANAGED_
