#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NeedleVUAudioProcessorEditor  : public juce::AudioProcessorEditor,
private juce::Timer
{
public:
    NeedleVUAudioProcessorEditor (NeedleVUAudioProcessor&);
    ~NeedleVUAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;
    float leftMeterLevel = 0.0f;
    float rightMeterLevel = 0.0f;
    float leftSmoothedLevel = -60.0f;
    float rightSmoothedLevel = -60.0f;

    NeedleVUAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NeedleVUAudioProcessorEditor)
};
