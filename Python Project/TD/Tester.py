import subprocess
import time

def test(program_name):    
    start_time = time.time()
    subprocess.call(["python", program_name+".py"])
    end_time = time.time()
    print("time needed :"+end_time - start_time)