#ifndef REPORT_H
#define REPORT_H

#include "route.h"
#include "bin.h"

// Simple report generator
void print_trip_report(const RouteResult *result,const Bin *bins, =int bin_count);

#endif
