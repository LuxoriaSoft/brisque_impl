#include "BrisqueAlgorithm.hpp"
#include <stdexcept>

namespace luxoria {
    namespace filter {
        namespace algorithms {
            BrisqueAlgorithm::BrisqueAlgorithm(const std::string& modelPath, const std::string& rangePath) {
                if (modelPath.empty() || rangePath.empty()) {
                    throw std::invalid_argument("Model and range file paths must not be empty.");
                }
                _model = cv::quality::QualityBRISQUE::create(modelPath, rangePath);
            }

            double BrisqueAlgorithm::compute(const cv::Mat& img) const {
                if (img.empty()) {
                    throw std::runtime_error("Input image is empty.");
                }
                cv::Scalar score = _model->compute(img);
                return score[0]; // Return the BRISQUE score
            }
        }
    }
}
