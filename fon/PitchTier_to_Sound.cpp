/* PitchTier_to_Sound.cpp
 *
 * Copyright (C) 1992-2011 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * pb 2004/10/03 sine wave generation
 * pb 2005/07/08 PitchTier_to_Sound_phonation
 * pb 2006/12/30 new Sound_create API
 * pb 2007/02/25 changed default sampling frequency to 44100 Hz
 * pb 2008/01/19 double
 * pb 2011/06/05 C++
 */

#include "PitchTier_to_Sound.h"
#include "PitchTier_to_PointProcess.h"
#include "PointProcess_and_Sound.h"

autoSound PitchTier_to_Sound_pulseTrain (PitchTier me, double samplingFrequency,
	 double adaptFactor, double adaptTime, long interpolationDepth, bool hum)
{
	static double formant [1 + 6] = { 0.0, 600.0, 1400.0, 2400.0, 3400.0, 4500.0, 5500.0 };
	static double bandwidth [1 + 6] = { 0.0, 50.0, 100.0, 200.0, 300.0, 400.0, 500.0 };
	try {
		autoPointProcess point = PitchTier_to_PointProcess (me);
		autoSound sound = PointProcess_to_Sound_pulseTrain (point.peek(), samplingFrequency, adaptFactor, adaptTime, interpolationDepth);
		if (hum) {
			Sound_filterWithFormants (sound.peek(), 0.0, 0.0, 6, formant, bandwidth);
		}
		return sound;
	} catch (MelderError) {
		Melder_throw (me, U": not converted to Sound (pulse train).");
	}
}

autoSound PitchTier_to_Sound_phonation (PitchTier me, double samplingFrequency,
	 double adaptFactor, double maximumPeriod, double openPhase, double collisionPhase, double power1, double power2, bool hum)
{
	static double formant [1 + 6] = { 0.0, 600.0, 1400.0, 2400.0, 3400.0, 4500.0, 5500.0 };
	static double bandwidth [1 + 6] = { 0.0, 50.0, 100.0, 200.0, 300.0, 400.0, 500.0 };
	try {
		autoPointProcess point = PitchTier_to_PointProcess (me);
		autoSound sound = PointProcess_to_Sound_phonation (point.peek(), samplingFrequency, adaptFactor,
			maximumPeriod, openPhase, collisionPhase, power1, power2);
		if (hum) {
			Sound_filterWithFormants (sound.peek(), 0.0, 0.0, 6, formant, bandwidth);
		}
		return sound;
	} catch (MelderError) {
		Melder_throw (me, U": not converted to Sound (phonation).");
	}
}

void PitchTier_playPart (PitchTier me, double tmin, double tmax, bool hum) {
	try {
		autoSound sound = PitchTier_to_Sound_pulseTrain (me, 44100.0, 0.7, 0.05, 30, hum);
		Sound_playPart (sound.peek(), tmin, tmax, nullptr, nullptr);
	} catch (MelderError) {
		Melder_throw (me, U": not played.");
	}
}

void PitchTier_play (PitchTier me) {
	PitchTier_playPart (me, my xmin, my xmax, false);
}

void PitchTier_hum (PitchTier me) {
	PitchTier_playPart (me, my xmin, my xmax, true);
}

autoSound PitchTier_to_Sound_sine (PitchTier me, double tmin, double tmax, double samplingFrequency) {
	try {
		if (tmax <= tmin) tmin = my xmin, tmax = my xmax;
		long numberOfSamples = 1 + (long) floor ((my xmax - my xmin) * samplingFrequency);   // >= 1
		double samplingPeriod = 1.0 / samplingFrequency;
		double tmid = (tmin + tmax) / 2.0;
		double t1 = tmid - 0.5 * (numberOfSamples - 1) * samplingPeriod;
		autoSound thee = Sound_create (1, tmin, tmax, numberOfSamples, samplingPeriod, t1);
		double phase = 0.0;
		for (long isamp = 2; isamp <= numberOfSamples; isamp ++) {
			double tleft = t1 + (isamp - 1.5) * samplingPeriod;
			double fleft = RealTier_getValueAtTime (me, tleft);
			phase += fleft * thy dx;
			thy z [1] [isamp] = 0.5 * sin (2.0 * NUMpi * phase);
		}
		return thee;
	} catch (MelderError) {
		Melder_throw (me, U": not converted to Sound (sine).");
	}
}

void PitchTier_playPart_sine (PitchTier me, double tmin, double tmax) {
	try {
		if (tmax <= tmin) { tmin = my xmin; tmax = my xmax; }   // autowindowing
		autoSound sound = PitchTier_to_Sound_sine (me, tmin, tmax, 44100.0);
		Sound_playPart (sound.peek(), tmin, tmax, nullptr, nullptr);
	} catch (MelderError) {
		Melder_throw (me, U": not played.");
	}
}

/* End of file PitchTier_to_Sound.cpp */
