#------------------------------------------
#--- This code relies on store_Sensor_Data_to_DB.py. If you change the Topic - make appropriate changes 
#--- in the store_Sensor_Data_to_DB.py code as well.
#--- Date: 14th January 2018
#--- This code was inherited from 
#--- https://iotbytes.wordpress.com/store-mqtt-data-from-sensors-into-sql-database/
#------------------------------------------

# Use this code to Subscribe to a certain topic from the mqtt broker Cloudmqtt.com
# The topic I am interested is PublishTopic and Temperature.
# The data should be first published from the device to the cloud - in order to receive by doing a subscribe here.
# 1. Let the device send data to the Cloud Broker.
# 2. Validate that the data is being received on the broker's WebsocketUI console.
# 3. Run this code to receive the events from the Cloud mqtt broker.

# If this does not work - check the MQTT_Broker, Port, and the credentials.
# If there is no events received that may mean the broker has not received any data.

import paho.mqtt.client as mqtt
from store_Sensor_Data_to_DB import sensor_Data_Handler

# MQTT Settings 
#MQTT_Broker = "broker.mqttdashboard.com"
MQTT_Broker = "m12.cloudmqtt.com"
MQTT_Port = 19757
Keep_Alive_Interval = 45
MQTT_Topic = "PublishTopic/Temperature"

#Subscribe to all Sensors at Base Topic
def on_connect(mosq, obj,flags, rc):
    mqttc.subscribe(MQTT_Topic, 0)

#Save Data into DB Table
def on_message(mosq, obj, msg):
    # This is the Master Call for saving MQTT Data into DB
    # For details of "sensor_Data_Handler" function please refer "sensor_data_to_db.py"
    print "MQTT Data Received..."
    print "MQTT Topic: " + msg.topic  
    print "Data: " + msg.payload
    sensor_Data_Handler(msg.topic, msg.payload)

def on_subscribe(mosq, obj, mid, granted_qos):
    pass

mqttc = mqtt.Client()

# Assign event callbacks
mqttc.on_message = on_message
mqttc.on_connect = on_connect
mqttc.on_subscribe = on_subscribe

# Connect
mqttc.username_pw_set("oxefqvkn" , "aKpQPSFiTpXp")
mqttc.connect(MQTT_Broker, int(MQTT_Port), int(Keep_Alive_Interval))

# Continue the network loop
mqttc.loop_forever()
