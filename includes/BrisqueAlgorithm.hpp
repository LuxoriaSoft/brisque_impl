#pragma once

#include <opencv2/quality.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>
#include <stdexcept>

namespace luxoria {
    namespace filter {
        namespace algorithms {
            // Encapsulates the BRISQUE algorithm
            class BrisqueAlgorithm {
            private:
                cv::Ptr<cv::quality::QualityBRISQUE> _model;

            public:
                // Constructor to initialize BRISQUE with model and range files
                BrisqueAlgorithm(const std::string& modelPath, const std::string& rangePath) {
                    if (modelPath.empty() || rangePath.empty()) {
                        throw std::invalid_argument("Model and range file paths must not be empty.");
                    }
                    _model = cv::quality::QualityBRISQUE::create(modelPath, rangePath);
                }

                // Compute the BRISQUE score for an input image
                double compute(const cv::Mat& image) const {
                    if (image.empty()) {
                        throw std::runtime_error("Input image is empty.");
                    }
                    cv::Scalar score = _model->compute(image);
                    return score[0];
                }
            };
        }
    }
}
