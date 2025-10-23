/*
 * beeper.hpp
 *
 *  Created on: Oct 15, 2025
 *      Author: Oleksiy
 */

#ifndef BEEPER_BEEPER_HPP_
#define BEEPER_BEEPER_HPP_

#include <cstdint>
#include "../interfaces/output_pin.hpp"


namespace nikolex {

class Beeper {

public:

	struct Bip{
		uint32_t bip;
		uint32_t pause;
	};

	enum Mode{
		STOP,
		ONCE,
		INFINITE,
	};

	enum Active{
		LOW,
		HIGH
	};

private:


	OutputPin& _pin;
	uint32_t(* getTick)(void);
	Bip* _melody;
	uint32_t _size;
	uint8_t index = 0;
	uint32_t startTime;
	void (*playFinishedCb)(void);
	Mode mode = ONCE;
	Active _active;
	Bip times[10];

	void playWith(uint32_t time);
	void finish();


public:

	Beeper(OutputPin& pin, uint32_t(* getTickFn)(void), Active active = LOW):
		_pin(pin),
		getTick(getTickFn),
		_active(active)
	{}

	void on();
	void off();
	void setMelody(Bip * melody, uint32_t size);
	void nextBip();
	void play(void (* callback)(void) = nullptr);
	void play_infinity();
	void loop();
	void stop(){ mode = STOP;}
	Mode getMode(){ return mode; }

	virtual ~Beeper(){};
};

};



#endif /* BEEPER_BEEPER_HPP_ */
