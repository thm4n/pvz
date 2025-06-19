#pragma once

#include <iostream>
#include <string>
#include <vector>

class Animation {
public:
    Animation(int fps, int frameCount, const std::string& name) {
        this->_fps = fps;
        this->_frameCount = frameCount;
        this->_duration = (float)frameCount / fps; // Calculate duration in seconds
        this->_name = name;

        this->_currentFrame = 0; // Start at the first frame
        this->_shown = false; // Initially not shown
    }
    
    ~Animation() {

    }

private:
    int _fps;
    int _frameCount; // Number of frames in the animation
    float _duration; // Duration of the animation in seconds
    std::string _name; // Name of the animation

    int _currentFrame; // Current frame index
    bool _shown;
};