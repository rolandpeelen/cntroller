# RallyBlitz Remote Boards DIY Instructions, v1.2

Arduino Sketch: RallyBlitzBFruitV1_0.ino
This code tested on an Bluefruit Feather 32u4. Should also work on Feather M0.

## Setup
1. Arduino IDE needs to be installed and configured. Find at
www.arduino.cc You will need to change a setting in the preferences
(Files/Preferences). This text (without quotes)
"https://adafruit.github.io/arduino-boardindex/package_adafruit_index.json" needs to be added to the Additional
Boards Manager URLs: field at the bottom of the Settings tab.

2. Close Arduino app.

3. AdaFruit/Bluefruit Library (like printer drivers) need to be added to
the IDE. Find the instructions here:
- Windows: https://learn.adafruit.com/adafruit-feather-32u4-bluefruitle/pinouts?view=all#installing-ble-library 
- - Mac OSX: https://learn.adafruit.com/adafruit-all-about-arduinolibraries-install-use/installing-a-library-on-mac-osx 
- Make sure if you have unzipped the file that it isn't buried 2 folders deep when you copy it over (...Libraries\Adafruit_Bluefruit\Adafruit_BlueFruit\.... is bad, only one
folder deep). Also be careful that the folder name doesn't have spaces
or dashes in it, underscores are okay.
A common source of confusion on Windows and Mac machines, your sketchbook
folder is not named "sketchbook" it is named "Arduino". For Windows it is
created the first time you start the Arduino app and is in your C:/My
Documents folder.

4. Create a folder called RallyBlitzBFruitV1_0 It needs to be in the
Arduino IDE folder called "Libraries". This is the same folder as
above. You should have both the RallyBlitzBFruitV1_0 folder and the
Adafruit_BlueFruitLE_nRF51_Master folders in the same place
5. Open files from Rally Blitz website titled:
`RallyBlitzBFruitV1_0.docx`
`BluefruitConfig.doc`

6. Open and copy the content from each of the two files above and paste
them into new files to be save as the following names. Cutting and
pasting into Notepad or similar is an easy way to save the files with the
correct file names and extensions. These files need to be saved into the
RallyBlitzBFruitV1_0 folder you created above. Those will be the only
two files in this folder. The names must match below exactly.
RallyBlitzBFruitV1_0.ino
BluefruitConfig.h

7. Double click the .ino file and the Arduino app will launch and
automatically load both files into the sketch window. You should see two
tabs at the the top with both file names from the RallyBlitz folder.

8. Plug the Feather into the PC via USB, after the drivers install you
will need to go to Tools -->Board:-->Board Manager. Pick "Contributed" in
the drop down and then find and click in the Adafruit AVR Boards section,
click Install. (If using the M0 find the Adafruit SAMD Boards and
install that instead).

9. Change to the correct board type, Tools -->Board: and scroll down to find Adafruit Feather 32u4 and selelct it. (or Feather M0 if using that instead).

10. In the Arduino Menu under Tools --> Port, select the port with the Feather connected.

11. Upload the Sketch with Control+U (or find the button or menu item saying the same).

12. Pair device with iDevice using name "RallyBlitz Control".

13. If using two iDevices (RB Nav and RB RB) and need two Bluefruit boards, power up and pair devices one at a time. Devices will keep pairing until the boards are "forgotten" from the iOS BT menu.  

## DIY Switch Build Notes.
Buttons need to be wired between the pinouts and ground
Pins 5 and 11 = ODO + 0.10
Pins 6 and 12 = OOD - 0.10
Pin 9 = Advance Roadbook
Pin 10 = Rewind Roadbook

Li_PO Battery can be plugged into Feather board - Will charge and
run at the same time with USB connected. 100 mAh batt will run the board
for approx 12 hours before needing a recharge.
