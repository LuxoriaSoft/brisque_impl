#pragma once

#include <opencv2/quality.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>

namespace luxoria {
    namespace filter {
        namespace algorithms {
            class BrisqueAlgorithm {
            private:
                cv::Ptr<cv::quality::QualityBRISQUE> _model;

            public:
                // Constructor: Initializes the BRISQUE model
                BrisqueAlgorithm(const std::string& modelPath, const std::string& rangePath);

                // Method to compute the BRISQUE score
                double compute(const cv::Mat& img) const;

                // Destructor
                ~BrisqueAlgorithm() = default;
            };
        }
    }
}
