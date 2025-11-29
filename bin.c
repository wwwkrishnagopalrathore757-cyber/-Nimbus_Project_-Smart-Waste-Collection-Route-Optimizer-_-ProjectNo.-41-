#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bin.h"

// Local helper: do points ke beech ka distance
static double point_distance(double x1, double y1, double x2, double y2) {
    double dx=x2-x1;
    double dy=y2-y1;
    return sqrt(dx*dx+dy*dy);
}

Bin* create_bin_array(int initial_capacity,int *capacity_out) {
    // Thoda sanity check
    if (initial_capacity<=0){
        initial_capacity=2; // minimum 2 toh rakhenge hi
    }

    Bin *bins=(Bin*)malloc(sizeof(Bin)*initial_capacity);
    if (!bins){
        printf("Memory allocation fail ho gaya yaar (bins array).\n");
        *capacity_out=0;
        return NULL;
    }

    *capacity_out=initial_capacity;
    return bins;
}

Bin* add_bin(Bin *bins,int *count,int *capacity,Bin b) {
    // Agar current capacity khatam ho gayi toh size double kar denge
    if (*count>=*capacity){
        int new_capacity=(*capacity)*2;
        Bin *temp=(Bin*)realloc(bins,sizeof(Bin)*new_capacity);
        if (!temp){
            printf("realloc fail ho gaya, aur bins add nahi kar sakte.\n");
            return bins; // purana pointer hi return karenge, but add nahi hoga
        }
        bins=temp;
        *capacity=new_capacity;
        // Thoda info user ke liye
        // printf("Bins array resize ho ke %d ho gaya.\n", new_capacity);
    }

    bins[*count]=b;
    (*count)++;
    return bins;
}

void print_bins(const Bin *bins,int count){
    int i;
    printf("\n--- City Bins Overview ---\n");
    for (i=0;i<count;i++) {
        printf("Bin ID: %d | Location: (%.2f, %.2f) | Fill: %.1f%% | Priority: %d | Serviced: %s\n",
               bins[i].id,
               bins[i].x,
               bins[i].y,
               bins[i].fill_level,
               bins[i].priority,
               bins[i].serviced ? "Yes" : "No");
    }
    printf("---------------------------\n");
}

double** create_distance_matrix(const Bin *bins,int count){
    int i,j;
    double **matrix=(double**)malloc(sizeof(double*)*count);
    if (!matrix){
        printf("Distance matrix ke rows ke liye memory nahi mili.\n");
        return NULL;
    }

    for (i=0;i<count;i++){
        matrix[i]=(double*)malloc(sizeof(double)*count);
        if (!matrix[i]){
            printf("Distance matrix ke ek row me memory fail.\n");
            // jitna allocate hua hai, free kar do
            int k;
            for(k = 0;k<i;k++){
                free(matrix[k]);
            }
            free(matrix);
            return NULL;
        }
    }

    // Distances fill karte hain
    for (i=0;i<count;i++){
        for (j=0;j<count;j++){
            if (i==j){
                matrix[i][j]=0.0;
            } else{
                matrix[i][j]=point_distance(bins[i].x, bins[i].y,
                                              bins[j].x, bins[j].y);
            }
        }
    }

    return matrix;
}

void free_distance_matrix(double **matrix,int count){
    if(!matrix) return;
    for(int i=0;i<count;i++){
        free(matrix[i]);
    }
    free(matrix);
}

void free_bins(Bin *bins){
    free(bins);
}