

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int SIZE = 512;
#include <stdint.h>
#include "param.h"


void foo(float* output, float* x0, float* x1){
  /* mapSeq */
  for (int i_11448 = 0;(i_11448 < 512/v_B_14);i_11448 = (1 + i_11448)) {
    /* mapSeq */
    for (int i_11449 = 0;(i_11449 < 512/v_B_14);i_11449 = (1 + i_11449)) {
      /* reduceSeq */
      {
        float x11197[1024];
        /* mapSeq */
        for (int i_11450 = 0;(i_11450 < v_B_14);i_11450 = (1 + i_11450)) {
          /* mapSeq */
          for (int i_11451 = 0;(i_11451 < v_B_14);i_11451 = (1 + i_11451)) {
            x11197[(i_11451 + (32 * i_11450))] = 0.0f;
          }
          
        }
        
        for (int i_11452 = 0;(i_11452 < (512 / v_N_14));i_11452 = (1 + i_11452)) {
          /* reduceSeq */
          {
            float x11117[1024];
            /* mapSeq */
            for (int i_11453 = 0;(i_11453 < v_B_14);i_11453 = (1 + i_11453)) {
              /* mapSeq */
              for (int i_11454 = 0;(i_11454 < v_B_14);i_11454 = (1 + i_11454)) {
                x11117[(i_11454 + (v_B_14 * i_11453))] = x11197[(i_11454 + (v_B_14 * i_11453))];
              }
              
            }
            
            for (int i_11483 = 0;(i_11483 < v_N_14);i_11483 = (1 + i_11483)) {
              /* mapSeq */
              for (int i_11484 = 0;(i_11484 < v_B_14);i_11484 = (1 + i_11484)) {
                /* mapSeq */
                for (int i_11485 = 0;(i_11485 < v_B_14);i_11485 = (1 + i_11485)) {
                  x11117[(i_11485 + (v_B_14 * i_11484))] = (x11117[(i_11485 + (v_B_14 * i_11484))] + (x0[(((i_11483 + (512 * i_11484)) + (512 * v_B_14 * i_11448)) + (v_N_14 * i_11452))] * x1[(((i_11485 + (v_B_14 * i_11449)) + ((512 * v_N_14) * i_11452)) + (512 * i_11483))]));
                }
                
              }
              
            }
            
            /* mapSeq */
            for (int i_11542 = 0;(i_11542 < v_B_14);i_11542 = (1 + i_11542)) {
              /* mapSeq */
              for (int i_11543 = 0;(i_11543 < v_B_14);i_11543 = (1 + i_11543)) {
                x11197[(i_11543 + (v_B_14 * i_11542))] = x11117[(i_11543 + (v_B_14 * i_11542))];
              }
              
            }
            
          }
          
        }
        
        /* mapSeq */
        for (int i_11544 = 0;(i_11544 < v_B_14);i_11544 = (1 + i_11544)) {
          /* mapSeq */
          for (int i_11545 = 0;(i_11545 < v_B_14);i_11545 = (1 + i_11545)) {
            output[(((i_11545 + (v_B_14* i_11449)) + (512 * i_11544)) + (512* v_B_14 * i_11448))] = x11197[(i_11545 + (v_B_14* i_11544))];
          }
          
        }
        
      }
      
    }
    
  }
  
}


void compute_gold(float* output, float* x0, float* x1){
  /* mapSeq */
  for (int i_574450 = 0;(i_574450 < 512);i_574450 = (1 + i_574450)) {
    /* mapSeq */
    for (int i_574451 = 0;(i_574451 < 512);i_574451 = (1 + i_574451)) {
      {
        float x574436[512];
        /* mapSeq */
        for (int i_574452 = 0;(i_574452 < 512);i_574452 = (1 + i_574452)) {
          x574436[i_574452] = (x0[(i_574452 + (512 * i_574450))] * x1[(i_574451 + (512 * i_574452))]);
        }
        
        /* reduceSeq */
        {
          float x574434;
          x574434 = 0.0f;
          for (int i_574453 = 0;(i_574453 < 512);i_574453 = (1 + i_574453)) {
            x574434 = (x574434 + x574436[i_574453]);
          }
          
          output[(i_574451 + (512 * i_574450))] = x574434;
        }
        
      }
      
    }
    
  }
  
}



int compare_gold(float* C, float* GOLD){
  int valid = 1;
        for(int i = 0; i < SIZE*SIZE; i++){
    		  if(C[i] != GOLD[i]){
    			  valid = 0;
            i = SIZE*SIZE;
    		  }
    	  }
        
    return valid;
    }
    

int main(int argc, char** argv) {

  
        const int N = 512;
        
        //inputs
        float* x0 = (float*) malloc(sizeof(float)*N*N);
        for (int i = 0; i < N*N; i++) {
          x0[i] = i;
        }
        
        float* x1 = (float*) malloc(sizeof(float)*N*N);
        for (int i = 0; i < N*N; i++) {
          x1[i] = i;
        }
        

        //output
        float* output = (float*) malloc(sizeof(float)*N*N);
        float* gold = (float*) malloc(sizeof(float)*N*N);
        for (int i = 0; i < N*N; i++) {
          output[i] = 0;
          gold[i] = 0;
        }
        

  //measure time
 	struct timespec tp_start;
	struct timespec tp_end;
	clockid_t clk_id = CLOCK_MONOTONIC;
  double duration = 0;

  clock_gettime(clk_id, &tp_start);
  foo(output, x0, x1);
  clock_gettime(clk_id, &tp_end);

  duration = (tp_end.tv_sec - tp_start.tv_sec) * 1000000000 + (tp_end.tv_nsec - tp_start.tv_nsec);
  duration = duration / 1000000;

  compute_gold(gold, x0, x1);
  int check = compare_gold(output, gold);

  
       //free memory
        free(x0);
        free(x1);
        free(gold);
        free(output);

  //check result
  if(!check){
    return -1;
  }

  //print result
  printf("%f\n", duration);

  return 0;
}

