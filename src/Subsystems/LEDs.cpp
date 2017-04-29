/*
 * LEDs.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: adam
 */

#include "LEDs.h"
#include "../Commands/LEDs/LEDRefresh.h"
#include <algorithm>
#include <vector>

LEDs::LEDs(unsigned number) : Subsystem("LEDs") {
	// TODO Auto-generated constructor stub
	this->number = number;
	this->led_number = number;
	this->offset = 0;
	this->cycle = true;
	colors = new std::vector<struct color>(number);
	spif = fopen("/dev/spidev0.0", "wb");
	increment = 1;
	for(unsigned i = 0; i < number; i++){
		(*colors)[i].__brightness = 0xff;
		(*colors)[i].r = 0;
		(*colors)[i].g = 0;
		(*colors)[i].b = 0;
	}
	cycle_time = 1000;
	SmartDashboard::PutBoolean("LED RUNNING", false);
}

void LEDs::InitDefaultCommand(){
	SetDefaultCommand(new LEDRefresh());
}

LEDs::~LEDs() {
	delete colors;
	fclose(spif);
	// TODO Auto-generated destructor stub
}

void LEDs::ChangeMode(LEDMode mode)
{
	switch (mode)
	{
		case LEDMode::NONE:
			cycle_time = 1000;
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
				(*colors)[i].__brightness = 0xff;
				(*colors)[i].r = 0;
				(*colors)[i].g = 0;
				(*colors)[i].b = 0;
			}
			break;
		case LEDMode::RED:
			cycle_time = 1000;
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = 0xff;
					(*colors)[i].g = 0;
					(*colors)[i].b = 0;
			}
			break;
		case LEDMode::BLUE:
			cycle_time = 1000;
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = 0;
					(*colors)[i].g = 0;
					(*colors)[i].b = 0xff;
			}
			break;
		case LEDMode::GREEN:
			cycle_time = 1000;
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = 0;
					(*colors)[i].g = 0xff;
					(*colors)[i].b = 0;
			}
			break;
		case LEDMode::YELLOW:
			cycle_time = 1000;
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = 0xff;
					(*colors)[i].g = 0xff;
					(*colors)[i].b = 0;
			}
			break;
		case LEDMode::PURPLE:
			cycle_time = 1000;
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = 0xff;
					(*colors)[i].g = 0;
					(*colors)[i].b = 0xff;
			}
			break;
		case LEDMode::PATRIOTIC:
			cycle_time = 75;
			Resize(led_number * 2);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = (i < number * 2 / 3)? 0xff : 0;
					(*colors)[i].g = (i > number / 3 && i < number * 2 / 3)? 0xff : 0;
					(*colors)[i].b = (i > number / 3)? 0xff : 0;
			}
			break;
		case LEDMode::GREEN_BLINK:
			cycle_time = 100;
			Resize(led_number * 2);
			increment = led_number / 2;
			for (unsigned i = 0; i < number; i++)
			{
				(*colors)[i].__brightness = 0xff;
				(*colors)[i].r = 0;
				(*colors)[i].g = (i < led_number / 2 || (i > led_number && i < led_number * 3 / 2))? 0xff : 0;
				(*colors)[i].b = 0;
			}
			break;
		case LEDMode::RED_BLINK:
			cycle_time = 600;
			Resize((led_number | 3) + 1);// * 2);
			increment = 2;//led_number / 2;
			for (unsigned i = 0; i < number; i++)
			{
				(*colors)[i].__brightness = 0xff;
				(*colors)[i].r = ((i & 3) < 2) ? 0xff : 0;//(i < led_number / 2 || (i > led_number && i < led_number * 3 / 2))? 0xff : 0;
				(*colors)[i].g = 0;
				(*colors)[i].b = 0;
			}
			break;
	}
}

void LEDs::Refresh() {
	//fprintf(stderr, "refresh\n");
	if (cycle)
	{
		offset += increment;
		offset %= number;
	}
	struct color *c = colors->data();
//	for(unsigned i = 0; i < size; i += 128){
//		spi->Write(c + i, (unsigned char)std::min((unsigned)(size - i), (unsigned)128));
//	}
	fwrite("\x00\x00\x00\x00", 4, 1, spif);
	int a = 0, b = 0;
	if(number != offset) a = fwrite(c + offset, sizeof(struct color), number-offset, spif);
	if(offset != 0) b = fwrite(c, sizeof(struct color), offset, spif);
	//fprintf(stderr, "%d %d  %d %d %d\n", number, offset, a, b, a+b);

	fwrite("\xff\xff\xff\xff", 4, 1, spif);
	fflush(spif);
}

void LEDs::Resize(unsigned n){
	colors->resize(n);
	for(unsigned i = number; i < n; i++){
		(*colors)[i].__brightness = 0xff;
	}
	number = n;
}
