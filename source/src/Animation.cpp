#include "inc/Animation.hpp"

Animation::Animation(int fps, const std::string& name) {
    this->_fps = fps;
    this->_name = name;

    this->_currentFrame = 0;  // Start at the first frame
    this->_shown = false;     // Initially not shown
}

Animation::~Animation() {}

void Animation::loadTracks(const std::vector<AnimationReader::AnimationTrack>& tracks) {
    if (!this->_tracks.empty()) {
        error("Tracks have already been loaded for this animation.");
        throw std::runtime_error("Tracks have already been loaded for this animation.");
    }
    if (tracks.empty()) {
        error("No tracks provided to loa/d.");
        throw std::runtime_error("No tracks provided to load.");
    }

    this->_frameCount = tracks[0].frameCount;

    for (uint i = 0; i < tracks.size(); i++) {
        debug("Loading track #%d: '%s'", i, tracks[i].name.c_str(),
              tracks[i].frameCount);
        this->_tracks.push_back(tracks[i]);
        if (this->_frameCount != tracks[i].frameCount) {
            error("All tracks must have the same number of frames.");
            throw std::runtime_error("All tracks must have the same number of frames.");
        }
    }

    this->_duration = (float)this->_frameCount / this->_fps;
}

std::vector<std::string> Animation::getRequiredResources() const {
    if (this->_tracks.empty()) {
        error("No tracks loaded, cannot get required resources.");
        throw std::runtime_error("No tracks loaded.");
    }

	std::set<std::string> reqRes;
    for (const auto& track : this->_tracks) {
        for (const auto& frame : track.frames) {
            if (!frame.image.empty()) {
                reqRes.insert(frame.image);
            }
        }
    }

    return std::vector<std::string>(reqRes.begin(), reqRes.end());
}

void Animation::loadRequiredResources() const {
	std::string resourcePath;

	for (const auto& resourceName : this->getRequiredResources()) {
		warning("WIP");
		// debug("Loading required resource: %s", resourceName.c_str());
		// ResourceManager::loadResource(resourceName, resourceName);
	}
}

void Animation::playTrack(std::string trackName) {
	if (this->_tracks.empty()) {
		error("No tracks loaded, cannot play track.");
		throw std::runtime_error("No tracks loaded.");
	}

	auto it = std::find_if(this->_tracks.begin(), this->_tracks.end(),
						   [&trackName](const AnimationReader::AnimationTrack& track) {
							   return track.name == trackName;
						   });

	if (it == this->_tracks.end()) {
		error("Track '%s' not found in animation '%s'.", trackName.c_str(), this->_name.c_str());
		throw std::runtime_error("Track not found.");
	}

	// Logic to play the track goes here
	// For example, iterate through frames and render them
	debug("Playing track: %s", it->name.c_str());
	it->running = true;
}

void Animation::update() {
	for(auto it = this->_tracks.begin(); it != this->_tracks.end(); ++it) {
		if (it->running) {
			it->currentFrame++;

			if (it->currentFrame >= it->frameCount) {
				it->currentFrame = 0; // Loop back to the first frame
			}
		}
	}
}

void Animation::draw(SDL_Renderer* renderer) const {
	AnimationReader::AnimationFrame currentFrame;
	SDL_Rect renderQuad = {0,0,0,0};
	double angle = 0.0;

	Texture* texture = nullptr;

	for(auto it = this->_tracks.begin(); it != this->_tracks.end(); ++it) {
		if (it->running) {
			currentFrame = it->frames[it->currentFrame];
			AnimationReader::printFrame(currentFrame);
			if (currentFrame.shown) {
				texture = ResourceManager::getResource(currentFrame.image);
				if (!texture) {
					error("Texture '%s' not found for animation frame.", currentFrame.image.c_str());
					throw std::runtime_error("Texture not found.");
				}
				
				renderQuad.x = currentFrame.x;
				renderQuad.y = currentFrame.y;
				renderQuad.w = texture->getWidth() * currentFrame.sx;
				renderQuad.h = texture->getHeight() * currentFrame.sy;
				angle = currentFrame.kx;
				debug("renderQuad: x=%d, y=%d, w=%d, h=%d, angle=%.2f",
					  renderQuad.x, renderQuad.y, renderQuad.w, renderQuad.h, angle);

				SDL_RenderCopyEx(renderer, texture->getTexture(), nullptr, &renderQuad, angle, nullptr, SDL_FLIP_NONE);
			}
		}
	}
}

std::string Animation::getName() const { return _name; }
int Animation::getFrameCount() const { return _frameCount; }
float Animation::getDuration() const { return _duration; }
int Animation::getFPS() const { return _fps; }
int Animation::getCurrentFrame() const { return _currentFrame; }
bool Animation::isShown() const { return _shown; }
