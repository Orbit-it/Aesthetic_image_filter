#ifndef FILTERS_H  // include guard
#define FILTERS_H  // guard

// Including OpenCV headers for image data types only
#include <opencv2/opencv.hpp>  // Provides cv::Mat class and image I/O functions

/**
 * Posterize Filter - Reduces number of colors in an image
 * @param input: Input image (cv::Mat format from OpenCV)
 * @param levelsPerChannel: Number of intensity levels per RGB channel (default 4)
 * @return Output image with posterized effect (same size and type as input)
 * 
 * Syntax explanation:
 * - cv::Mat: OpenCV's matrix class that stores image data
 * - & (reference): Pass by reference to avoid copying large images
 * - const: Promise not to modify the input image
 */
cv::Mat posterizeFilter(const cv::Mat& input, int levelsPerChannel = 4);

/**
 * Sobel Sketch Filter - Creates pencil-sketch effect using edge detection
 * @param input: Input image (cv::Mat format from OpenCV)
 * @param edgeThreshold: Threshold for edge detection (0-1, default 0.3)
 * @return Output image with sketch effect (grayscale)
 */
cv::Mat sobelSketchFilter(const cv::Mat& input, float edgeThreshold = 0.3f);

// Helper function - declared here but implemented in filters.cpp
unsigned char bgrToGrayscale(const cv::Vec3b& pixel);

#endif  // End of include guard