#include "life.h"

#include <random>

namespace algo {
namespace life {


Rules::Rules(std::unordered_set<uint> born, std::unordered_set<uint> survive)
  : born_{born}, survive_{survive} {}

bool Rules::WillLive(Cell* cell, uint num_neighbors_alive) {
  if (cell->alive) {
    return survive_.count(num_neighbors_alive) != 0;
  } else {
    return born_.count(num_neighbors_alive) != 0;
  }
}

Simulation::Simulation(int radius, Rules rules)
  : grid_{radius}, rules_{rules} {
  float size = 0.025f;  // TODO(seanemoon): better solution.
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  for (auto& coord_cell : grid_.Data()) {
    hex::PixelCoord pixel_coord(coord_cell.first);
    pixel_coord *= size;
    bool alive {dist(mt) > 0.3};
    coord_cell.second->alive = alive;
    if (alive) {
      coord_cell.second->hexagon.SetColor(0xFF, 0x7F, 0x7F);
    } else {
      coord_cell.second->hexagon.SetColor(0x7F, 0x7F, 0x7F);
    }
    coord_cell.second->hexagon.SetPixelCoord(pixel_coord);
    coord_cell.second->hexagon.SetSize(size);
  }
}

void Simulation::Step() {
  // Determine which cells will live in the next step.
  for (auto& curr : grid_.Data()) {
    uint num_alive = 0;
    for (auto& neighbor : grid_.Neighbors(curr.first)) {
      if (neighbor.second->alive) ++num_alive;
    }
    curr.second->will_live = rules_.WillLive(curr.second.get(), num_alive);
  }

  // Set which cells are alive.
  for (auto& curr : grid_.Data()) {
    curr.second->alive = curr.second->will_live;
    if (curr.second->alive) {
      curr.second->hexagon.SetColor(0xFF, 0x7F, 0x7F);
    } else {
      curr.second->hexagon.SetColor(0x7F, 0x7F, 0x7F);
    }
  }
}

void Simulation::Render(
    mgl::VertexAttribute* position, mgl::VertexAttribute *color) {
  for (auto& curr : grid_.Data()) {
    curr.second->hexagon.Render(position, color);
  }
}

}  // namespace life
}  // namespace algo
