#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define q 6977

int64_t rec(int32_t a, int32_t b) {                                                              
  int64_t t;
  t = (a + 4) * q - (b << 4);
  t = (t * 19237) >> 30;
  t = t & 1;
  return t;
}

int64_t rec1(int32_t a, int32_t b) {                                                              
  int64_t t;
  t = (a + 4) * q - (b << 4);
  t = t / 55816 - ((uint64_t)t >> 63);
  t = t & 1;
  return t;
}


int main(){
    int64_t t;
    int64_t t_star;
    for(int32_t i = 0;i < 8192;i++){
        for(int32_t j = 0;j < 16;j++){
            t = rec1(j,i);
            t_star = (j*q - (i << 4) + 4*q);
            t_star = t_star / (8*q) - ((uint64_t)t_star >> 63);
            t_star = t_star & 1;
            if((t-t_star) != 0){
                printf("error,%d,%d,%ld,%ld,\n",i,j,t,t_star);
            }
        }
        
    }
    printf("end\n");
}