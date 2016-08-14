#ifndef HEX_UTIL_H_
#define HEX_UTIL_H_

#include "hex/hexagon.h"

#include <vector>

namespace hex {
namespace util {

// Creates and returns a hexagon-shaped grid of hexagons.
// `radius` is the the maximum number of hexagons contained in a line drawn
// from the center of the grid to any edge in the grid.
// `scale` is the maximal radius (R) of each hexagon in the grid.
std::vector<Hexagon> CreateHexagonalGrid(int radius, double scale);

}  // namespace util
}  // namespace hex

#endif  // HEX_UTIL_H_
