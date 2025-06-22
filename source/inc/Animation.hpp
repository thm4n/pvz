#pragma once

#include <tinyxml2.h>

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "Animation.hpp"
#include "Logger.hpp"

namespace xml = tinyxml2;
namespace fs = std::filesystem;

class Animation;

namespace AnimationReader {
typedef struct {
    int frameIndex;  // Index of the frame in the animation
    double x, y;     // Position of the frame
    double sx, sy;   // Scale factors
    double kx, ky;   // Rotation angle in radians
    double opacity;  // Opacity of the frame
    bool shown;      // Whether the frame is currently shown
    std::string image;
} AnimationFrame;

typedef struct {
    std::string name;
    std::vector<AnimationFrame> frames;  // List of frames in the track
    int frameCount;                      // Total number of frames in the track
} AnimationTrack;

Animation* readAnimation(const std::string& filePath);
void parseTrack(xml::XMLElement* trackElement, AnimationTrack& track);
bool parseTrackFrame(xml::XMLElement* frameElement, AnimationFrame& frame);
void printFrame(const AnimationFrame& frame);
}  // namespace AnimationReader

class Animation {
public:
    Animation(int fps, const std::string& name);

    ~Animation();

    void loadTracks(const std::vector<AnimationReader::AnimationTrack>& tracks);
    std::vector<std::string> getRequiredResources() const;

private:
    int _fps;
    std::vector<AnimationReader::AnimationTrack>
        _tracks;        // List of animation tracks
    int _frameCount;    // Number of frames in the animation
    float _duration;    // Duration of the animation in seconds
    std::string _name;  // Name of the animation

    int _currentFrame;  // Current frame index
    bool _shown;
};