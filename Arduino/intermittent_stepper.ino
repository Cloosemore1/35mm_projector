// Define pin connections & motor's steps per frame
const int stepPin = 10;
const int stepsPerFrame = 20; //10 frame/40 perf sprocket
const int stepsPerPerf = stepsPerFrame / 4;

void setup()
{
	// Declare pins as outputs
	pinMode(stepPin, OUTPUT);
}

void loop()
{
  //1,000,000 microseconds in one second, 24 frames per second
  //41,666 microseconds per frame (truncated but will result in less than 1 frame deviation over multiple hours)
  //31,266 microsecond dwell period per frame, 10,400 microsecond moving time
  //for 20 step frame movement, 10 steps for acceleration and 10 for decceleration
  //Average pulse period needs to be 10,400/20 = 520

  //Accelerating
  for (int i = 0; i < stepsPerFrame * 4; i += 8) { //pulse starts at 300, goes to 220, linear average is 260
    digitalWrite(stepPin, HIGH);
		delayMicroseconds(300 - i);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(300 - i);
  }
  //Deccelerating
  for (int i = stepsPerFrame * 4; i > 0; i -= 8) { //pulse starts at 220, goes to 300, linear average is 260
    digitalWrite(stepPin, HIGH);
		delayMicroseconds(300 - i);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(300 - i);
  }
	//Rest period for intermittent
	delayMicroseconds(31266);
}