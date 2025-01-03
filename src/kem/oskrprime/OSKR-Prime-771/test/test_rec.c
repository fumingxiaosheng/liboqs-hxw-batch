#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define q 3923

int64_t rec(int32_t a, int32_t b) {                                                              
  int64_t t;
  t = (a + 16) * q - (b << 6);
  t = (t * 8553) >> 30;
  t = t & 1;
  return t;
}

int64_t rec1(int32_t a, int32_t b) {                                                              
  int64_t t;
  t = (a + 16) * q - (b << 6);
  t = t / 125536 - ((uint64_t)t >> 63);
  t = t & 1;
  return t;
}


int main(){
    int64_t t;
    int64_t t_star;
    for(int32_t i=0;i<4096;i++){
        for(int32_t j=0;j<64;j++){
            t=rec1(j,i);
            t_star=(j*q-(i<<6)+16*q);
            t_star=t_star/(32*q) - ((uint64_t)t_star >> 63);
            t_star=t_star&1;
            if((t-t_star)!=0){
                printf("error,%d,%d,%ld,%ld,\n",i,j,t,t_star);
            }
        }
        
    }
    printf("end\n");
}