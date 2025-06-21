#include "inc/Animation.hpp"

Animation::Animation(int fps, const std::string& name) {
    this->_fps = fps;
    this->_name = name;

    this->_currentFrame = 0; // Start at the first frame
    this->_shown = false; // Initially not shown
}

Animation::~Animation() {

}

void Animation::loadTracks(const std::vector<AnimationReader::AnimationTrack>& tracks) {
    if(!this->_tracks.empty()) {
        error("Tracks have already been loaded for this animation.");
        // throw std::runtime_error("Tracks have already been loaded for this animation.");
    }
    if(tracks.empty()) {
        error("No tracks provided to loa/d.");
        // throw std::runtime_error("No tracks provided to load.");
    }

    this->_frameCount = tracks[0].frameCount;

    for(uint i = 0; i < tracks.size(); i++) {
        debug("Loading track #%d: '%s'", i, tracks[i].name.c_str(), tracks[i].frameCount);
        this->_tracks.push_back(tracks[i]);
        if(this->_frameCount != tracks[i].frameCount) {
            error("All tracks must have the same number of frames.");
            // throw std::runtime_error("All tracks must have the same number of frames.");
        }
    }

    this->_duration = (float)this->_frameCount / this->_fps; // Update duration based on frame count
}

std::vector<std::string> Animation::getRequiredResources() const {
    if(this->_tracks.empty()) {
        error("No tracks loaded, cannot get required resources.");
        // throw std::runtime_error("No tracks loaded.");
    }

    std::vector<std::string> resources;
    for(const auto& track : this->_tracks) {
        for(const auto& frame : track.frames) {
            if(!frame.image.empty()) {
                resources.push_back(frame.image);
            }
        }
    }

    return resources;
}
