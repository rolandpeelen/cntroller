# Navigation Controller

## Introduction
I've been meaning to build a set of remote controls for navigation for a while now. Chris, from RallyBlitz, was kind enough to send me some links to his source-code. That will be the base for my own version.

## Roadmap / Plan / Ideas
- Make existing code-base work for own device 
- Try and 'identify' as mouse instead of keyboard, so we can do some scrolling 
  - Scrolling + PS2 style joypad control = inertia control, so we can scroll faster / slower, making it more natural
- See if we can get Gurumaps to follow suit and implement scrolling features

## Setup
Setup the Arduino-CLI with the following commands. Device needs to be plugged-in.
```sh
# Update Homebrew
brew update

# Install the Arduino-Cli
brew install arduino-cli

# Init an empty Config
arduino-cli config init

# Add the external board URL
'
In the Yaml file, Replace:

  additional_urls: []

With:

  additional_urls: 
    - https://raw.githubusercontent.com/rolandpeelen/cntroller/master/package_adafruit_index.json

Save / Exit
'
# Update the cli config
arduino-cli core update-index

# Install the correct adafruit package (run EITHER command)
arduino-cli core install adafruit:avr # For 32u4 bluefruit
arduino-cli core install adafruit:samd # For m0 feather boards

# Confirm USB (note the "Port")
arduino-cli board list

# Confirm package is installed (note the "FQBN")
arduino-cli board listall adafruit

# Compile (this command will look different for a different board. Doublecheck the FQBN!)
arduino-cli compile --fqbn adafruit:samd:adafruit_feather_m0 testing # Command structure: arduino-cli compile --fqbn #{FQBN} #{PROJECT_FILE_OR_FOLDER}

# Upload (this command will look different for a different board. Doublecheck the FQBN and PORT!)
arduino-cli upload -p /dev/cu.usbmodem101 --fqbn adafruit:samd:adafruit_feather_m0 testing # Command Structure: arduino-cli upload -p #{PORT} --fqbn #{FQBN} #{PROJECT_FILE_OR_FOLDER}

# Project should now be running
# Connect to USB Serial with screen
screen /dev/cu.usbmodem101 115200 # Command Structure: screen #{PORT} #{BAUDRATE}

# To disconnect, either press reset button on Arduino, or "CTRL+A" followed by typing ":quit"
```

# From Chris
## RallyBlitz Remote Boards DIY Instructions, v1.2

This code tested on an Bluefruit Feather 32u4. Should also work on Feather M0.

## Setup
### 1. Install Arduino
Arduino IDE needs to be installed and configured. Find at www.arduino.cc You will need to change a setting in the preferences (Files/Preferences). The file `package_adafruit_index.json` needs to be added to the Additional Boards Manager URLs: field at the bottom of the Settings tab.

### 2. Close Arduino App

### 3. Add Adafruit / Bluefruit Libraries
AdaFruit/Bluefruit Library (like printer drivers) need to be added to the IDE. Find the instructions here:

- [Windows](https://learn.adafruit.com/adafruit-feather-32u4-bluefruitle/pinouts?view=all#installing-ble-library)
- [Mac OSX](https://learn.adafruit.com/adafruit-all-about-arduinolibraries-install-use/installing-a-library-on-mac-osx)

Make sure if you have unzipped the file that it isn't buried 2 folders deep when you copy it over (...Libraries\Adafruit_Bluefruit\Adafruit_BlueFruit\.... is bad, only one folder deep). Also be careful that the folder name doesn't have spaces or dashes in it, underscores are okay.

A common source of confusion on Windows and Mac machines, your sketchbook folder is not named "sketchbook" it is named "Arduino". For Windows it is created the first time you start the Arduino app and is in your `C:/My Documents` folder.

### 4. Create Folder Structure
Create a folder called `RallyBlitzBFruitV1_0`. It needs to be in the Arduino IDE folder called `Libraries`. This is the same folder as above. You should have both the `RallyBlitzBFruitV1_0` folder and the `Adafruit_BlueFruitLE_nRF51_Master` folders in the same place 

### 5. Copy Files
Copy `RallyBlitzBFruitV1_0.ino` and `BluefruitConfig.h` into the `RallyBlitzBFruitV1_0`

### 6. Open App
Double click the .ino file and the Arduino app will launch and automatically load both files into the sketch window. You should see two tabs at the the top with both file names from the RallyBlitz folder.  
### 7. Configure Board for use with Arduino App
Plug the Feather into the PC via USB, after the drivers install you will need to go to Tools --> Board:--> Board Manager. Pick "Contributed" in the drop down and then find and click in the Adafruit AVR Boards section, click Install. (If using the M0 find the Adafruit SAMD Boards and install that instead).

### 8. Change Board Type
Change to the correct board type, Tools --> Board: and scroll down to find Adafruit Feather 32u4 and select it. (or Feather M0 if using that instead).

### 9. Change Port
In the Arduino Menu under Tools --> Port, select the port with the Feather connected.

### 10. Upload to Arduino
Upload the Sketch with Control+U (or find the button or menu item saying the same).

## Usage
### 1. Pairing
Pair device with iDevice using name "RallyBlitz Control".

### Side-note
If using two iDevices (RB Nav and RB RB) and need two Bluefruit boards, power up and pair devices one at a time. Devices will keep pairing until the boards are "forgotten" from the iOS BT menu.  

## DIY Switch Build Notes.
Buttons need to be wired between the pinouts and ground
Pins 5 and 11 = ODO + 0.10
Pins 6 and 12 = OOD - 0.10
Pin 9 = Advance Roadbook
Pin 10 = Rewind Roadbook

Li_PO Battery can be plugged into Feather board - Will charge and
run at the same time with USB connected. 100 mAh batt will run the board
for approx 12 hours before needing a recharge.
