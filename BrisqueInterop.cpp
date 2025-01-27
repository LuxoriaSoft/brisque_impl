#include "BrisqueInterop.h"
#include "BrisqueAlgorithm.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <stdexcept>

using namespace luxoria::filter::algorithms;

extern "C" {
    void* CreateBrisqueAlgorithm(const char* modelPath, const char* rangePath) {
        try {
            return new BrisqueAlgorithm(modelPath, rangePath);
        } catch (const std::exception&) {
            return nullptr; // Return nullptr on failure
        }
    }

    double ComputeBrisqueScore(void* brisqueInstance, const char* imagePath) {
        try {
            if (!brisqueInstance) throw std::runtime_error("Invalid BRISQUE instance");

            BrisqueAlgorithm* brisque = static_cast<BrisqueAlgorithm*>(brisqueInstance);

            // Load the input image
            cv::Mat img = cv::imread(imagePath, cv::IMREAD_COLOR);
            if (img.empty()) throw std::runtime_error("Failed to load image: " + std::string(imagePath));

            // Convert to grayscale
            cv::Mat grayImg;
            cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);

            // Compute the score
            return brisque->compute(grayImg);
        } catch (const std::exception&) {
            return -1.0; // Return -1.0 in case of an error
        }
    }

    void ReleaseBrisqueAlgorithm(void* brisqueInstance) {
        if (brisqueInstance) {
            BrisqueAlgorithm* brisque = static_cast<BrisqueAlgorithm*>(brisqueInstance);
            delete brisque;
        }
    }
}
