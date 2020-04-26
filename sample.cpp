// Copyright 2020 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <cstdio>

#include "dsp/Spectrogram.hpp"
#include "dsp/SynthesizeImpulseResponse.hpp"
#include "dsp/SynthesizePhrase.hpp"

// This is a sample to use dsp directory.
int main()
{
    int fftSize = 1024;
    int f0Length = 1000;
    NaiveSpectrogram spectrogram((unsigned int)f0Length, (unsigned int)fftSize, /* msFramePeriod = */ 1.0);

    /* Analyze and create WORLD spectrogram here. */

    int waveLength = 44100;
    int samplingFrequency = 44100;
    double *wave = new double[waveLength];
    for(int i = 0; i < waveLength; i++) {
        wave[i] = 0.0;
    }

    SynthesizeImpulseResponseWithWORLD irs(spectrogram.fftSize(), samplingFrequency);
    SynthesizePhraseWithWORLD synthesize(&irs, /* f0Floor = */ 71.0, /* f0Default = */ 500.0);

    PhraseSignal s(wave, /* indexMin = */ 0, /* indexMax = */ waveLength, samplingFrequency);
    PhraseParameters p(&spectrogram, /* startPhase = */ 0.0, /* startFractionalTimeShift = */ 0.0);

    synthesize(&s, &p);

    /* Save wave as wav file here. */
}
