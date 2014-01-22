/* 
 * File:   main.cpp
 * Author: reafle
 *
 * Created on January 13, 2014, 12:33 AM
 */

#include <cstdlib>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

using namespace std;

void bresenhamLineInt(int linex1, int linex2, int liney1, int liney2) {
    int dx = linex2 - linex1;
    int dy = liney2 - liney1;
    int y = liney1;

    int e = 2 * dy - dx;
    for (int x = linex1; x < linex2; x++) //2 * dy - dx  <= e <  2 * dy + dx
    {
//        drawPoint(x, y);
        if (e >= 0) {
            y = y + 1;
            e = e - 2 * dx;
        }
        e = e + 2 *  dy;
    }
    
    return ;
}

void bresenhamLineFloat(int linex1, int linex2, int liney1, int liney2) {

    int dx = linex2 - linex1;
    int dy = liney2 - liney1;
    int y = liney1;

    float e = 0.0;

    for (int x = linex1; x < linex2; x++) { // -0.5 <= e < 0.5
//        drawPoint(x, y);

        e = e + dy / dx;

        if (e >= 0.5) {
            y = y + 1;
            e = e - 1.0;
        } 
    }
}

int main(int argc, char** argv) {

    struct timeval last_start_time, last_end_time;

    srand(time(0));
    if (argc != 2) {
        printf("Usage: ./main [iterations]");
        printf("\n");
        return 1;
    }

    int number_of_iterations = strtol(argv[1], NULL, 10);
    if (number_of_iterations <= 0 || number_of_iterations > 10000000) {
        printf("Parameter `iterations` must fall within [0, 10000000]");
        printf("\n");
        return 1;
    }


    int test1 = number_of_iterations;
    long long total_time_int = 0;

    while (test1-- > 0) {
        int linex1 = 1 + rand() % 16;
        int linex2 = 16 + rand() % 32;
        int liney1 = 1 + rand() % 32;
        int liney2 = 16 + rand() % 32;

        gettimeofday(&last_start_time, NULL);

        bresenhamLineInt(linex1, linex2, liney1, liney2);

        gettimeofday(&last_end_time, NULL);

        long long start = last_start_time.tv_sec * 1000000LL + last_start_time.tv_usec;
        long long end = last_end_time.tv_sec * 1000000LL + last_end_time.tv_usec;

        total_time_int += (end - start);
    }

    printf("%d calls to bresenhamLineInt   completed in %lld ns (%3.6f s)", number_of_iterations, total_time_int, total_time_int / 1000000.0);
    printf("\n");

    int test2 = number_of_iterations;
    long long total_time_float = 0;

    while (test2-- > 0) {
        int linex1 = 1 + rand() % 16;
        int linex2 = 16 + rand() % 32;
        int liney1 = 1 + rand() % 32;
        int liney2 = 16 + rand() % 32;

        gettimeofday(&last_start_time, NULL);

        bresenhamLineFloat(linex1, linex2, liney1, liney2);

        gettimeofday(&last_end_time, NULL);

        long long start = last_start_time.tv_sec * 1000000LL + last_start_time.tv_usec;
        long long end = last_end_time.tv_sec * 1000000LL + last_end_time.tv_usec;

        total_time_float += (end - start);
    }

    printf("%d calls to bresenhamLineFloat completed in %lld ns (%3.6f s)", number_of_iterations, total_time_float, total_time_float / 1000000.0);
    printf("\n");
    printf("INT version is  %2.2f%% faster than FLOAT", (float)(100 - (total_time_int * 100) / total_time_float));
    printf("\n");
  
    printf("\n");
    return 0;
}

