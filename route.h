#ifndef ROUTE_H
#define ROUTE_H

#include "bin.h"

// Route ke final result ko store karne ke liye structure
typedef struct {
    double total_distance;
    int bins_serviced;
    double total_time_min;
} RouteResult;

// Nearest-full-bin routing algorithm ka main function
RouteResult run_nearest_full_bin_route(Bin *bins,
                                       int bin_count,
                                       double **distance_matrix,
                                       double depot_x,
                                       double depot_y);

#endif