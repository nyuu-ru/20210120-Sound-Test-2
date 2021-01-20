/*
 * Generator.h
 *
 *  Created on: 20 янв. 2021 г.
 *      Author: unyuu
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <cmath>
static constexpr double Pi = acos(-1.);

class Generator
{
protected:
	double _frequency { 0. };
	double _time { 0. };

public:
	virtual ~Generator() = default;

	virtual void set_frequency(double f)
	{
		if (f >= 0.) _frequency = f;
	}

	virtual double next_sample()
	{
		_time += 1. / AudioDriver::SAMPLING_FREQ;
		return 0.;
	}
};

class SquareWaveGenerator: public Generator
{
public:
	virtual ~SquareWaveGenerator() = default;

	virtual double next_sample() override
	{
		double result = (sin(2. * Pi * _frequency * _time) > 0)? 1.0 : -1.0;
		Generator::next_sample();
		return result;
	}
};



#endif /* GENERATOR_H_ */
