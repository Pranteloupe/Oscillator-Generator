//
// Created by Praneeth Bandi on 8/26/25.
//

#include "../include/Oscillator.h"
#include <algorithm>
#include <cmath>

Oscillator::Oscillator(float freq, float amp, int sampleRate) : frequency(freq), amplitude(amp), sampleRate(sampleRate) {
    offset = 2 * M_PI * freq / sampleRate;
    angle = 0.0f;
}

float Oscillator::process() {
    auto sample = amplitude * sin(angle);
    angle += offset;
    return sample;
}

void Oscillator::setFrequency(float freq) {
    frequency = freq;
    offset = 2 * M_PI * freq / sampleRate;
    angle = 0.0f;
}

void Oscillator::setAmp(float amp) {
    amplitude = amp;
}


int Oscillator::getSampleRate() const { return sampleRate; }

float Oscillator::getFrequency() const { return frequency; }


