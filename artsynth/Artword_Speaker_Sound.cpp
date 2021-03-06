/* Artword_Speaker_Sound.cpp
 *
 * Copyright (C) 1992-2011,2015 Paul Boersma
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

#include "Artword_Speaker_Sound.h"
#include "Artword_Speaker.h"
#include "Art_Speaker.h"

Thing_define (Artword_Speaker_Sound_PlayInfo, Thing) {
	Artword artword;
	Speaker speaker;
	Graphics graphics;
};

Thing_implement (Artword_Speaker_Sound_PlayInfo, Thing, 0);

static int playCallback (Artword_Speaker_Sound_PlayInfo me, int /* phase */, double /* tmin */, double /* tmax */, double t) {
	static autoArt art;
	if (! art)
		art = Art_create ();
	Artword_intoArt (my artword, art.get(), t);
	Graphics_clearWs (my graphics);
	Art_Speaker_draw (art.get(), my speaker, my graphics);
	return 1;
}

void Artword_Speaker_Sound_movie (Artword artword, Speaker speaker, Sound sound, Graphics graphics) {
	try {
		static autoArtword_Speaker_Sound_PlayInfo info;
		if (! info)
			info = Thing_new (Artword_Speaker_Sound_PlayInfo);
		info -> artword = artword;
		info -> speaker = speaker;
		info -> graphics = graphics;
		if (sound) {
			Sound_play (sound, playCallback, info.get());
		} else {
			autoSound silence = Sound_createSimple (1, artword -> totalTime, 44100.0);
			Sound_play (silence.peek(), playCallback, info.get());
		}
	} catch (MelderError) {
		Melder_throw (artword, U" & ", speaker, U": movie not played.");
	}
}

/* End of file Artword_Speaker_Sound.cpp */
