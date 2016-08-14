#ifndef HEX_UTIL_H_
#define HEX_UTIL_H_

#include "hex/hexagon.h"

#include <vector>

namespace hex {
namespace util {

std::vector<Hexagon> CreateHexagonalGrid(int radius, double scale);

}  // namespace util
}  // namespace hex

#endif  // HEX_UTIL_H_
