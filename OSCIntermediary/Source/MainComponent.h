#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component,
                       private juce::OSCReceiver,
                       private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    int currentPortNumber = -1;

    struct handParams
    {
        int newGesture     = 0,
            timesSeenGest  = 0,
            currentGesture = 0,
            newNumeric     = 0,
            timesSeenNum   = 0,
            currentNumeric = 0,
            x              = 0,
            y              = 0;
    } leftHand, rightHand;

    juce::TextEditor logScreen;

    juce::Slider testSlider;

    juce::OSCSender senderEC2; // The sender for EmissionControl2

    void oscMessageReceived         (const juce::OSCMessage&) override;
    void showConnectionErrorMessage (const juce::String&);
    void showArgumentErrorMessage   (const juce::String&);
    void logMessage                 (const juce::String&);

    //==============================================================================
    void handleConnectError (int);
    void handleDisconnectError();
    void handleInvalidPortNumberEntered();

    //==============================================================================
    void updateHands (handParams&, int, int, int, int, int);
    bool resend (juce::String&);

    juce::String OSCArgToString (const juce::OSCArgument&);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
