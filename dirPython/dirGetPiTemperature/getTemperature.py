import subprocess

def get_cpu_temp():
    with open("/sys/class/thermal/thermal_zone0/temp") as tempFile:
        cpu_temp = tempFile.read()
    return float(cpu_temp) / 1000
    # Uncomment the next line if you want the temp in Fahrenheit
    #return float(1.8 * (cpu_temp / 1000)) + 32

def get_gpu_temp():
    gpu_temp = subprocess.getoutput('/opt/vc/bin/vcgencmd measure_temp').replace('temp=', '').replace('\'C', '')
    return float(gpu_temp)
    # Uncomment the next line if you want the temp in Fahrenheit
    #return float(1.8 * float(gpu_temp)) + 32

def main():
    print("CPU temp: ", str(get_cpu_temp()))
    print("GPU temp: ", str(get_gpu_temp()))

if __name__ == '__main__':
    main()

