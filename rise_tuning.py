#!/usr/bin/python
import math, sys
import numpy as np
import os
from subprocess import Popen, PIPE, call, check_output, run
sys.path.append('scripts')
import hypermapper

ITERATIONS = 3

from pathlib import Path

PATH = Path().absolute() 
print("PATH: " + str(PATH))

def rise(X):
    # get parameters from X 
    v_N_14 = X['v_N_14']
    v_B_14 = X['v_B_14']
    print("v_N_14 " + str(v_N_14))
    print("v_B_14 " + str(v_B_14))

    # check constraints
    c1 = 512%v_N_14 == 0
    c2 = 512%v_B_14 == 0
    valid = c1 and c2
    #
    # print result
    print('valid: ' + str(valid))

    runtime = sys.maxsize
    
    if valid:
        # replace values with parameters in param.h file 
        f = open(str(PATH) + "/param.h", "w")
        f.write("#define v_N_14 " + str(v_N_14) + "\n")
        f.write("#define v_B_14 " + str(v_B_14))
        f.close()

        # compile 
        call(["clang", "-O2", "-o", str(PATH) + "/tmp", str(PATH) + "/rise_program.c"])

        # execute and measure time 
        error = False

        runtimes = np.zeros(ITERATIONS)
        try:
            for i in range(ITERATIONS):
                runtimes[i] = 1
                value = float(check_output([str(PATH) + "/tmp"]))
                runtimes[i] = value
        except Exception as e: 
            runtime = sys.maxsize
            error = True
            valid = False
            print("runtime: inf")

        if(not error):
            runtime = np.median(runtimes)
            print("runtime: " + str(runtime))

    #output = {}
    #output['runtime'] = runtime
    #output['Valid'] = valid
    
   # return output
    return runtime 

def main():
    parameters_file = str(PATH) + "/rise3.json"
    hypermapper.optimize(parameters_file, rise)
    print("End of mm.")

if __name__ == "__main__":
    main()
