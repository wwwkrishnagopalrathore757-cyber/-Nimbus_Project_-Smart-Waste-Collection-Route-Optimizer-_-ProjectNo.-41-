#include <stdio.h>
#include <math.h>
#include "route.h"
#include "config.h"

// Depot se kisi bin tak ka distance (direct calculate kar lenge)
static double depot_to_bin_distance(double depot_x, double depot_y, const Bin *b){
    double dx=b->x-depot_x;
    double dy=b->y-depot_y;
    return sqrt(dx*dx+dy*dy);
}

// Next bin choose karne ka logic
static int choose_next_bin(const Bin *bins,
                           int bin_count,
                           double **distance_matrix,
                           int current_index,
                           int at_depot,
                           double depot_x,
                           double depot_y) {
    int chosen_index=-1;
    double best_distance=0.0;

    for (int i=0;i<bin_count;i++){
        // Agar bin already serviced hai ya full threshold ke neeche hai toh skip
        if (bins[i].serviced) continue;
        if (bins[i].fill_level<FILL_THRESHOLD) continue;

        double dist;
        if (at_depot){
            // Agar abhi depot pe hain toh direct depot-to-bin distance
            dist=depot_to_bin_distance(depot_x,depot_y,&bins[i]);
        } else{
            // Nahi toh distance matrix se current bin se next bin tak ka distance
            dist = distance_matrix[current_index][i];
        }

        // Priority bhi consider kar sakte hain:
        // pehle higher priority, fir distance
        if (chosen_index==-1){
            chosen_index=i;
            best_distanc=dist;
        } else{
            // Priority check: agar naya bin zyada priority ka hai toh le lo
            if (bins[i].priority>bins[chosen_index].priority){
                chosen_index=i;
                best_distance dist;
            } else if (bins[i].priority==bins[chosen_index].priority){
                // Agar priority same hai toh nearest choose karenge
                if (dist<best_distance) {
                    chosen_index=i;
                    best_distance=dist;
                }
            }
        }
    }

    return chosen_index;
}

RouteResult run_nearest_full_bin_route(Bin *bins,
                                       int bin_count,
                                       double **distance_matrix,
                                       double depot_x,
                                       double depot_y) {
    RouteResult result;
    result.total_distance=0.0;
    result.bins_serviced=0;
    result.total_time_min=0.0;

    int current_index=-1; // -1 means abhi depot pe hain
    int at_depot=1;

    while (1){
        int next_index=choose_next_bin(bins,
                                         bin_count,
                                         distance_matrix,
                                         current_index,
                                         at_depot,
                                         depot_x,
                                         depot_y);

        if (next_index==-1){
            // Koi bhi full bin bacha hi nahi jisko collect karna ho
            break;
        }

        double distance_to_next;
        if (at_depot){
            distance_to_next=depot_to_bin_distance(depot_x,depot_y,&bins[next_index]);
        } else {
            distance_to_next=distance_matrix[current_index][next_index];
        }

        // Distance aur time update karte hain
        result.total_distance+=distance_to_next;

        // Time: travel + unloading
        double travel_time_hr=distance_to_next/TRUCK_SPEED;
        double travel_time_min=travel_time_hr*60.0;
        result.total_time_min+=travel_time_min;
        result.total_time_min+=UNLOAD_TIME_MIN; // unloading time

        // Bin ko serviced mark kar do
        bins[next_index].serviced=1;
        result.bins_serviced++;

        // Ab truck yahi bin pe khada hai
        current_index=next_index;
        at_depot=0;

        // Debug info jaisa print: route trace
        printf("Truck reached Bin %d, distance travelled: %.2f units, total distance: %.2f\n",
               bins[next_index].id,
               distance_to_next,
               result.total_distance);
    }

    // Optional: last me truck ko wapas depot bhejna hai ya nahi
    // Agar chaho toh yaha wapas depot ka distance bhi add kar sakte ho

    return result;
}
