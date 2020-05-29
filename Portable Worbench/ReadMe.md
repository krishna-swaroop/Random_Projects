# Portable Electronics Workbench
This is a quarantine project made so that I could tinker with stuff without access to a lab. This has a DIY
power supply, DIY oscilloscope, RPi desktop system, electronic component dispenser all packaged into a trash can with a single connection
to 230V single phase AC mains supply.

## Components
List of modules in the trash can- 
1. ATX Power Supply 
2. DIY Oscilloscope 
3. Component dispenser 
4. Soldering station 
5. Raspberry Pi Desktop Station

### ATX Power Supply
A cheap DIY power supply can be made from ATX power supplies found in old PCs. Minor modifications to the connections are to be made to get
it up and running. [This tutorial](https://www.electronics-tutorials.ws/blog/convert-atx-psu-to-bench-supply.html) is a great place to start
to make your own Bench supply.

TODO: Add Pictures of the finished prototype.

### DIY Oscilloscope
This module uses the ADC in an Arduino Uno in conjunction with a Python script running on the Raspberry Pi desktop environment and peripheral
circuitry to act as a basic Oscilloscope. The relevant schematics and scripts can be found [here](https://github.com/krishna-swaroop/Random_Projects/tree/master/RPi/DIY%20Oscilloscope)
TODO: Add Pictures and schematics to the other folder.


### Component Dispenser
Just a physical container full of passive components and relevant ICs.

### Soldering Station
This module contains a basic soldering station drawing power from a power spike embedded in the trashcan with necessary safety circuits and fuses.

### Raspberry Pi Desktop Station
Contains a Raspberry Pi4 4GB Single Board Computer (SBC) running the latest version of Raspbian OS. This desktop environment is for running
oscilloscope software and to maintain wireless connectivity in case I decide to add more modules. Setting up a Raspbian enviroment is 
well documented on the internet.


