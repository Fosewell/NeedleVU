#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (640, 240);
    startTimerHz(30);
    
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)

{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour (0xff202020));
    g.setColour (juce::Colour (0xffffe8bd));
    g.fillRoundedRectangle(30.0f, 40.0f, 270.0f, 180.0f, 8.0f);
    g.fillRoundedRectangle(320.0f, 40.0f, 270.0f, 180.0f, 8.0f);
    
    auto drawVUMeterScale = [&g] (float centerX)
    {
        const float centerY = 130.0f;
        const float radiusX = 125.0f;
        const float radiusY = 60.0f;


        const float labelStartAngle = juce::MathConstants<float>::pi * 1.15f;
        const float labelEndAngle   = juce::MathConstants<float>::pi * 1.85f;

        juce::Path scaleArc;

        for (int i = 0; i <= 100; ++i)
        {
            float proportion = i / 100.0f;

            float angle = labelStartAngle + proportion * (labelEndAngle - labelStartAngle);
            
            float x = centerX + radiusX * std::cos (angle);
            float y = centerY + radiusY * std::sin (angle);

            if (i == 0)
                scaleArc.startNewSubPath (x, y);
            else
                scaleArc.lineTo (x, y);
        }
        
        g.setColour (juce::Colours::black);
        g.strokePath (scaleArc, juce::PathStrokeType (2.5f));
        
        juce::Path redZeroArc;
        
        for (int i = 0; i <=25; ++i)
        {
            float proposition = i / 25.0f;
            
            float angle = labelStartAngle + (0.625f + proposition * 0.375f) * (labelEndAngle - labelStartAngle);
            float x = centerX + radiusX * std::cos(angle);
            float y = centerY + radiusY * std::sin(angle) - 6.0f;
            
                if (i == 0)
                    redZeroArc.startNewSubPath(x, y);
                else
                    redZeroArc.lineTo(x,y);
        }
        
        g.setColour(juce::Colours::red);
        g.strokePath(redZeroArc, juce::PathStrokeType(4.0f,juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        
        for (int i = 0; i <= 8; ++i)
        {
            float proportion = i / 8.0f;
                float angle = labelStartAngle
                            + proportion * (labelEndAngle - labelStartAngle);

                float x = centerX + radiusX * std::cos(angle);
                float y = centerY + radiusY * std::sin(angle);

                float dx = -std::cos(angle) / radiusX;
                float dy = -std::sin(angle) / radiusY;

                float length = std::sqrt(dx * dx + dy * dy);
                dx /= length;
                dy /= length;

                g.setColour(i >= 7 ? juce::Colours::red
                                   : juce::Colours::black);

                g.drawLine(x, y, x + dx * 10.0f, y + dy * 10.0f, 2.0f);
        }
        
        const char* scaleLabels[] =
        {
            "-20", "-10", "-7", "-5", "-3", "0", "+1", "+2", "+3"
        };

        g.setFont (14.0f);

        for (int i = 0; i < 9; ++i)
        {
            float proportion = i / 8.0f;
            float angle = labelStartAngle + proportion * (labelEndAngle - labelStartAngle);

            float x = centerX + radiusX * std::cos (angle);
            float y = centerY + radiusY * std::sin (angle);

            if (i >= 7)
                g.setColour (juce::Colours::red);
            else
                g.setColour (juce::Colours::black);
            

            g.drawText (scaleLabels[i],
                        x - 19.0f, y + 8.0f,
                        34.0f, 18.0f,
                        juce::Justification::centred);
            
            // Channel labels
            g.setColour (juce::Colour (0xff333333));
            g.setFont (16.0f);

            g.drawText ("LEFT", 115, 190, 100, 20,
                        juce::Justification::centred);

            g.drawText ("RIGHT", 405, 190, 100, 20,
                        juce::Justification::centred);


            // VU badges
            g.setColour (juce::Colour (0xff333333));

            g.fillRoundedRectangle (250.0f, 184.0f, 38.0f, 24.0f, 3.0f);
            g.fillRoundedRectangle (540.0f, 184.0f, 38.0f, 24.0f, 3.0f);


            // VU lettering
            g.setColour (juce::Colours::white);
            g.setFont (14.0f);

            g.drawText ("VU", 250, 184, 38, 24,
                        juce::Justification::centred);

            g.drawText ("VU", 540, 184, 38, 24,
                        juce::Justification::centred);
        }
    };

    drawVUMeterScale (165.0f);
    drawVUMeterScale (455.0f);

    
    
    g.setColour (juce::Colour (0xff777777));
    g.fillEllipse (160.0f, 140.0f, 10.0f, 10.0f);

    g.setColour (juce::Colour (0xff333333));
    g.drawEllipse (160.0f, 140.0f, 10.0f, 10.0f, 1.0f);

    g.setColour (juce::Colour (0xff777777));
    g.fillEllipse (450.0f, 140.0f, 10.0f, 10.0f);

    g.setColour (juce::Colour (0xff333333));
    g.drawEllipse (450.0f, 140.0f, 10.0f, 10.0f, 1.0f);
    
    
    float leftNeedleAngle = juce::jmap(juce::jlimit(-20.0f, 3.0f, leftMeterLevel), -20.0f, 3.0f, -63.0f, 68.0f);
    float rightNeedleAngle = juce::jmap(juce::jlimit(-20.0f, 3.0f, rightMeterLevel), -20.0f, 3.0f, -63.0f, 68.0f);
    
    float leftAngleRadians = juce::degreesToRadians(leftNeedleAngle);
    float rightAngleRadians = juce::degreesToRadians(rightNeedleAngle);
    
    juce::Path leftNeedle;
    g.setColour(juce::Colour(0xffd94b32));
    g.setColour(juce::Colour(0xff202020));
    leftNeedle.startNewSubPath (165.0f, 145.0f);
    leftNeedle.lineTo (165.0f, 65.0f);
    
    leftNeedle.applyTransform(juce::AffineTransform::rotation (leftAngleRadians, 165.0f, 145.0f));
    
    g.strokePath(leftNeedle, juce::PathStrokeType (3.0f));
    
    juce::Path rightNeedle;
    rightNeedle.startNewSubPath(455.0f, 145.0f);
    rightNeedle.lineTo(455.0f, 65.0f);
    
    rightNeedle.applyTransform(juce::AffineTransform::rotation (rightAngleRadians, 455.0f, 145.0f));
    
    g.strokePath (rightNeedle, juce::PathStrokeType(3.0f));

    
    const char* scaleLabels[] =
    {
        "-20", "-10", "-7", "-5", "-3", "0", "+1", "+2", "+3"
    };
    
    g.setFont(18.0f);
    
    g.drawText("Left", 30, 15, 270, 20, juce::Justification::centred);
    
    g.drawText("Right", 320, 15, 270, 20, juce::Justification::centred);
    

}

void NewProjectAudioProcessorEditor::resized()
{

}

void NewProjectAudioProcessorEditor::timerCallback()
{
    float leftTarget = juce::Decibels::gainToDecibels (audioProcessor.getLeftRMS(), -60.0f) + 18.0f;
    float rightTarget = juce::Decibels::gainToDecibels (audioProcessor.getRightRMS(), -60.0f) + 18.0f;

    float leftCoefficient = leftTarget > leftSmoothedLevel ? 0.25f : 0.15f;
    float rightCoefficient = rightTarget > rightSmoothedLevel ? 0.25f : 0.15f;

    leftSmoothedLevel += (leftTarget - leftSmoothedLevel) * leftCoefficient;
    rightSmoothedLevel += (rightTarget - rightSmoothedLevel) * rightCoefficient;

    leftMeterLevel = leftSmoothedLevel;
    rightMeterLevel = rightSmoothedLevel;
    
    repaint();
}
