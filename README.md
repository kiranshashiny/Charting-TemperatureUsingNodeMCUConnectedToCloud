# Charting Temperature Using NodeMCU Connected To a MQTT Broker 'cloudmqtt.com'
This blog is about how to publish and subscribe Temperature and Humidity to the a MQTT Broker in the cloud
and how to subscribe to the data and insert into a SQL db.
A simple python flask app is used to chart the data.


Parts needed

        NodeMCU
        DHT11
        Router
        Internet connection
        Some knowledge of C/C++, Python programming.
        MQTT basic understanding.

        Arduino IDE installed to compile and Upload code to NodeMCU
        NodeMCU Pin Diagram familiarity
        An Android Smartphone to subscribe to events from cloud
        An account with cloudmqtt.com MQTT Broker

A Typical NodeMCU and Pin diagram:

<img width="511" alt="screen shot 2018-01-06 at 10 18 10 pm" src="https://user-images.githubusercontent.com/14288989/34641820-d391c96a-f32f-11e7-80c1-a1185c0fe3a4.png">

DHT 11 temperature sensor that was used for this demo.

<img width="400" alt="screen shot 2018-01-06 at 10 19 36 pm" src="https://user-images.githubusercontent.com/14288989/34641819-d351345e-f32f-11e7-88bd-53d559caba2b.png">

The Charting that was showing the Temperature in the web portal.

<img width="1435" alt="screen shot 2018-01-06 at 10 19 51 pm" src="https://user-images.githubusercontent.com/14288989/34641818-d312d8e4-f32f-11e7-96c2-76a22d25cd11.png">


Setup :


Connections


Publish code in Arduino


Client code to subscribe in Python



Database setup.


References :

https://iotbytes.wordpress.com/store-mqtt-data-from-sensors-into-sql-database/

https://www.fontenay-ronan.fr/dynamic-charts-with-highcharts-sqlite-and-python/

https://github.com/esp8266/Arduino

