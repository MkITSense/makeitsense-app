# Mosquito MQTT

## Probar funcionamento 

### Raspberry Pi y Computadora

- Preparación
  
La computadora debe estar conectada al wifi del Raspberry pi

- Comandos

  - Raspberry Pi: `mosquitto_sub -d -v -t testTopic -h 192.168.4.1 -p 1883`
  - Computadora: `mosquitto_pub -d -t testTopic -m  "Hello world" -h 192.168.4.1 -p 1883`
