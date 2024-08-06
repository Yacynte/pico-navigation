import socket
import time

def start_client(host='127.0.0.1', port=4000):
    # Create a TCP/IP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        # Connect the socket to the server's port
        client_socket.connect((host, port))
        
        try:
            # Send data
            while True:
                # Example: Send two float values
                float0 = "forward"
                float1 = 3.14
                float2 = 2.71
                float3 = "\n"
                message = f"{float0} {float1} {float2} {float3}"
                client_socket.sendall(message.encode('utf-8'))
                print(f"Sent: {message}")
                
                # Receive response
                data = client_socket.recv(1024)
                print(f"Received: {data.decode('utf-8')}")
                
        
        finally:
            # Clean up the connection
            client_socket.close()

if __name__ == '__main__':
    start_client()
