Darien Maynard 620133775

# Lab 5

## Controlling LEDs using Arduino and HTTP

This code is used for an ESP32 board to control the state of three LEDs by making a GET request to a server and using the response to set the LED states.


This code controls three LEDs by connecting to a server over WiFi. It's written in C++ and uses the Arduino framework to make it easy to work with the hardware.

To begin, the program sets up the pins that the LEDs are connected to and establishes a connection to a server using WiFi credentials stored in a separate file (env.h).

Then, the program enters a loop where it goes through all possible LED states. For each state, it updates the LEDs and sends a message to the server using HTTP PUT and JSON format to indicate the current state of the LEDs. The server's response, if any, is printed to the serial monitor.

After waiting for two seconds, the program moves on to the next state. Once all possible states have been sent to the server, the program closes the connection and starts over.