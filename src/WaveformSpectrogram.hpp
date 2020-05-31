// Copyright 2020 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef UZUME_DSP_WAVEFORM_SPECTROGRAM_HPP
#define UZUME_DSP_WAVEFORM_SPECTROGRAM_HPP

#include <functional>

#include "AnalyzeAperiodicity.hpp"
#include "AnalyzePeriodicity.hpp"
#include "Contour.hpp"
#include "EstimateF0.hpp"
#include "InstantWaveform.hpp"
#include "Spectrogram.hpp"
#include "Waveform.hpp"

namespace uzume {
    namespace dsp {

        /**
         * WaveformSpectrogram is an implementation of Spectrogram.
         * This class treat waveform as spectrogram with WORLD analysis algorithm.
         */
        class WaveformSpectrogram final : public Spectrogram {
        public:
            static const std::function<AnalyzeAperiodicity *(unsigned int)> DefaultAperiodicAnalysisFactory;
            static const std::function<AnalyzePeriodicity *(unsigned int)> DefaultPeriodicAnalysisFactory;
            static const std::function<EstimateF0 *(double)> DefaultF0EstimationFactory;

            explicit WaveformSpectrogram(Waveform *waveform,
                                         const std::function<AnalyzeAperiodicity *(
                                                 unsigned int)> &aperiodicAnalysisFactory = DefaultAperiodicAnalysisFactory,
                                         const std::function<AnalyzePeriodicity *(
                                                 unsigned int)> &periodicAnalysisFactory = DefaultPeriodicAnalysisFactory,
                                         const std::function<EstimateF0 *(
                                                 double)> &f0EstimationFactory = DefaultF0EstimationFactory);

            ~WaveformSpectrogram() final;

            bool pickUpSpectrumAt(Spectrum *destination, double ms) const override;

            double f0At(double ms) const override;

            double msLength() const override;

            unsigned int fftSize() const override;

        private:
            AnalyzeAperiodicity *analyzeAperiodicity;
            AnalyzePeriodicity *analyzePeriodicity;
            Waveform *waveform;
            Contour *f0;

            InstantWaveform *iw;
        };

    }
}

#endif //UZUME_DSP_WAVEFORM_SPECTROGRAM_HPP
