#include <emscripten/bind.h>
#include "Sound.h"
#include "embind_Daata.h"
#include <memory>
#include "melder.h"
#include "MelderErrorGuard.h"

using namespace emscripten;

namespace js {
  std::unique_ptr<structSound> Sound_create (long numberOfChannels, double xmin, double xmax, long nx, double dx, double x1) {
    MelderErrorGuard guard;
    return ::Sound_create(numberOfChannels, xmin, xmax, nx, dx, x1);
  }

  std::unique_ptr<structSound> Sound_createSimple (long numberOfChannels, double duration, double samplingFrequency) {
    MelderErrorGuard guard;
    return ::Sound_createSimple(numberOfChannels, duration, samplingFrequency);
  }

  std::unique_ptr<structSound> Sound_createAsPureTone (long numberOfChannels, double startingTime, double endTime,
        double sampleRate, double frequency, double amplitude, double fadeInDuration, double fadeOutDuration)
  {
    MelderErrorGuard guard;
    return ::Sound_createAsPureTone(numberOfChannels, startingTime, endTime, sampleRate, frequency, amplitude, fadeInDuration, fadeOutDuration);
  }

  void Sound_writeToAudioFile (structSound& me, std::string filePath, int audioFileType, int numberOfBitsPerSamplePoint) {
    MelderErrorGuard guard;
    structMelderFile file = {0};
    Melder_pathToFile (Melder_peek8to32(filePath.c_str()), &file);
    ::Sound_writeToAudioFile(&me, &file, audioFileType, numberOfBitsPerSamplePoint);
  }

  std::unique_ptr<structSound> Sound_readFromSoundFile (std::string filePath) {
    MelderErrorGuard guard;    
    structMelderFile file = {0};
    Melder_pathToFile (Melder_peek8to32(filePath.c_str()), &file);
    return ::Sound_readFromSoundFile(&file);
  }
}

// Binding code
Daata_EMSCRIPTEN_BINDINGS(Sound) {
  constant("Melder_AIFF", Melder_AIFF);
  constant("Melder_AIFC", Melder_AIFC);
  constant("Melder_WAV", Melder_WAV);
  constant("Melder_NEXT_SUN", Melder_NEXT_SUN);
  constant("Melder_NIST", Melder_NIST);
  constant("Melder_FLAC", Melder_FLAC);
  constant("Melder_MP3", Melder_MP3);

  Daata_EMSCRIPTEN_BINDINGS_CLASS(Sound)
  .class_function("create", &js::Sound_create)
  .class_function("createSimple", &js::Sound_createSimple)
  .class_function("createAsPureTone", &js::Sound_createAsPureTone)
  .function("writeToAudioFile", &js::Sound_writeToAudioFile)
  .class_function("readFromSoundFile", &js::Sound_readFromSoundFile)
  ;
}