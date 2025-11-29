#ifndef BIN_H
#define BIN_H

// Ek bin ka data structure
typedef struct {
    int id;             // unique id
    double x;           // x coordinate
    double y;           // y coordinate
    double fill_level;  // kitna percent bhara hai
    int priority;       // priority (bada number = zyada important)
    int serviced;       // 0 => abhi tak collect nahi hua, 1 => ho chuka
} Bin;

// Dynamic array banane ke liye helper
Bin* create_bin_array(int initial_capacity, int *capacity_out);

// Naya bin add karo, agar jagah kam pad gayi toh realloc se bada kar dega
Bin* add_bin(Bin *bins, int *count, int *capacity, Bin b);

// Sirf dekhne ke liye sab bins print kar do
void print_bins(const Bin *bins, int count);

// Distance matrix allocate + fill karega
double** create_distance_matrix(const Bin *bins, int count);

// Distance matrix free karne ke liye
void free_distance_matrix(double **matrix, int count);

// Bin array ko free karne ke liye
void free_bins(Bin *bins);

#endif
