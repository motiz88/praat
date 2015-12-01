#ifndef _LongSound_h_
#define _LongSound_h_
/* LongSound.h
 *
 * Copyright (C) 1992-2012,2015 Paul Boersma, 2007 Erez Volk (for FLAC, MP3)
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

#include "Sound.h"
#include "Collection.h"

#define COMPRESSED_MODE_READ_FLOAT 0
#define COMPRESSED_MODE_READ_SHORT 1

#if !defined(DISABLE_FLAC)
struct FLAC__StreamDecoder;
struct FLAC__StreamEncoder;
#endif
#if !defined(DISABLE_MP3)
struct _MP3_FILE;
#endif
Thing_define (LongSound, Sampled) {
	structMelderFile file;
	FILE *f;
	int audioFileType, numberOfChannels, encoding, numberOfBytesPerSamplePoint;
	double sampleRate;
	long startOfData;
	double bufferLength;
	int16 *buffer;   // this is always 16-bit, because will always play sounds in 16-bit, even those from 24-bit files
	long imin, imax, nmax;
	#if !defined(DISABLE_FLAC)
	struct FLAC__StreamDecoder *flacDecoder;
	#else
	void *flacDecoder_reserved;
	#endif
	#if !defined(DISABLE_MP3)	
	struct _MP3_FILE *mp3f;
	#else
	void *mp3f_reserved;
	#endif
	int compressedMode;
	long compressedSamplesLeft;
	double *compressedFloats [2];
	int16 *compressedShorts;

	void v_destroy ()
		override;
	void v_info ()
		override;
	void v_copy (Daata data_to)
		override;
	bool v_writable ()
		override { return false; }
	int v_domainQuantity ()
		override { return MelderQuantity_TIME_SECONDS; }
};

autoLongSound LongSound_open (MelderFile file);

autoSound LongSound_extractPart (LongSound me, double tmin, double tmax, int preserveTimes);

bool LongSound_haveWindow (LongSound me, double tmin, double tmax);
/*
 * Returns 0 if error or if window exceeds buffer, otherwise 1;
 */

void LongSound_getWindowExtrema (LongSound me, double tmin, double tmax, int channel, double *minimum, double *maximum);

void LongSound_playPart (LongSound me, double tmin, double tmax,
	Sound_PlayCallback callback, Thing boss);

void LongSound_writePartToAudioFile (LongSound me, int audioFileType, double tmin, double tmax, MelderFile file, int numberOfBitsPerSamplePoint);
void LongSound_writeChannelToAudioFile (LongSound me, int audioFileType, int channel, MelderFile file);

void LongSound_readAudioToFloat (LongSound me, double **buffer, long firstSample, long numberOfSamples);
void LongSound_readAudioToShort (LongSound me, int16 *buffer, long firstSample, long numberOfSamples);

void LongSound_concatenate (Collection collection, MelderFile file, int audioFileType, int numberOfBitsPerSamplePoint);
/* Concatenate a collection of Sound and LongSound objects. */

void LongSound_preferences ();
long LongSound_getBufferSizePref_seconds ();
void LongSound_setBufferSizePref_seconds (long size);

/* End of file LongSound.h */
#endif
