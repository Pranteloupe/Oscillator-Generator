//
// Created by Praneeth Bandi on 8/26/25.
//

#include "../include/Oscillator.h"
#include <algorithm>
#include <cmath>

Oscillator::Oscillator(float freq, float amp, int sampleRate) : frequency(freq), amplitude(amp), sampleRate(sampleRate) {
    offset = 2 * M_PI * freq / sampleRate;
    angle = 0.0f;
    type = 0;
}

float Oscillator::process() {
    if (type == 0) { //Sinusoid
        auto sample = amplitude * sin(angle);
        angle += offset;
        return sample;
    } else if (type == 1) { //Triangle Wave
        auto sample = amplitude * (1.0f - 4.0f * abs(angle - 0.5f));
        angle += offset;
        if (angle >= 1.0f) {
            angle -= 1.0f;
        }
        return sample;
    } else if (type == 2) { //Square Wave
        auto sample = amplitude * (angle < 0.5f ? -1.0f : 1.0f);
        angle += offset;
        if (angle >= 1.0f) {
            angle -= 1.0f;
        }
        return sample;
    } else { //Sawtooth Wave
        float frac = fmod(angle, 1.0f);
        auto sample = amplitude * (frac - floor(frac));
        angle += offset;
        if (angle >= 1.0f) {
            angle -= 1.0f;
        }
        return sample;
    }
}

void Oscillator::setFrequency(float freq) {
    frequency = freq;
    if (type == 0) {
        offset = 2 * M_PI * frequency / sampleRate;
        angle = 0.0f;
    } else {
        offset = frequency / sampleRate;
        angle = 0.0f;
    }
}

void Oscillator::setAmp(float amp) {
    amplitude = amp;
}

void Oscillator::setType(int t) {
    type = t;
}



int Oscillator::getSampleRate() const { return sampleRate; }

std::string Oscillator::waveType() const {
    if (type == 0) {
        return "Sinusoid";
    } else if (type == 1) {
        return "Triangle";
    } else if (type == 2) {
        return "Square";
    } else {
        return "Sawtooth";
    }
}


float Oscillator::getFrequency() const { return frequency; }


