#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NeedleVUAudioProcessor::NeedleVUAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

NeedleVUAudioProcessor::~NeedleVUAudioProcessor()
{
}

//==============================================================================
const juce::String NeedleVUAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NeedleVUAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NeedleVUAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NeedleVUAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NeedleVUAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NeedleVUAudioProcessor::getNumPrograms()
{
    return 1;
}

int NeedleVUAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NeedleVUAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NeedleVUAudioProcessor::getProgramName (int index)
{
    return {};
}

void NeedleVUAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NeedleVUAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void NeedleVUAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NeedleVUAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NeedleVUAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    DBG ("Buffer channels: " + juce::String (buffer.getNumChannels()));
    DBG ("Input channels: " + juce::String (totalNumInputChannels));
    DBG ("Samples: " + juce::String (buffer.getNumSamples()));

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        DBG ("First sample: " + juce::String (buffer.getSample (channel, 0), 6));
        const auto rmsLevel = buffer.getRMSLevel(channel, 0, buffer.getNumSamples());
        DBG ("Channel " + juce::String (channel)
             + " RMS: " + juce::String (rmsLevel, 6));
        DBG ("Input channels: " + juce::String (totalNumInputChannels));
        DBG ("RMS: " + juce::String (rmsLevel));
        
        if (channel == 0)
            leftRMS.store (rmsLevel);

        else if (channel == 1)
            rightRMS.store (rmsLevel);
        float peakLevel = buffer.getMagnitude (
            channel, 0, buffer.getNumSamples()
        );

        DBG ("Channel " + juce::String (channel)
             + " Peak: " + juce::String (peakLevel, 6));
        
        // ..do something to the data...
    }
}

//==============================================================================
bool NeedleVUAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NeedleVUAudioProcessor::createEditor()
{
    return new NeedleVUAudioProcessorEditor (*this);
}

//==============================================================================
void NeedleVUAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

}

void NeedleVUAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NeedleVUAudioProcessor();
}

float NeedleVUAudioProcessor::getLeftRMS() const
{
    return leftRMS.load();
}

float NeedleVUAudioProcessor::getRightRMS() const
{
    return rightRMS.load();
}
