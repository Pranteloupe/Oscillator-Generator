//
// Created by Praneeth Bandi on 8/26/25.
//

#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include <string>

class Oscillator {
    public:
    Oscillator(float freq, float amp, int sampleRate);
    float process();
    void setFrequency(float freq);
    void setAmp(float amp);
    void setType(int t);
    std::string waveType() const;
    [[nodiscard]] float getFrequency() const;
    [[nodiscard]] int getSampleRate() const;

    private:
    float frequency;
    float amplitude;
    float angle;
    float offset;
    int sampleRate;
    int type;
};

#endif //OSCILLATOR_H
