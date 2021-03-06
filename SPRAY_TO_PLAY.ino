/*
   SPRAY_TO_PALY
   
   A water spout that is operated by a button
   press. The button does not initially work. 
   Also connected is the carnival game where a
   person uses a water gun to apply pressure to 
   a target. When a person plays the game and 
   hits the target at least every 2 seconds,
   the spout is enabled and can be used.  
   
   created 02/14/2020
   updated 03/30/20
   by Noah Kernis
*/

// button pins
const int spoutBtn = 2;
const int targetBtn = 3;
const int spout = 4;

const int debounce = 20;

// init button states
int targetBtnSate;
int spoutBtnSate;

bool isEnabled = false;

// for timer
unsigned long timeout = 2000;
unsigned long startTime;

void setup()
{
	Serial.begin(9600);

	startTime = millis();

	// initialize inputs
	pinMode(spoutBtn, INPUT_PULLUP);
	pinMode(targetBtn, INPUT_PULLUP);
	pinMode(spout, OUTPUT);
}

void loop()
{
	// read pins
	targetBtnSate = digitalRead(targetBtn);
	spoutBtnSate = digitalRead(spoutBtn);

	checkTarget();
	checkSpout();

	delay(debounce);
}

void checkTarget()
{
	if (targetBtnSate == LOW)
	{
		Serial.println("hit");
		setTimeout();
	}

	if (checkTimeout())
	{
		isEnabled = true;
	}
	else
	{
		isEnabled = false;
	}
}

void setTimeout()
{
	startTime = millis();
}

bool checkTimeout()
{
	// check if timeout occurred
	unsigned long now = millis();
	unsigned long elapsed = now - startTime;

	if (elapsed < timeout)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void checkSpout()
{
	if (spoutBtnSate == LOW)
	{
		Serial.println("please");
		if (isEnabled)
		{
			Serial.println("water");
			openSpout();
		}
	}
	else
	{
		closeSpout();
	}
}

void openSpout()
{
	digitalWrite(spout, HIGH);
}

void closeSpout()
{
	digitalWrite(spout, LOW);
}
