#include "hex/util.h"
#include "hex/coords.h"

#include <cstdlib>

namespace hex {
namespace util {

std::vector<Hexagon> CreateHexagonalGrid(int radius, double scale) {
  std::vector<Hexagon> hexagons;
  for (int i {0}; i <= 2*radius; ++i) {
    int row = i - radius;
    int col_min = std::max(-i, -radius);
    int col_max = std::min(2*radius - i, radius);
    for (int col {col_min}; col <= col_max; ++col) {
      AxialCoord<int> axial_coord(col, row);
      PixelCoord pixel_coord(axial_coord);
      double x = pixel_coord.x*scale;
      double y = pixel_coord.y*scale;
      hexagons.emplace_back(x, y, fabs(x)*0xFF, fabs(y)*0xFF, 127, scale);
    }
  }
  return hexagons;
}

}  // namespace util
}  // namespace hex
