#ifndef HEX_AXIAL_GRID_H_
#define HEX_AXIAL_GRID_H_

#include "hex/coords.h"
#include "hex/hexagon.h"

#include <unordered_map>
#include <memory>

namespace hex {

using Coord = AxialCoord<int>;

namespace AxialDirection {

// Directional constants.
const Coord kEast {1, 0};
const Coord kNorthEast {0, 1};
const Coord kNorthWest {-1, 1};
const Coord kWest {-1, 0};
const Coord kSouthWest {0, -1};
const Coord kSouthEast {1, -1};
const std::vector<Coord> kAll {
    kEast, kNorthEast, kNorthWest, kWest, kSouthWest, kSouthEast
};

}  // namespace AxialDirection

// Responsible for organizing hexagons in a grid using axial coordinates.
// Supports things like look-up by coordinate and querying for neighbors.
template<typename T>
class AxialGrid {
 public:
  // Who doesn't like readability?
  using CoordDataMap = std::unordered_map<Coord, std::unique_ptr<T>>;
  using CoordDataPair = std::pair<const Coord, T*>;

  // Constructs a hexagonal axial grid.
  // `radius` is the the maximum number of hexagons contained in a line drawn
  // from the center of the grid to any edge in the grid.
  AxialGrid(int radius) {
    for (int i {0}; i <= 2*radius; ++i) {
      int row = i - radius;
      int col_min = std::max(-i, -radius);
      int col_max = std::min(2*radius - i, radius);
      for (int col {col_min}; col <= col_max; ++col) {
        AxialCoord<int> axial_coord(row, col);
        data_[axial_coord].reset(new T());
      }
    }
  }

  // Return the hexagons neighboring `coord`.
  std::vector<CoordDataPair> Neighbors(Coord coord) {
    std::vector<CoordDataPair> neighbors;
    for (Coord direction : AxialDirection::kAll) {
      auto it = data_.find(coord + direction);
      if (it != data_.end()) {
        neighbors.emplace_back(it->first, it->second.get());
      }
    }
    return neighbors;
  }

  // Return the underlying data for this grid.
  CoordDataMap& Data() { return data_; }

 private:
  int radius_;
  CoordDataMap data_;
};


}  // namespace hex


#endif  // HEX_AXIAL_GRID_H_
