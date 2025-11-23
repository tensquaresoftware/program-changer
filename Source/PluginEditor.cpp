#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p), 
      processorRef(p),
      decrementButton("<"),
      incrementButton(">"),
      currentProgramSlider(juce::Slider::LinearHorizontal, juce::Slider::TextBoxLeft),
      currentProgramLabel("", "Current")
{
    addAndMakeVisible(decrementButton);
    addAndMakeVisible(incrementButton);
    addAndMakeVisible(currentProgramSlider);
    addAndMakeVisible(currentProgramLabel);

    decrementButton.addListener(this);
    incrementButton.addListener(this);
    currentProgramSlider.addListener(this);

    currentProgramSlider.setRange(0.0, 127.0, 1.0);
    currentProgramSlider.setValue(processorRef.getCurrentProgramNumber());

    currentProgramLabel.attachToComponent(&currentProgramSlider, false);
    currentProgramLabel.setJustificationType(juce::Justification::centredLeft);

    updateButtonStates();

    setSize(250, 150);
}

PluginEditor::~PluginEditor()
{
}

void PluginEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PluginEditor::resized()
{
    const int buttonWidth = 100;
    const int buttonHeight = 40;
    const int margin = 10;
    const int sliderHeight = 40;
    const int labelHeight = 20;
    
    const int totalWidth = buttonWidth * 2 + margin;
    const int startX = (getWidth() - totalWidth) / 2;
    const int buttonY = margin + 20;
    
    decrementButton.setBounds(startX, buttonY, buttonWidth, buttonHeight);
    incrementButton.setBounds(startX + buttonWidth + margin, buttonY, buttonWidth, buttonHeight);
    
    const int sliderY = buttonY + buttonHeight + margin + labelHeight;
    currentProgramSlider.setBounds(margin, sliderY, 
                                   getWidth() - 2 * margin, sliderHeight);
    
    currentProgramLabel.setBounds(margin, buttonY + buttonHeight + margin,
                                  getWidth() - 2 * margin, labelHeight);
}

void PluginEditor::buttonClicked(juce::Button* button)
{
    if (button == &decrementButton)
    {
        processorRef.decrementProgram();
        updateSliderValue();
        updateButtonStates();
    }
    else if (button == &incrementButton)
    {
        processorRef.incrementProgram();
        updateSliderValue();
        updateButtonStates();
    }
}

void PluginEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &currentProgramSlider)
    {
        int newValue = static_cast<int>(currentProgramSlider.getValue());
        processorRef.setCurrentProgramNumber(newValue);
        updateButtonStates();
    }
}

void PluginEditor::updateButtonStates()
{
    int currentProgram = processorRef.getCurrentProgramNumber();
    
    decrementButton.setEnabled(currentProgram > 0);
    incrementButton.setEnabled(currentProgram < 127);
}

void PluginEditor::updateSliderValue()
{
    currentProgramSlider.setValue(processorRef.getCurrentProgramNumber(), 
                                  juce::dontSendNotification);
}