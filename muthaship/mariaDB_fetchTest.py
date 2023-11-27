#!/usr/bin/python 
import mariadb 

conn = mariadb.connect(
    user="admin",
    password="sensorhub2",
    host="localhost",
    database="humTemp")
cur = conn.cursor() 

#retrieving information 
cur.execute("SELECT hum,temp FROM dhtData WHERE hum=?", (49.00,)) 

for hum, temp in cur: 
    print(f"humidity: {hum}, temp: {temp}")
    
#insert information 
try: 
    cur.execute("INSERT INTO dhtData (hum,temp) VALUES (?, ?)", ("48.90","27.00")) 
except mariadb.Error as e: 
    print(f"Error: {e}")

conn.commit() 
print(f"Last Inserted ID: {cur.lastrowid}")
    
conn.close()