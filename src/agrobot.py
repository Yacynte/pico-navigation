import serial
import time

# Replace with the correct port for your setup
port = '/dev/ttyACM0'  # For Linux
# port = 'COM3'  # For Windows
# port = '/dev/tty.usbmodem14101'  # For macOS

baudrate = 115200
# Open the serial port
try:
    ser = serial.Serial(port, baudrate, timeout=1)
except serial.SerialException as e:
    print(f"Error opening serial port {port}: {e}")
    exit(1)

def send_data(data):
    if ser.is_open:
        ser.write(data.encode('utf-8'))
        print(f"Sent: {data}")
    else:
        print("Serial port is not open")

try:
    while True:
        # Example: Send two float values
        float0 = "forward"
        float1 = 3.14
        float2 = 2.71
        data = f"{float0} {float1} {float2}\n"
        send_data(data)
        
        # Wait before sending the next data
        time.sleep(1)
except KeyboardInterrupt:
    ser.close()
    print("Serial port closed")
