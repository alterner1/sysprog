#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "md5.h"
#include "version.h" 

#define START   0x20 //space
#define END     0x7E //~ 

static void print_version(){

  printf("Version: %s\n", g_version);
}

int compare(const uint32_t a[], const uint32_t b[]) {
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}

int brute_force_fixed_length(const uint32_t hash[4], byte_t* result, byte_t* test, int p, int len) {
    static md5_t MD5;
    static uint32_t check[4];
    int c;

    if (p < len - 1) {
        for (c = START; c <= END; ++c) {
            test[p] = c;
            if (brute_force_fixed_length(hash, result, test, p + 1, len))
                return 1;
        }
    } else {
        for (c = START; c <= END; ++c) {
            test[p] = c;

            md5_init(&MD5);
            md5_update(&MD5, test, len);
            md5_hash(&MD5, check);

            if (compare(hash, check)) {
                strcpy(result, test);
                return 1;
            }
        }
    }

    return 0;
}

int u_threads () {
    int num_procs = omp_get_num_procs();
    int max_threads = omp_get_max_threads();
    int nthreads = (num_procs > max_threads ? num_procs : max_threads) - 1; 
    return nthreads; 
}

int brute_force(const uint32_t hash[4], byte_t* result, int maxlen) {
    byte_t str[maxlen + 1];
int nthreads = u_threads();

// #pragma omp parallel for num_threads(nthreads)

    for (int i = 0; i < maxlen; i++) {
        if (brute_force_fixed_length(hash, result, str, 0, i)) return 1;
    }
    return 0;
    
}


int main() {
    uint32_t hash[4];
    char hexstring[33] = {0};
    char result[11];          

    printf("Enter hex hash:  ");
    fgets(hexstring, 33, stdin);
    for (int i = 0; i < 4; i++)
        sscanf(&hexstring[i * 8], "%8x", &hash[i]);
    
    print_version();
    printf("Decrypting hash: %08x%08x%08x%08x\n", hash[0], hash[1], hash[2], hash[3]);
   
    printf("Number of potential parallel processes: %d\n", u_threads()); 
  
        brute_force(hash, result, 10);
 
    printf("Original text:   %s\n", result);

    return 0;
}