#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include <tinyxml2.h>

#include "Animation.hpp"



namespace AnimationReader {
    typedef struct {
        std::string file; // File path of the frame image
        int frameIndex; // Index of the frame in the animation
        double x, y; // Position of the frame
        double sx, sy; // Scale factors
        double rotation; // Rotation angle in radians
        double opacity; // Opacity of the frame
        bool shown; // Whether the frame is currently shown
    } AnimationFrame;

    class AnimationTrack {
    public:

    private:

    };

    Animation* readAnimation(const std::string& filePath) { // entry point
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open animation file: " << filePath << std::endl;
            return nullptr;
        }

        std::stringstream animationStream;
        animationStream << file.rdbuf();
        file.close();

        // Parse the animation metadata
        int fps, frameCount;
        std::string name;

    }

    AnimationTrack parseTrack(std::stringstream& animationStream) {
        AnimationTrack track;

        
    }

    AnimationFrame parseTrackFrame(std::stringstream& animationStream) {

    }
}
