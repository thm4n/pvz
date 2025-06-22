#include "inc/Animation.hpp"

int main(int argc, char* argv[]) {
	if(argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <animation_file_path>" << std::endl;
		return 1;
	}
	
    // Example usage of the AnimationReader
    std::string animationFilePath(argv[1]); // Replace with actual file path
    Animation* animation = AnimationReader::readAnimation(animationFilePath);
    
    if(animation) {
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
