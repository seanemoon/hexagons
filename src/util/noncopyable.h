#ifndef UTIL_NONCOPYABLE_H_
#define UTIL_NONCOPYABLE_H_

namespace util {

class NonCopyable {
 protected:
  NonCopyable() = default;
  ~NonCopyable() = default;

  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;
};

}  // namespace util

#endif // UTIL_NONCOPYABLE_H_
