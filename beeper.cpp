/*
 * beeper.cpp
 *
 *  Created on: Oct 15, 2025
 *      Author: Oleksiy
 */
#include "beeper.hpp"

using namespace nikolex;

void Beeper::setMelody(Bip * melody, uint32_t size){
	_melody = melody;
	_size = size;
}


void Beeper::nextBip(){
	index++;
	if(index < _size){

	}
	else {
		index = 0;
		finish();
	}
}


void Beeper::play(void (* callback)(void)){
	playFinishedCb = callback;
	mode = ONCE;
	playWith(getTick());
}


void Beeper::playWith(uint32_t time){
	index = 0;
	startTime = time;
	uint32_t lastTime = startTime;
	for(uint8_t i = 0; i < _size; i++){
		times[i].bip = lastTime + _melody[i].bip;
		lastTime = lastTime +_melody[i].bip + _melody[i].pause;
		times[i].pause = lastTime;
	}
}


void Beeper::on(){
	if(_active == LOW) _pin.setLow();
	else _pin.setHigh();
}


void Beeper::off(){
	if(_active == LOW) _pin.setHigh();
	else _pin.setLow();
}


void Beeper::play_infinity(){
	mode = INFINITE;
	playWith(getTick());
}


void Beeper::loop(){
	if(mode == STOP) {
		off();
		return;
	}
	uint32_t now = getTick();

	if(now < times[index].bip && now > startTime){
		on();
	}
	else if(now >= times[index].bip && now < times[index].pause){
		off();
	}
	else if(now >= times[index].pause){
		nextBip();
	}
}


void Beeper::finish(){
	uint32_t now = getTick();
	off();

	if(mode == INFINITE){
		playWith(now + 3000);
	}
	if(mode == ONCE){
		stop();
		if(playFinishedCb) playFinishedCb();
	}
}
