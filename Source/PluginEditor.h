#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "PluginProcessor.h"

class PluginEditor : public juce::AudioProcessorEditor,
                     public juce::Button::Listener,
                     public juce::Slider::Listener
{
public:
    explicit PluginEditor(PluginProcessor&);
    ~PluginEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    PluginProcessor& processorRef;

    juce::TextButton decrementButton;
    juce::TextButton incrementButton;
    juce::Slider currentProgramSlider;
    juce::Label currentProgramLabel;

    void updateButtonStates();
    void updateSliderValue();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};