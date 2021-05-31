// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.

#include <stdio.h>
#include <SynthesizeSegment.hpp>
#include "data/Waveform.hpp"
#include "spectrogram/StretchedPartialSpectrogram.hpp"
#include "spectrogram/WaveformSpectrogram.hpp"
#include "world/SynthesizeImpulseResponseWithWORLD.hpp"
#include "world/SynthesizeSegmentWithWORLD.hpp"

using namespace uzume::vocoder;
using namespace uzume::vocoder::world;

class SimpleDoubledTimeAxisMap : public uzume::vocoder::TimeAxisMap {
public:
    SimpleDoubledTimeAxisMap() = delete;
    SimpleDoubledTimeAxisMap(double msLength) : _msLength(msLength) { }
    ~SimpleDoubledTimeAxisMap() = default;
    double at(double ms) const { return ms / 2.0; }
    double msLength() const { return _msLength; }
private:
    const double _msLength;
};

int main(int argc, char *argv[]) {
    if(argc < 2 || 3 < argc) {
        printf("usage: uzume_vocoder_sample (in filepath) (out filepath)<optional>");
        exit(-1);
    }
    const char *inPath = argv[1];
    const char *outPath = argc == 3 ? argv[2] : "output.wav";

    // simply analyze spectrogram from waveform.
    auto *in = Waveform::read(inPath);
    auto *inSpec = new WaveformSpectrogram(in);

    // prepare time axis map, output spectrogram and output waveform.
    auto *tam = new SimpleDoubledTimeAxisMap(inSpec->msLength() * 2.0);
    auto *outSpec = new StretchedPartialSpectrogram(inSpec, tam);
    auto *out = new Waveform(in->length * 2, in->samplingFrequency);

    // set synthesizer parameters
    SynthesizeImpulseResponseWithWORLD irs(outSpec->fftSize(), out->samplingFrequency);
    SynthesizeSegmentWithWORLD synthesize(&irs);

    SegmentSignal s(out->data, /* indexMin = */ 0, /* indexMax = */ out->length, out->samplingFrequency);
    SegmentParameters p(outSpec, /* startPhase = */ 0.0, /* startFractionalTimeShift = */ 0.0);

    // synthesize spectrogram in `outSpec` into output waveform in `out`.
    synthesize(&s, &p);

    // save waveform.
    out->save(outPath);

    return 0;
}
