import socket
import json
UDP_IP = ""
UDP_PORT = 8080

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))
while True:
    data, addr = sock.recvfrom(20000) # buffer size is 20000 bytes
    print("Current Humidity = ", json.loads(data.decode())["h"], "%",
                                                                " ---",
        "Current Temperature = ", json.loads(data.decode())["t"], "C")
