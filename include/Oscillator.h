//
// Created by Praneeth Bandi on 8/26/25.
//

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

class Oscillator {
    public:
    Oscillator(float freq, float amp, int sampleRate);
    float process();
    void setFrequency(float freq);
    [[nodiscard]] float getFrequency() const;
    [[nodiscard]] int getSampleRate() const;

    private:
    float frequency;
    float amplitude;
    float angle;
    float offset;
    int sampleRate;
};

#endif //OSCILLATOR_H
