#pragma once

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API
#endif

extern "C" {
    // Create and initialize a BRISQUE algorithm instance
    EXPORT_API void* CreateBrisqueAlgorithm(const char* modelPath, const char* rangePath);

    // Compute BRISQUE score for a given image
    EXPORT_API double ComputeBrisqueScore(void* brisqueInstance, const char* imagePath);

    // Release resources used by a BRISQUE algorithm instance
    EXPORT_API void ReleaseBrisqueAlgorithm(void* brisqueInstance);
}
