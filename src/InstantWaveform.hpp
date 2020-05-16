// Copyright 2020 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef UZUME_DSP_INSTANT_WAVEFORM_HPP
#define UZUME_DSP_INSTANT_WAVEFORM_HPP

namespace uzume { namespace dsp {

class InstantWaveform final {
public:
    InstantWaveform(unsigned int samplingFrequency);
    ~InstantWaveform();

    double *data;
    double f0;
    unsigned int length;
    unsigned int samplingFrequency;
};

} }
#endif //UZUME_DSP_INSTANT_WAVEFORM_HPP
