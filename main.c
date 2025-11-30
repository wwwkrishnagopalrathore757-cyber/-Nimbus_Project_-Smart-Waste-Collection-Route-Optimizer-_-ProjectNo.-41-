#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "bin.h"
#include "route.h"
#include "report.h"

int main(void) {
    int n;
    int capacity;
    int count = 0;

    printf("=============================================\n");
    printf(" Smart Waste Collection Route Optimizer (C)\n");
    printf("=============================================\n");
    printf("Note: Ye sirf ek simulator hai, real life ka full software nahi :)\n\n");

    printf("Kitne garbage bins add karne hain city me? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of bins, program exit ho raha hai.\n");
        return 1;
    }

    // Initial capacity thodi kam rakh ke realloc ka use dikhaya hai
    Bin *bins = create_bin_array(2, &capacity);
    if (!bins) {
        return 1;
    }

    // User se bin data lete hain
    for (int i = 0; i < n; i++) {
        Bin b;
        b.id = i + 1;
        b.serviced = 0;

        printf("\n--- Bin %d details ---\n", b.id);

        // Real student jaisa input: thoda guidance de diya
        printf("Enter x coordinate (e.g., 10.5): ");
        scanf("%lf", &b.x);

        printf("Enter y coordinate (e.g., 5.0): ");
        scanf("%lf", &b.y);

        printf("Enter fill level in percent (0-100): ");
        scanf("%lf", &b.fill_level);

        printf("Enter priority (1 = low, 5 = very high, e.g., hospital): ");
        scanf("%d", &b.priority);

        // Dynamic array me add kar dete hain
        bins = add_bin(bins, &count, &capacity, b);
        if (!bins) {
            printf("Kuch gadbad ho gayi bins add karte waqt.\n");
            return 1;
        }
    }

    // Bins ka ek overview de dete hain
    print_bins(bins, count);

    // Distance matrix banate hain
    double **distance_matrix = create_distance_matrix(bins, count);
    if (!distance_matrix) {
        free_bins(bins);
        return 1;
    }

    // Simple assumption: depot (0,0) pe hai
    double depot_x = 0.0;
    double depot_y = 0.0;

    printf("\nDepot location assume kiya gaya hai: (%.1f, %.1f)\n", depot_x, depot_y);
    printf("Fill threshold for collection: %.1f%%\n", FILL_THRESHOLD);
    printf("Truck speed: %.1f units/hour, Unload time: %.1f min/bin\n\n",
           TRUCK_SPEED, UNLOAD_TIME_MIN);

    // Routing algorithm run karte hain
    RouteResult result = run_nearest_full_bin_route(bins, count, distance_matrix, depot_x, depot_y);

    // Report print kar dete hain
    print_trip_report(&result, bins, count);

    // Memory cleanup (warna sirf practical me marks cutte :P)
    free_distance_matrix(distance_matrix, count);
    free_bins(bins);

    printf("\nProgram finished. Thanks for using Smart Waste Route Optimizer!\n");
    return 0;
}
