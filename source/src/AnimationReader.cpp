#include "inc/Animation.hpp"

namespace AnimationReader {
Animation* readAnimation(const std::string& filePath) {  // entry point
    xml::XMLDocument doc;

    int fps;
    AnimationTrack track;
    Animation* animation = nullptr;
    xml::XMLElement* element = nullptr;
    std::vector<AnimationTrack> tracks;
    std::string animationName;

    fs::path animationPath(filePath);

    if (!fs::exists(animationPath)) {
        error("Animation file does not exist: %s", filePath.c_str());
        return nullptr;
    }
    animationName = animationPath.stem().string();
    debug("Loading animation: %s", animationName.c_str());

    doc.LoadFile(filePath.c_str());
    if (doc.ErrorID() != xml::XML_SUCCESS) {
        error("Failed to load animation file: %s, Error: %s", filePath.c_str(),
              doc.ErrorName());
        return nullptr;
    }

    debug("Animation file loaded successfully: %s", filePath.c_str());

    element = doc.FirstChildElement("fps");
    if (!element) {
        error("No <fps> element found in animation file: %s", filePath.c_str());
        return nullptr;
    }
    fps = std::stoi(element->GetText());
    debug("FPS: %d", fps);

    while((element = element->NextSiblingElement("track"))) {
        debug("Found track element: %s", element->Name());
        track = {std::string(""), std::vector<AnimationFrame>({}), 0};
        parseTrack(element, track);
        if (track.frameCount == 0) {
            error("Track %s has no frames, skipping", track.name.c_str());
            // throw std::runtime_error("Track has no frames");
        }
        tracks.push_back(track);
        debug("added to animation '%s' track '%s'", animationName.c_str(),
              track.name.c_str(), track.frameCount);
    }

    animation = new Animation(fps, animationName);
    animation->loadTracks(tracks);

    doc.Clear();
    return animation;
}

void parseTrack(xml::XMLElement* trackElement, AnimationTrack& track) {
    AnimationFrame currentFrame = {0,   0.0, 0.0, 1.0,  1.0,
                                   0.0, 0.0, 1.0, true, std::string("")};
    xml::XMLElement* element = nullptr;

    debug("Entering parseTrack function");
    element = trackElement->FirstChildElement("name");
    track.name = element->GetText();
    debug("Parsing track: %s", track.name.c_str());

    debug("starting to parse frames");
    element = trackElement->FirstChildElement("t");
    if (!element) {
        error("No <t> elements found in track: %s", track.name.c_str());
        // throw std::runtime_error("No frames found in track");
    }

    while (element) {
        parseTrackFrame(element, currentFrame);
        printFrame(currentFrame);

        currentFrame.frameIndex = track.frameCount;
        debug("Parsed frame index: %d", currentFrame.frameIndex);
        track.frames.push_back(currentFrame);
        track.frameCount++;
        debug("going to next frame element: %d", track.frameCount);
        element = element->NextSiblingElement("t");
    }
    debug("Finished parsing frames, total frames: %d", track.frameCount);
}

void parseTrackFrame(xml::XMLElement* frameElement, AnimationFrame& frame) {
    xml::XMLElement* currElement = nullptr;

    currElement = frameElement->FirstChildElement();
    while (currElement) {
        debug("Parsing frame element: %s", currElement->Name());

        if (currElement->Name() == std::string("f")) {
            debug("Found <f> element: %s", currElement->Name());
            if (currElement->IntText() == -1) {
                debug("<f> element indicates frame is hidden");
                frame.shown = false;
            } else {
                debug("<f> element indicates frame is shown");
                frame.shown = true;
            }
        } else if (currElement->Name() == std::string("x")) {
            frame.x = currElement->DoubleText();
            debug("Parsed x: %f", frame.x);
        } else if (currElement->Name() == std::string("y")) {
            frame.y = currElement->DoubleText();
            debug("Parsed y: %f", frame.y);
        } else if (currElement->Name() == std::string("sx")) {
            frame.sx = currElement->DoubleText();
            debug("Parsed sx: %f", frame.sx);
        } else if (currElement->Name() == std::string("sy")) {
            frame.sy = currElement->DoubleText();
            debug("Parsed sy: %f", frame.sy);
        } else if (currElement->Name() == std::string("kx")) {
            frame.kx = currElement->DoubleText();
            debug("Parsed kx: %f", frame.kx);
        } else if (currElement->Name() == std::string("ky")) {
            frame.ky = currElement->DoubleText();
            debug("Parsed ky: %f", frame.ky);
        } else if (currElement->Name() == std::string("a")) {
            frame.opacity = currElement->DoubleText();
            debug("Parsed opacity: %f", frame.opacity);
        } else if (currElement->Name() == std::string("i")) {
            frame.image = std::string(currElement->GetText());
            debug("Parsed image: %s", frame.image.c_str());
        } else {
            error("Unknown element in frame: %s", currElement->Name());
        }

        currElement = currElement->NextSiblingElement();
    }
}

void printFrame(const AnimationFrame& frame) {
    debug("Frame Index: %d", frame.frameIndex);
    debug("Position: (%f, %f)", frame.x, frame.y);
    debug("Scale: (%f, %f)", frame.sx, frame.sy);
    debug("Rotation: (%f, %f)", frame.kx, frame.ky);
    debug("Opacity: %f", frame.opacity);
    debug("Shown: %s", frame.shown ? "true" : "false");
    debug("Image: %s", frame.image.c_str());
}
}  // namespace AnimationReader