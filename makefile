# File: makefile

# Makefile for Praat.
# Paul Boersma, 14 January 2012

# System-dependent definitions of CC, LIBS, ICON and MAIN_ICON should be in
# makefile.defs, which has to be copied and renamed
# from a suitable makefile.defs.XXX file in the makefiles directory,
# Perhaps that file requires some editing.

all:

.PHONY: platform_postbuild platform_clean

PRAAT_MODULES = fon/libfon.a \
		contrib/ola/libOla.a artsynth/libartsynth.a \
		FFNet/libFFNet.a gram/libgram.a EEG/libEEG.a \
		LPC/libLPC.a dwtools/libdwtools.a \
		fon/libfon.a stat/libstat.a dwsys/libdwsys.a \
		sys/libsys.a num/libnum.a kar/libkar.a \
		external/espeak/libespeak.a external/portaudio/libportaudio.a \
		external/flac/libflac.a external/mp3/libmp3.a \
		external/glpk/libglpk.a external/gsl/libgsl.a
		
include makefile.defs

all: $(EXECUTABLE) platform_postbuild

# Makes the Praat executable in the source directory.

$(EXECUTABLE): main/main_Praat.o $(MAIN_ICON) $(PRAAT_MODULES)
	$(LINK) -o $(EXECUTABLE) $+ $(LIBS)

external/gsl/libgsl.a:	
	$(MAKE) -C external/gsl

external/glpk/libglpk.a:
	$(MAKE) -C external/glpk

external/mp3/libmp3.a:
	$(MAKE) -C external/mp3

external/flac/libflac.a:
	$(MAKE) -C external/flac

external/portaudio/libportaudio.a:
	$(MAKE) -C external/portaudio

external/espeak/libespeak.a:
	$(MAKE) -C external/espeak

kar/libkar.a:
	$(MAKE) -C kar

num/libnum.a:
	$(MAKE) -C num

sys/libsys.a:
	$(MAKE) -C sys

dwsys/libdwsys.a:
	$(MAKE) -C dwsys

stat/libstat.a:
	$(MAKE) -C stat

fon/libfon.a:
	$(MAKE) -C fon

dwtools/libdwtools.a:
	$(MAKE) -C dwtools

LPC/libLPC.a:
	$(MAKE) -C LPC

EEG/libEEG.a:
	$(MAKE) -C EEG

gram/libgram.a:
	$(MAKE) -C gram

FFNet/libFFNet.a:
	$(MAKE) -C FFNet

artsynth/libartsynth.a:
	$(MAKE) -C artsynth

contrib/ola/libOla.a:
	$(MAKE) -C contrib/ola

main/main_Praat.o: $(ICON)
	$(MAKE) -C main main_Praat.o $(ICON)


clean: platform_clean
	$(MAKE) -C external/gsl clean
	$(MAKE) -C external/glpk clean
	$(MAKE) -C external/mp3 clean
	$(MAKE) -C external/flac clean
	$(MAKE) -C external/portaudio clean
	$(MAKE) -C external/espeak clean
	$(MAKE) -C kar clean
	$(MAKE) -C num clean
	$(MAKE) -C sys clean
	$(MAKE) -C dwsys clean
	$(MAKE) -C stat clean
	$(MAKE) -C fon clean
	$(MAKE) -C dwtools clean
	$(MAKE) -C LPC clean
	$(MAKE) -C EEG clean
	$(MAKE) -C gram clean
	$(MAKE) -C FFNet clean
	$(MAKE) -C artsynth clean
	$(MAKE) -C contrib/ola clean
	$(MAKE) -C main clean
	$(RM) $(EXECUTABLE)
