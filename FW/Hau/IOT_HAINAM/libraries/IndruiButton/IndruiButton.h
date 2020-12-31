

#ifndef IndruiButton_h
#define IndruiButton_h

#include <Arduino.h>

#define COUNT_FALLING 0
#define COUNT_RISING  1
#define COUNT_BOTH    2

class IndruiButton
{
	private:
		int btnPin;
		unsigned long debounceTime;
		unsigned long count;
		int countMode;

		int previousSteadyState;  // the previous steady state from the input pin, used to detect pressed and released event
		int lastSteadyState;      // the last steady state from the input pin
		int lastFlickerableState; // the last flickerable state from the input pin
		int currentState;         // the current reading from the input pin

		unsigned long lastDebounceTime; // the last time the output pin was toggled

	public:
		IndruiButton(int pin);
		void setDebounceTime(unsigned long time);
		int getState(void);
		int getStateRaw(void);
		bool isPressed(void);
		bool isReleased(void);
		void setCountMode(int mode);
		unsigned long getCount(void);
		void resetCount(void);
		void loop(void);
};




#endif
