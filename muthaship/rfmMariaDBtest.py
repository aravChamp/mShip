"""
MUDBUG

Author: Arav Sharma
"""
# Import Python System Libraries
import time
# Import Blinka Libraries
import busio
from digitalio import DigitalInOut, Direction, Pull
import board
# Import RFM9x
import adafruit_rfm9x
#import database connection
import mariadb 
import sys

try:
    conn = mariadb.connect(
        user="admin",
        password="sensorhub2",
        host="localhost",
        port=3306,
	database="humTemp"

    )
except mariadb.Error as e:
    print(f"Error connecting to MariaDB Platform: {e}")
    sys.exit(1)
	
cur = conn.cursor()

# Configure LoRa Radio
CS = DigitalInOut(board.CE1)
RESET = DigitalInOut(board.D25)
spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)
rfm9x = adafruit_rfm9x.RFM9x(spi, CS, RESET, 915.0)
rfm9x.tx_power = 23
prev_packet = None

while True:
    packet = None

    print("RasPi LoRa")

    # check for packet rx
    packet = rfm9x.receive()
    if packet is None:
        print("- Waiting for PKT -")
    else:
        # Display the packet text and rssi
        prev_packet = packet
        packet_text = str(prev_packet, "utf-8")
        Hum = packet_text[3:8]
        Temp = packet_text[12:17]
        #hum = float(Hum)
        #temp = float(Temp)
        print(packet_text)
        try:
                cur.execute("INSERT INTO dhtData (hum,temp) VALUES (?, ?)", (Hum,Temp))
        except mariadb.Error as e:
                print(f"Error: {e}")
        conn.commit()
        time.sleep(1)

    time.sleep(1)

  