#pragma once

#include <JuceHeader.h>

class decibelSlider: public juce::Slider
{
public:
    decibelSlider() {};
    double getValueFromText(const juce::String& text) override;
    juce::String getTextFromValue(double value) override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (decibelSlider)
};
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    juce::Random random;
    decibelSlider slider;
    juce::Slider ampSlider;
    juce::Label decibelLabel;
    float level = 0.0f;
    //==============================================================================
    // Your private member variables go here...
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


