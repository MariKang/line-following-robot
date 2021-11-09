import serial
import csv
import time

arduino_com_port = "/dev/cu.usbmodem142301"

baud_rate = 9600

serial_port = serial.Serial(arduino_com_port, baud_rate, timeout=1)

with open("line_follower_data.csv", "w") as outfile:
    outfile.write("IR_left,IR_right, Motor_left, Motor_right\n")

while True:
    time.sleep(1)
    data = serial_port.readline().decode()

    file = open("line_follower_data.csv")
    reader = csv.reader(file)
    lines= len(list(reader))

    if len(data):
        ir_left, ir_right, motor_left, motor_right = [float(x) for x in data.split()]


    with open("line_follower_data.csv", "a") as outfile:
        outfile.write(f"{ir_left},{ir_right},{motor_left}, {motor_right}\n")
