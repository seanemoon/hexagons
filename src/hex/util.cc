#include "hex/util.h"
#include "hex/coords.h"

#include <cstdlib>

namespace hex {
namespace util {

std::vector<Hexagon> CreateHexagonalGrid(int radius, double scale) {
  radius -= 1;
  std::vector<Hexagon> hexagons;
  for (int i {0}; i <= 2*radius; ++i) {
    int row = i - radius;
    int col_min = std::max(-i, -radius);
    int col_max = std::min(2*radius - i, radius);
    for (int col {col_min}; col <= col_max; ++col) {
      AxialCoord<int> axial_coord(row, col);
      PixelCoord pixel_coord(axial_coord);
      pixel_coord *= scale;
      hexagons.emplace_back(pixel_coord, scale);
      hexagons.back().SetColor(
          fabs(pixel_coord.x*pixel_coord.y)/2.0*0xFF,
          fabs(pixel_coord.x-pixel_coord.y)/2.0*0xFF,
          fabs(pixel_coord.x+pixel_coord.y)/2.0*0xFF);
    }
  }
  return hexagons;
}

}  // namespace util
}  // namespace hex
