#ifndef HEX_CONSTANTS_H_
#define HEX_CONSTANTS_H_

#include <cmath>

// We only consider regular hexagons here; any reference to a hexagon is
// implicitly a reference to a regular hexagon. We use the definitions below
// when working with hexagons. We choose to use the maximal radius (R) as the
// base unit. That is, any quantities with unspecified units are assumed to be
// in units of maximal radius (R).
//
// R = maximal radius or circumradius (base unit)
// D = maximal diameter
//   = 2R
// t = side length
//   = R
// r = minimal radius or inradius
//   = cos(pi/6)*R = (sqrt(3)/2)*R
//
//            _-_            ---               ---
//         _-     -_          |                 |
//      _-           -_       |                 |
//    *                 *     | R    ---        |
//    |                 |     |       |         |
//    |                 |     |       |         |
//    |                 |    ---      | t=R     | D=2R
//    |                 |             |         |
//    |                 |             |         |
//    *                 *            ---        |
//      -_           _-                         |
//         -_     _-                            |
//            -_-                              ---
//
//    |--------|
//        r
//
//    |-----------------|
//            d=2r
static const double kMaximalRadius = 1.0;                       // R
static const double kMaximalDiameter = 2.0;                     // D
static const double kSideLength = 1.0;                          // t
static const double kMinimalRadius = std::cos(M_PI/6.0);        // r
static const double kMinimalDiameter = 2.0 * kMinimalRadius;    // d
static const double kVerticalSpacing = 1.5;                     // v
static const double kHorizontalSpacing = kMinimalDiameter;      // h

#endif  // HEX_CONSTANTS_H_
