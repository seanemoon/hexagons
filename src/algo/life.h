#ifndef ALGO_LIFE_H_
#define ALGO_LIFE_H_

#include "hex/axial_grid.h"

#include <unordered_set>

namespace algo {
namespace life {

struct Cell {
  Cell() : hexagon{}, alive{false}, will_live{false} {}

  // A renderable hexagon.
  hex::Hexagon hexagon;

  // True iff the cell is alive in the current step.
  bool alive;

  // True iff the cell should live in the next step.
  bool will_live;
};


// Specifies the update rules for the game of life.
class Rules {
 public:
  Rules(std::unordered_set<uint> born, std::unordered_set<uint> survive);

  // Returns true iff `cell` will be alive in the next step given it has
  // `num_neighbors_alive` neighbors which are currently alive.
  bool WillLive(Cell* cell, uint num_neighbors_alive);

 private:
  // If a cell is dead and the number of living neighbors is in the set
  // `born_`, then the cell will be alive in the next step.
  std::unordered_set<uint> born_;

  // If a cell is alive and and the number of living neighbors in the set
  // `survive_`, then the cell will be alive in the next step.
  std::unordered_set<uint> survive_;
};


class Simulation {
 public:
  // Constructs a new random simulation.
  // `radius` is the radius of the AxialGrid that the simulation will play on.
  // `rules` are the rules defining the update steps of the simulation.
  Simulation(int radius, Rules rules);

  // Updates simulation one step.
  void Step();

  // Renders the current state of the simulation to the screen.
  void Render(mgl::VertexAttribute* position, mgl::VertexAttribute *color);

 private:
  // The Cell data for this simulation.
  hex::AxialGrid<Cell> grid_;

  // The rules defining the update steps of the simulation.
  Rules rules_;
};

}  // namespace life
}  // namespace algo

#endif  // ALGO_LIFE_H_
