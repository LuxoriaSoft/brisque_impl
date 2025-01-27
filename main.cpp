#include <iostream>
#include <string>
#include "BrisqueInterop.h"

#define DEFAULT_MODEL_PATH "./models/brisque_model_live.yml"
#define DEFAULT_RANGE_PATH "./models/brisque_range_live.yml"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <image_path> [model_path] [range_path]" << std::endl;
        return 1;
    }

    const char* imagePath = argv[1];
    const char* modelPath = (argc > 2) ? argv[2] : DEFAULT_MODEL_PATH;
    const char* rangePath = (argc > 3) ? argv[3] : DEFAULT_RANGE_PATH;

    // Create the BRISQUE algorithm instance
    void* brisqueInstance = CreateBrisqueAlgorithm(modelPath, rangePath);
    if (!brisqueInstance) {
        std::cerr << "Failed to initialize BRISQUE algorithm with model: " << modelPath
                  << " and range: " << rangePath << std::endl;
        return -1;
    }

    // Compute the BRISQUE score
    double score = ComputeBrisqueScore(brisqueInstance, imagePath);
    if (score < 0) {
        std::cerr << "Failed to compute BRISQUE score for image: " << imagePath << std::endl;
    } else {
        std::cout << "BRISQUE Score: " << score << std::endl;
    }

    // Clean up resources
    ReleaseBrisqueAlgorithm(brisqueInstance);
    return 0;
}
