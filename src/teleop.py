# import keyboard
from pynput import keyboard
import threading
import time
from queue import Queue

# Queue to hold key inputs
input_queue = Queue()

'''
increase speed: w
decrease speed: x 
rotate left: e
rotate rigth: r
stop: s
move forward: ↑ 
move  backward: ↓
rotate left: ←
rotate right: →
'''
target_speed = 0
target_ang_speed = 0
direction = "None"
orientation = "None"
current_speed = 0
current_ang_speed = 0
float5 = '\n'


# Function to print data continuously, including key inputs
def print_data():
    while True:
        # Check if there's any key input in the queue
        if not input_queue.empty():
            key_input = input_queue.get()
            print(f"Received key input: {key_input}")
        
        # Print other data
        # print("Printing other data...")
        time.sleep(1)

# Function to handle multiple key presses
def key_listener():
    while True:
        if keyboard.Key == 'w':
            target_speed += 0.1
        if keyboard.Key == 'x':
            target_speed -= 0.1
        if keyboard.Key == 's':
            target_speed = 0
            target_ang_speed = 0
        if keyboard.Key == 'e':
            target_ang_speed -= 2
        if keyboard.Key == 'r':
            target_ang_speed += 2
        if target_ang_speed > 0:
            orientation = "left"
        if target_ang_speed < 0:
            orientation = "right"
        if target_ang_speed == 0:
            orientation = "straight"
        if target_speed >= 0:
            direction = "forward"
        if target_speed < 0:
            direction = "backward"
        input_queue = f"{direction} {orientation} {current_speed} {current_ang_speed} {target_speed} {target_ang_speed} {float5}"
        # Add more keys if needed
        time.sleep(0.1)  # Prevents high CPU usage

# Creating threads
thread1 = threading.Thread(target=print_data)
thread2 = threading.Thread(target=key_listener)

# Starting threads
thread1.start()
thread2.start()

# Ensuring the main thread doesn't exit
thread1.join()
thread2.join()
