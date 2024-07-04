# MushroomHat
This is an Arduino-powered audio-responsive LED control module for a mushroom hat.

It uses an Arduino Nano with the ATMega32p chip (would work fine with the ATMega16p because it's a small program). 

The code specifies WS2812 RGB strips with 144 LEDs, broken up in groups of 16, with three groups for each of bass, midrange, and treble. There's pins for four 1W or brighter LEDs, which flash when audio spikes. When the audio spikes, the Arduino also increases the value it's writing to an LED which is coupled to an LDR, Vactrol-style, to adjust the gain of the audio circuitry.

The code could be modified to use different LED strips, more or fewer LEDs, and may NEED modification to work with the 1W LED driver I'll be building it with.

It will be powered by high-current batteries (a power bank plugged into the Arduino *will* make the circuit work, but the current will sag if you're using bright enough 1W LEDs). There's also a bipolar power module to be used by the audio circuitry, a microphone input circuit, and a (relatively) high-powered LED constant-current LED driver.

# Here's AliExpress product links that work as of July 4, 2024 #
[Microphone module](https://www.aliexpress.us/item/3256803832972502.html?spm=a2g0o.order_list.order_list_main.39.5a311802kwjAgN&gatewayAdapt=glo2usa)

[Bipolar boost power module 12V](https://www.aliexpress.us/item/3256805006736981.html?spm=a2g0o.order_list.order_list_main.129.5a311802kwjAgN&gatewayAdapt=glo2usa)

[LED constant current driver](https://www.aliexpress.us/item/3256805730202828.html?spm=a2g0o.order_list.order_list_main.158.5a311802kwjAgN&gatewayAdapt=glo2usa)

[RGB LED strip (project uses 144 LEDs)](https://www.aliexpress.us/item/3256805387967621.html?spm=a2g0o.order_list.order_list_main.171.5a311802kwjAgN&gatewayAdapt=glo2usa)

Uses a micro-toggle switch, 3 sealed-style potentiometers, a Thonkiconn-style 3.5mm audio jack to plug in an audio signal (interrupts the mic signal when plugged in), there's pads to connect other 5V devices like more LED strings (twinkle-lights) or a fan or two.
