#ifndef HEX_AXIAL_GRID_H_
#define HEX_AXIAL_GRID_H_

#include "hex/coords.h"
#include "hex/hexagon.h"

#include <memory>
#include <unordered_map>

namespace hex {


// Responsible for organizing hexagons in a grid using axial coordinates.
// Supports things like look-up by coordinate and querying for neighbors.
class AxialGrid {
 public:
  // Who doesn't like readability?
  using T = int;
  using Coord = AxialCoord<T>;
  using CoordHexagonMap = std::unordered_map<Coord, std::unique_ptr<Hexagon>>;
  using CoordHexagonPair = std::pair<const Coord, Hexagon*>;

  // Directional constants.
  static const Coord kEast;
  static const Coord kSouthEast;
  static const Coord kSouthWest;
  static const Coord kWest;
  static const Coord kNorthWest;
  static const Coord kNorthEast;
  static const std::vector<Coord> kDirections;

  // Constructs a hexagonal axial grid.
  // `radius` is the the maximum number of hexagons contained in a line drawn
  // from the center of the grid to any edge in the grid.
  // `scale` is the maximal radius (R) of each hexagon in the grid.
  AxialGrid(int radius, double scale);

  // Return the hexagons neighboring `coord`.
  std::vector<CoordHexagonPair> Neighbors(Coord coord);

  // Return the underlying data for this grid.
  CoordHexagonMap& Data() { return data_; }

 private:
  CoordHexagonMap data_;
};


}  // namespace hex


#endif  // HEX_AXIAL_GRID_H_
