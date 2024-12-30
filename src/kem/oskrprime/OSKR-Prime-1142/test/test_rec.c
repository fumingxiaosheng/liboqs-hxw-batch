#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define q 7177

int64_t rec(int32_t a, int32_t b) {                                                              
  int64_t t;
  t = (a + 2) * q - (b << 3);
  t = (t * 37402) >> 30;
  t = t & 1;
  return t;
}

int64_t rec1(int32_t a, int32_t b) {                                                              
  int64_t t;
  t = (a + 2) * q - (b << 3);
  t = t / 28708 - ((uint64_t)t >> 63);
  t = t & 1;
  return t;
}


int main(){
    int64_t t;
    int64_t t_star;
    for(int32_t i = 0;i < 8192;i++){
        for(int32_t j = 0;j < 8;j++){
            t = rec1(j,i);
            t_star = (j*q - (i << 3) + 2*q);
            t_star = t_star / (4*q) - ((uint64_t)t_star >> 63);
            t_star = t_star & 1;
            if((t-t_star) != 0){
                printf("error,%d,%d,%ld,%ld,\n",i,j,t,t_star);
            }
        }
        
    }
    printf("end\n");
}