#include "inc/AnimationReader.hpp"

int main() {
    // Example usage of the AnimationReader
    std::string animationFilePath = "path/to/animation.xml"; // Replace with actual file path
    Animation* animation = AnimationReader::readAnimation(animationFilePath);
    
    if (animation) {
        std::cout << "Animation loaded successfully!" << std::endl;
        delete animation; // Clean up after use
    } else {
        std::cout << "Failed to load animation." << std::endl;
    }

    // Example usage of AnimationTrack and AnimationFrame can be added here
    

    return 0;
}
