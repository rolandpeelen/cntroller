#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined(ARDUINO_ARCH_SAMD)
#include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"


/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

/* -------------------------- */
/* Generic Constants */
/* -------------------------- */
const int enableFactoryReset  = 1
const int PRESSED             = LOW;
const int tolerance           = 1;
const int joystickX           = A2;
const int joystickY           = A3;
const int joystickButton      = A4;

int inputPins[6]              = { 5, 6, 9, 10, 11, 12 };
char const *commands[6]       = { "VOLUME+", "VOLUME-", "MEDIANEXT", "MEDIAPREVIOUS", "VOLUME+", "VOLUME-" };

bool active(int tol, int x) {
	return x < (0 - tol) || x > (0 + tol);
};
/**************************************************************************/
/* Set things up */
/**************************************************************************/
void setup(void)
{
	/* while (!Serial); */
	delay(500);

	Serial.begin(115200);
	Serial.println("NavControls");
	Serial.println("---------------------------------------");

	/* Setup pins */
	pinMode(joystickButton, INPUT_PULLUP);

	/* Initialise bluetooth module  */
	Serial.print("Initialising the Bluefruit LE module: ");
	if ( !ble.begin(VERBOSE_MODE) )
	{
		Serial.println("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?");
		while(1); /* Hang when bluefruit couldn't be found */
	}

	Serial.println("OK!");

	/* Perform a factory reset to make sure everything is in a known state */
	if ( enableFactoryReset )
	{
		Serial.println("Performing a factory reset: ");
		ble.factoryReset();
	}

	/* Disable command echo from Bluefruit */
	ble.echo(false);

	/* Print Bluefruit information */
	Serial.println("Requesting Bluefruit info:");
	ble.info();

	/* Enable HID Service if not enabled */
	int32_t hidEnabled = 0;
	ble.sendCommandWithIntReply("AT+BleHIDEn", &hidEnabled);

	if (!hidEnabled)
	{
		Serial.println("Enable HID Service (including Keyboard): ");
		ble.sendCommandCheckOK("AT+BleHIDEn=On");

		/* Add or remove service requires a reset */
		Serial.println(F("Performing a SW reset (service changes require a reset): "));
		!ble.reset();
	}

	Serial.println("Go to your phone's Bluetooth settings to pair your device.");
	Serial.println("Then open an application that accepts keyboard input");

	/* Set device name */
	ble.println("AT+GAPDEVNAME=NavControls");
	ble.println("ATZ");
}

/* -------------------------- */
/* Loop */
/* -------------------------- */
void loop(void)
{
	if ( ble.isConnected() )
	{
		int joystickButtonValue = digitalRead(joystickButton);
		if (joystickButtonValue == PRESSED) {
			ble.println("AT+BLEHIDMOUSEBUTTON=L,CLICK");
			delay(100);
		};

		/* 
		   The "BLEHIDMOUSEMOVE" command takes (X,Y,SCROLL, PAN) as input. Ranged from -128 to +128.
		   We're getting back values from the analog input ranging from 0 to 1024. So we change them to the
		   required range
		 */
		int joystickXValue = (analogRead(joystickX) / 16) - 32;
		int joystickYValue = (analogRead(joystickY) / 16) - 32;
		/* 
			The input from the joystick is mostly not exactly 512, so we only move when a tolerance has been crossed.
		 */
		bool xActive = active(tolerance, joystickXValue);
		bool yActive = active(tolerance, joystickYValue);

		if(xActive || yActive) {
			ble.print("AT+BLEHIDMOUSEMOVE=");
			ble.print(joystickXValue);
			ble.print(",");
			ble.println(joystickYValue);
		}
	} 
}

