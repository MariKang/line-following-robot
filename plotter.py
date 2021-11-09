import pandas as pd
import csv

import matplotlib.pyplot as plt
import seaborn as sns

sns.set(style="whitegrid")


time = []
ir_left = []
motor_left = []

ir_right = []
motor_right = []

#Get the data from the csv
with open('line_follower_data.csv','r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    headings = next(lines)
    timestamp = 0
    for row in lines:
        time.append(timestamp)
        ir_left.append(float(row[0]))
        ir_right.append(float(row[1]))
        motor_left.append(float(row[2]))
        motor_right.append(float(row[3]))
        timestamp+=1


# create figure and axis objects with subplots()
fig,ax = plt.subplots()
# make a plot

ax.plot(time, motor_left, color="g", linestyle = 'dashed', marker = 'o', label="Motor Left")
ax.plot(time, motor_right, color="r", linestyle = 'dashed', marker = 'o', label="Motor Right")

# set x-axis label
ax.set_xlabel("time",fontsize=14)
# set y-axis label
ax.set_ylabel("Motor Speed",fontsize=14)

# twin object for two different y-axis on the sample plot
ax2=ax.twinx()

# make a plot with different y-axis using second axis object
ax2.plot(time, ir_left,color="b", linestyle = 'dashed', marker = 'o',label = "IR Left Value")
ax2.plot(time, ir_right,color="y", linestyle = 'dashed', marker = 'o',label = "IR Right Value")
ax2.set_ylabel("IR Value",fontsize=14)

leg = ax.legend()
  
plt.xticks(rotation = 90)
plt.title('Sensor Data from IR Sensors and Commanded Motor Speeds', fontsize = 20)
plt.grid()
plt.legend()
plt.show()

