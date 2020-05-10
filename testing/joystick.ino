/* -------------------------- */
/* Generic Constants */
/* -------------------------- */
const int PRESSED        = LOW;
const int tolerance      = 15;

/* -------------------------- */
/* Pins */
/* -------------------------- */
const int buttonOne      = A0;
const int buttonTwo      = A1;
const int joystickX      = A2;
const int joystickY      = A3;
const int joystickButton = A4;

/* -------------------------- */
/* Helper Functions */
/* -------------------------- */
bool active(int tol, int x) {
	return x < (0 - tol) || x > (0 + tol);
};

/* -------------------------- */
/* Meat 'n Potatoes */
/* -------------------------- */
void setup() {
	Serial.begin(115200);
	Serial.println(F("Starting"));

	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(buttonOne, INPUT_PULLUP);
	pinMode(buttonTwo, INPUT_PULLUP);
	pinMode(joystickButton, INPUT_PULLUP);
}

void loop() {
	/* -------------------------- */
	/* Buttons */
	/* -------------------------- */
	int buttonOneValue = digitalRead(buttonOne);
	int buttonTwoValue = digitalRead(buttonTwo);

	if (buttonOneValue == PRESSED) {
		Serial.println("One");
		digitalWrite(LED_BUILTIN, HIGH);
	};

	if (buttonTwoValue == PRESSED) {
		Serial.println("Two");
		digitalWrite(LED_BUILTIN, HIGH);
	};


	/* -------------------------- */
	/* Joysticks */
	/* -------------------------- */
	int joystickButtonValue = digitalRead(joystickButton);
	int joystickXValue = analogRead(joystickX) - 512;
	int joystickYValue = analogRead(joystickY) - 512;
	bool xActive = active(tolerance, joystickXValue);
	bool yActive = active(tolerance, joystickYValue);

	if (joystickButtonValue == PRESSED) {
		digitalWrite(LED_BUILTIN, HIGH);
		Serial.println("Joystick");
	};
	if(xActive || yActive) {
		Serial.print("X: ");
		Serial.print(joystickXValue);
		Serial.print(", ");
		Serial.print("Y: ");
		Serial.print(joystickYValue);
		Serial.println("");
	}

	Serial.println("- ");
	delay(100);
}
