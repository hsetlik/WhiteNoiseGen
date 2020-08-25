#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    
    slider.setRange(-100, -12.0);
    
    
    slider.onValueChange = [this] {level = juce::Decibels::decibelsToGain((float) slider.getValue());};
    slider.setValue(juce::Decibels::gainToDecibels(level));
    decibelLabel.setText("Noise in dB", juce::dontSendNotification);
    addAndMakeVisible(slider);
    addAndMakeVisible(decibelLabel);
    
    setSize (400, 200);
    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto currentLevel = level;
    auto levelScale = currentLevel * 2.0f;
    for(auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
        for(auto sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            auto rawNoise = random.nextFloat() * 1.0f - 0.5f;
            buffer[sample] = rawNoise * (levelScale - currentLevel);
        }
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    decibelLabel.setBounds(10, 10, 120, 20);
    slider.setBounds (130, 10, getWidth() - 140, 20);
}


double decibelSlider::getValueFromText(const juce::String &text)
{
    auto minusInfinitydB = -100.0;
    auto decibelText = text.upToFirstOccurrenceOf("dB", false, true).trim();
    return decibelText.equalsIgnoreCase("-INF") ? minusInfinitydB : decibelText.getDoubleValue();
}

juce::String decibelSlider::getTextFromValue(double value)
{
    return juce::Decibels::toString(value);
}
