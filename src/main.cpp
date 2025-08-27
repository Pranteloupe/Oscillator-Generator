#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include "portaudio.h"

#include "../include/Oscillator.h"
using namespace std;

#define SAMPLE_RATE 44100
#define NUM_SECONDS 2
#define FRAMES_PER_BUFFER 1024
#define NUM_CHANNELS 2

int stopProgram(const PaError err) {
    cerr << "Port Audio Error: " << Pa_GetErrorText(err) << endl;
    PaError endError = Pa_Terminate();
    if (endError != paNoError) {
        cerr << "Termination Error: " << Pa_GetErrorText(endError) << endl;
    }

    return 1;
}

int main() {
    PaStream *stream;
    PaStreamParameters outputParameters;
    float buffer[FRAMES_PER_BUFFER][NUM_CHANNELS];
    int command = 0;
    double left_freq = 440;
    double right_freq = 440;
    double left_amp = 0.5;
    double right_amp = 0.5;

    PaError err = Pa_Initialize();
    if (err != paNoError) {
        stopProgram(err);
    }

    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = NUM_CHANNELS;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(&stream, nullptr, &outputParameters, SAMPLE_RATE,
        FRAMES_PER_BUFFER, paClipOff, nullptr, nullptr);
    if (err != paNoError) {
        stopProgram(err);
    }

    Oscillator left_oscillator(left_freq, left_amp, SAMPLE_RATE);
    Oscillator right_oscillator(right_freq, right_amp, SAMPLE_RATE);

    while (true) {
        cout << "Commands:\n"
             << "0 - Run oscillators\n"
             << "1 - Set left oscillator frequency and amplitude\n"
             << "2 - Set right oscillator frequency and amplitude\n"
             << "3 - End program\n"
             << endl;
        cout << "Enter command: ";
        cin >> command;

        if (command == 3) {
            break;
        } else if (command == 1) {
            cout << "Enter frequency: ";
            cin >> left_freq;
            cout << "Enter amplitude: ";
            cin >> right_amp;
            left_oscillator.setFrequency(left_freq);
            left_oscillator.setAmp(left_amp);
        } else if (command == 2) {
            cout << "Enter frequency: ";
            cin >> right_freq;
            cout << "Enter amplitude: ";
            cin >> right_amp;
            right_oscillator.setFrequency(right_freq);
            right_oscillator.setAmp(right_amp);
        } else if (command == 0) {
            err = Pa_StartStream(stream);
            if (err != paNoError) { stopProgram(err); }

            constexpr int bufferCount = (NUM_SECONDS * SAMPLE_RATE) / FRAMES_PER_BUFFER;
            for (int i = 0; i < bufferCount; i++) {
                for (auto & j : buffer) {
                    j[0] = left_oscillator.process();
                    j[1] = right_oscillator.process();
                }

                err = Pa_WriteStream(stream, buffer, FRAMES_PER_BUFFER);
                if (err != paNoError) { stopProgram(err); }
            }

            err = Pa_StopStream(stream);
            if (err != paNoError) { stopProgram(err); }
        }
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        stopProgram(err);
    }

    err = Pa_Terminate();
    if (err != paNoError) {
        stopProgram(err);
    }

    return 0;
}