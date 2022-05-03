# App Flowmeter

Aplicación para medir el flujo de agua que pasa por el sensor. La aplicación muestra en pantalla

- El estado del dispositivo
- La velocidad del flujo
- El tiempo transcurrido
- Los litros consumidos

## Materiales

- Sparkfun ESP8266
- Display OLED 0.96 pulgadas
- Sensor de flujo de agua yf-s201

## Diagrana de conexión
 - [Diagrama esquemático en formato EasyEda](../img/schematic_caudalimetro.png)
 - [Diagrama EasyEda (cuenta personal)](https://easyeda.com/editor#id=051b62ef4045476d9a8eab23de744013)

## Código fuente

Ejemplo para probar la app, disponible también en su [carpeta de trabajo](../lib/APP_Flowmeter/)

## Notas
- En esta app no se debe utilizar `Serial.print()` ya que la aplicación [dejaría de funcionar](https://arduino.stackexchange.com/questions/46595/sending-serial-data-in-an-interrupt) ya que no se pueden utilizar con interrupciones.
- El tipo de retorno de la función `pulseCounter()` debe ser `void ICACHE_RAM_ATTR` y se debe prestar atención a la versión que se utiliza ya que en algunas pudiera no funcionar.