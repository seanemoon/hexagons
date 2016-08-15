#include "hex/axial_grid.h"

namespace hex {


const AxialGrid::Coord AxialGrid::kEast {1, 0};
const AxialGrid::Coord AxialGrid::kNorthEast {0, 1};
const AxialGrid::Coord AxialGrid::kNorthWest {-1, 1};
const AxialGrid::Coord AxialGrid::kWest {-1, 0};
const AxialGrid::Coord AxialGrid::kSouthWest {0, -1};
const AxialGrid::Coord AxialGrid::kSouthEast {1, -1};
const std::vector<AxialGrid::Coord> AxialGrid::kDirections {
    kEast, kNorthEast, kNorthWest, kWest, kSouthWest, kSouthEast
};

AxialGrid::AxialGrid(int radius, double scale) {
  radius -= 1;
  for (int i {0}; i <= 2*radius; ++i) {
    int row = i - radius;
    int col_min = std::max(-i, -radius);
    int col_max = std::min(2*radius - i, radius);
    for (int col {col_min}; col <= col_max; ++col) {
      AxialCoord<int> axial_coord(row, col);
      PixelCoord pixel_coord(axial_coord);
      pixel_coord *= scale;
      data_[axial_coord].reset(new Hexagon(pixel_coord, scale));
      data_[axial_coord]->SetColor(0x7F, 0x7F, 0x7F);
    }
  }
}

std::vector<AxialGrid::CoordHexagonPair> AxialGrid::Neighbors(
    AxialCoord<T> coord) {
  std::vector<CoordHexagonPair> neighbors;
  for (Coord direction : kDirections) {
    auto it = data_.find(coord + direction);
    if (it != data_.end()) {
      neighbors.emplace_back(it->first, it->second.get());
    }
  }
  return neighbors;
}


}  // namespace hex
