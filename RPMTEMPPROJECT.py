"""
Benjamin Lust
RPMTEMP Project
Python Data Logger
"""

import csv
import serial
import time
import matplotlib.pyplot as plt


def log_sensor_data(port, baudrate = 9600, csv_path = "rpm_heat_log.csv", duration = 75):
    ser = serial.Serial(port, baudrate)
    time.sleep(2)
    
    with open(csv_path, "w") as f:
        writer = csv.writer(f)
        writer.writerow(["rpm", "temperature"])
        
        start = time.time()
        count = 0
        
        while time.time() - start < duration:
            try:
                line = ser.readline().strip().decode().split(",")
                if len(line) == 2:
                    writer.writerow([line[0], line[1]])
                    count += 1
            except:
                pass
            
    ser.close()
    
    print(f"Logged {count} lines to {csv_path}")

# function that graphs the 
def show_data(csv_path):
    
    with open(csv_path, "r") as f:
        
        header = f.readline()
        rpm = []
        temp = []
        
        for line in f:
            parts = line.strip().split(",")
            if len(parts) == 2 and parts[0] != '' and parts[1] != '':
                temp.append(float(parts[0]))
                rpm.append(float(parts[1]))
        
        
        
        timestamps = list(range(len(rpm)))

        fig, ax1 = plt.subplots()
        ax1.plot(timestamps, temp, color = "red", label = "Temperature (F)")
        ax1.set_xlabel("Time (seconds)")
        ax1.set_ylabel("Temperature (F)", color = "red")

        ax2 = ax1.twinx()
        ax2.plot(timestamps, rpm, color="blue", label="RPM")
        ax2.set_ylabel("RPM", color="blue")
        plt.grid(True)
        
        ax1.set_yticks([60, 65, 70, 75, 80, 85, 90])
        ax2.set_yticks([0, 300, 600, 900])
        ax1.set_xticks(range(0, 61, 5))
        
        lines1, labels1 = ax1.get_legend_handles_labels()
        lines2, labels2 = ax2.get_legend_handles_labels()
        ax1.legend(lines1 + lines2, labels1 + labels2, loc = "upper left")

        plt.title("Temperature and RPM over Time")
        plt.show()
    
    
if __name__ == "__main__":
    log_sensor_data("COM3")
    show_data("rpm_heat_log.csv")
                            
                           