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


void bresenhamLineInt(int linex1, int linex2, int liney1, int liney2 ) {

    float m = linex2 != linex1 ? (liney2 - liney1) / (linex2 - linex1) : 0;

    bool first_octant = linex1 < linex2 && m >= 0 && m <= 1;
    bool second_octant = liney1 < liney2 && m > 1;
    bool third_octant = liney1 < liney2 && m < -1;
    bool fourth_octant = linex2 < linex1 && m >= -1 && m <= 0;
    bool fifth_octant = linex2 < linex1 && m > 0 && m <= 1;
    bool sixth_octant = liney2 < liney1 && m > 1;
    bool seventh_octant = liney2 < liney1 && m < -1;
    bool eight_octant = linex1 < linex2 && m < 0 && m >= -1;

    int x1 = linex1, x2 = linex2;
    int y1 = liney1, y2 = liney2;

    if (fifth_octant || sixth_octant || third_octant || fourth_octant) {
        x1 = linex2;
        x2 = linex1;

        y1 = liney2;
        y2 = liney1;
    }

    int w = x2 - x1;
    int h = y2 - y1;

    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
    if (w < 0) dx1 = -1;
    else if (w > 0) dx1 = 1;
    if (h < 0) dy1 = -1;
    else if (h > 0) dy1 = 1;
    if (w < 0) dx2 = -1;
    else if (w > 0) dx2 = 1;

    int longest = abs(w);
    int shortest = abs(h);
    if (!(longest > shortest)) {
        longest = abs(h);
        shortest = abs(w);
        if (h < 0) dy2 = -1;
        else if (h > 0) dy2 = 1;
        dx2 = 0;
    }

    int numerator = longest >> 1;
    int x = x1, y = y1;
    

    for (int i = 0; i <= longest; i++) {

        numerator += shortest;
        if (!(numerator < longest)) {
            numerator -= longest;
            x += dx1;
            y += dy1;
        } else {
            x += dx2;
            y += dy2;
        }
    }
}


int main(int argc, char** argv) {

    struct timeval last_start_time, last_end_time;

    srand (time(0));    
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
        int linex1 = 1 + rand() % 32;
        int linex2 = 1 + rand() % 32;
        int liney1 = 1 + rand() % 32;
        int liney2 = 1 + rand() % 32;
        
        gettimeofday(&last_start_time, NULL);
        
        bresenhamLineInt(linex1, linex2, liney1, liney2);

        gettimeofday(&last_end_time, NULL);
        
        long long start = last_start_time.tv_sec*1000000LL + last_start_time.tv_usec;
        long long end = last_end_time.tv_sec*1000000LL + last_end_time.tv_usec;        
    
        total_time_int += (end - start);
    }
    
    printf("%d calls to bresenhamLineInt completed in %lld ns (%3.6f s)", number_of_iterations, total_time_int, total_time_int/1000000.0);

    
    
//    if ((last_end_time - last_start_time) > 0) {
//        last_end_time = time(0);
//    }
    
//        if ((last_end_time - last_start_time) > 0) {
//            mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
//            ss << "time : " << mtime << " s. " << std::endl;            
//        }
    
    printf("\n");            
    return 0;
}

