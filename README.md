# Smart Waste Collection Route Optimizer

## Project Description
This project implements a greedy route optimizer for smart waste collection trucks. The system selects bins based on fill level and proximity, minimizing travel distance while prioritizing high-fill bins.

## Problem Summary
Given N waste bins with coordinates, fill levels, and priorities, find an efficient collection route using a nearest-full-bin greedy algorithm starting from a depot.

## Project Structure

### Core Files
- **bin.c / bin.h** – Main program entry point and bin management logic
- **route.c / route.h** – Route optimization and greedy selection algorithms
- **config.h** – Configuration constants and tunable parameters
- **report.h** – Structures and utilities for generating route reports

## Build Instructions

### Prerequisites
- C compiler (gcc, clang, or equivalent)
- Standard C library

### Compilation
```bash
gcc -Wall -Wextra -O2 -std=c11 -o route_optimizer bin.c route.c -I.
```

For debugging, use:
```bash
gcc -Wall -Wextra -g -std=c11 -o route_optimizer bin.c route.c -I.
```

## Configuration

Edit `config.h` to adjust:
- Bin capacity thresholds
- Proximity distance calculations
- Priority weighting factors
- Maximum route distance or stops

## Usage

```bash
./route_optimizer [input_file]
```

The program reads bin data (coordinates, fill levels, priorities) and outputs an optimized collection route.

## Algorithm Overview

The optimizer uses a greedy nearest-full-bin approach:
1. Start at the depot (origin)
2. Identify all bins meeting fill-level threshold
3. Select the nearest qualifying bin
4. Add to route and update truck position
5. Repeat until all priority bins serviced or constraints reached

## Testing

Create test data files with bin specifications:
```
x y fill_level priority
0 0 85 1
10 5 72 0
15 20 90 1
```

Run the optimizer and verify route feasibility and distance minimization.

## Future Enhancements

- Multi-objective optimization (distance + time)
- Dynamic priority adjustment based on real-time fill data
- Support for multiple truck fleets
- Integration with IoT bin sensors
- Web API for route updates

## Author
Krishna Gopal Rathore,Aradhy Mishra,KUNAL SINGH,AYUSH KUMAR MISHRA

## License
[Add license information here - e.g., MIT, Apache 2.0]

---

For questions or contributions, please open an issue or pull request.
