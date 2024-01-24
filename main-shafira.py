import cv2
import numpy as np
import paho.mqtt.client as mqtt # Import the MQTT library
import json
import csv
import time
import os

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH,1080)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT,720)
log_path = "log"

csv_name = "log.csv"
csv_path = os.path.join(log_path,csv_name)
def save_image(img, key):
    img_name = f"{key}.jpg"
    img_path = os.path.join(log_path,img_name)
    cv2.imwrite(img_path, img) # Save the image
    print(f'Image saved as {img_path}') # Print a confirmation messag


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("AQI") # Subscribe to a topic

def on_message(client, userdata, msg):
    payload = msg.payload.decode("utf-8")
    global Temp, Humi, Dust, Co
    try:
        data = json.loads(payload)
        pretty_data = json.dumps(data, indent=2)
        Temp = data["temp"]
        Humi = data["humi"]
        Dust = data["dust"]
        Co = data["co"]
        print(pretty_data)
        
    except KeyError as error_format_json:
        print("Error Format JSON:", str(error_format_json))
    except json.JSONDecodeError as error_parsing_json:
        print("Error parsing JSON:", str(error_parsing_json))
        
# Create a client instance
client = mqtt.Client()
client.on_connect = on_connect # Attach the message function to callback
client.on_message = on_message # Attach the message function to callback
client.connect("103.150.93.184", 1883) # Connect to (broker, port)
client.loop_start() # Process network traffic and dispatch callbacks
Temp = ""
Humi = ""
Dust = ""
Co = ""
last_publish_time = time.time()

while True:
    _, img = cap.read() 
    height, width,_ = img.shape
    waktu_csv = time.strftime("%d/%m/%Y;%H:%M:%S", time.localtime())
    waktu_img = time.strftime("%d_%m_%Y %H-%M-%S", time.localtime())  
    interval = 10  # Interval dalam detik (5 menit)
    current_time = time.time()
    if current_time - last_publish_time >= interval:
        save_image(img,waktu_img)
        with open(csv_path, mode='a', newline='') as file_csv:
            writer = csv.writer(file_csv)
            writer.writerow([waktu_csv+";"+str(Temp)+";"+str(Humi)+";"+str(Dust)+";"+str(Co)])
        last_publish_time = current_time
    cv2.imshow('Image', img)
    key = cv2.waitKey(1)
    if key==27:
        break
client.loop_stop() # Stop network loop
cap.release()
cv2.destroyAllWindows()
