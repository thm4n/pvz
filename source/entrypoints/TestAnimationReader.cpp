#include "inc/Animation.hpp"

int main() {
    // Example usage of the AnimationReader
    std::string animationFilePath = "resources/fire.reanim"; // Replace with actual file path
    Animation* animation = AnimationReader::readAnimation(animationFilePath);
    
    if (animation) {
        std::cout << "Animation loaded successfully!" << std::endl;
    } else {
        std::cout << "Failed to load animation." << std::endl;
        return 1;
    }

    auto reqs = animation->getRequiredResources();
    std::cout << "Required resource: " << std::endl;
    for(const auto& req : reqs) {
        std::cout << " >> " << req << std::endl;
    }
    // Example usage of AnimationTrack and AnimationFrame can be added here
    
    delete animation;
    return 0;
}
