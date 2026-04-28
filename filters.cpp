// Preprocessor directives - include header files
#include "filters.h"  // Our custom header
#include <cmath>      // C++ math library for sqrt(), pow()
#include <algorithm>  // C++ STL algorithms for min(), max()

/**
 * Convert BGR pixel to grayscale using luminance formula
 * @param pixel: BGR pixel from OpenCV (Vec3b is a 3-element vector of unsigned char)
 * @return Grayscale value (0-255)
 * 
 * SYNTAX EXPLANATION:
 * - cv::Vec3b: OpenCV's fixed vector class for 3 unsigned chars (B,G,R order)
 * - const&: Pass by const reference - read-only access without copying
 */
unsigned char bgrToGrayscale(const cv::Vec3b& pixel) {
    /*
     * Luminance formula for grayscale conversion:
     * Y = 0.299 * R + 0.587 * G + 0.114 * B
     * This matches human perception (green contributes most, blue least)
     * 
     * OpenCV stores colors in BGR order, so:
     * - pixel[0] = Blue channel
     * - pixel[1] = Green channel  
     * - pixel[2] = Red channel
     */
    return static_cast<unsigned char>(
        0.299f * pixel[2] +   // Red contribution (float multiplication)
        0.587f * pixel[1] +   // Green contribution
        0.114f * pixel[0]     // Blue contribution
    );
    /*
     * static_cast<unsigned char>: Converts float result to 0-255 range
     * The conversion automatically truncates decimal part
     */
}

/**
 * POSTERIZE FILTER IMPLEMENTATION
 * Reduces colors by quantizing each channel to fewer levels
 */
cv::Mat posterizeFilter(const cv::Mat& input, int levelsPerChannel) {
    /*
     * cv::Mat: OpenCV matrix class
     * .clone(): Creates a deep copy of the image (separate memory)
     * We clone to preserve original while modifying output
     */
    cv::Mat output = input.clone();
    
    /*
     * Calculate quantization step size
     * Example: if levelsPerChannel = 4, stepSize = 256/4 = 64
     * This means: 0-63, 64-127, 128-191, 192-255
     */
    int stepSize = 256 / levelsPerChannel;
    
    /*
     * Nested loops to process each pixel
     * input.rows: Number of rows (image height)
     * input.cols: Number of columns (image width)
     */
    for (int y = 0; y < input.rows; y++) {          // y = row index (vertical)
        for (int x = 0; x < input.cols; x++) {      // x = column index (horizontal)
            
            /*
             * .at<cv::Vec3b>(y, x): Template method to access pixel at (x,y)
             * cv::Vec3b: 3 unsigned chars (B,G,R)
             * Returns a reference to the pixel (we can modify it)
             */
            cv::Vec3b pixel = input.at<cv::Vec3b>(y, x);
            
            /*
             * QUANTIZATION PROCESS for Blue channel (index 0)
             * pixel[0] / stepSize: Integer division (truncates)
             * Example: pixel[0] = 100, stepSize = 64
             * 100/64 = 1 (integer division)
             * 1 * 64 = 64 (quantized to 64)
             */
            pixel[0] = static_cast<unsigned char>((pixel[0] / stepSize) * stepSize);
            pixel[1] = static_cast<unsigned char>((pixel[1] / stepSize) * stepSize);
            pixel[2] = static_cast<unsigned char>((pixel[2] / stepSize) * stepSize);
            
            /*
             * Add half step to center the quantized values
             * Without centering: values map to 0,64,128,192
             * With centering: values map to 32,96,160,224 (better visual distribution)
             * 
             * std::min(): Returns the smaller of two values (ensures we don't exceed 255)
             */
            pixel[0] = std::min<unsigned char>(pixel[0] + stepSize / 2, 255);
            pixel[1] = std::min<unsigned char>(pixel[1] + stepSize / 2, 255);
            pixel[2] = std::min<unsigned char>(pixel[2] + stepSize / 2, 255);
            
            // Write modified pixel back to output image at same position
            output.at<cv::Vec3b>(y, x) = pixel;
        }
    }
    
    // Return the processed image (by value - will use move semantics or RVO)
    return output;
}

/**
 * SOBEL SKETCH FILTER IMPLEMENTATION
 * Detects edges using Sobel operator and creates pencil-sketch effect
 */
cv::Mat sobelSketchFilter(const cv::Mat& input, float edgeThreshold) {
    /*
     * Create output image with same size as input
     * CV_8UC3: 8-bit unsigned char, 3 channels (BGR)
     * This creates a black image initialized to zero
     */
    cv::Mat output(input.size(), CV_8UC3);
    
    /*
     * STEP 1: Convert to grayscale using custom function
     * CV_8UC1: 8-bit unsigned char, 1 channel (grayscale)
     */
    cv::Mat grayscale(input.size(), CV_8UC1);
    
    // Convert each pixel from BGR to grayscale
    for (int y = 0; y < input.rows; y++) {
        for (int x = 0; x < input.cols; x++) {
            /*
             * Access grayscale image pixel:
             * .at<unsigned char>(y, x): Returns reference to single byte
             */
            grayscale.at<unsigned char>(y, x) = 
                bgrToGrayscale(input.at<cv::Vec3b>(y, x));
        }
    }
    
    /*
     * STEP 2: Define Sobel kernels (3x3 convolution matrices)
     * 
     * Sobel-X: Detects horizontal edges (vertical changes)
     * [-1, 0, 1]
     * [-2, 0, 2]
     * [-1, 0, 1]
     * 
     * Sobel-Y: Detects vertical edges (horizontal changes)  
     * [-1, -2, -1]
     * [ 0,  0,  0]
     * [ 1,  2,  1]
     * 
     * const: These values won't change after initialization
     */
    const int sobelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    
    const int sobelY[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
    
    /*
     * STEP 3: Apply Sobel operator
     * CV_32FC1: 32-bit floating point, 1 channel (for gradient magnitude)
     */
    cv::Mat gradient(input.size(), CV_32FC1);
    float maxGradient = 0.0f;
    
    /*
     * Process interior pixels only (skip border where kernel doesn't fit)
     * Border pixels will be handled separately
     */
    for (int y = 1; y < input.rows - 1; y++) {
        for (int x = 1; x < input.cols - 1; x++) {
            float gx = 0.0f;  // Gradient in X direction (horizontal edges)
            float gy = 0.0f;  // Gradient in Y direction (vertical edges)
            
            /*
             * Apply 3x3 convolution kernel
             * ky, kx: Kernel indices from -1 to 1
             * 
             * Example: ky=-1, kx=-1 accesses kernel[0][0] = -1
             * Corresponds to pixel at (x-1, y-1) in image
             */
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    // Calculate image coordinates
                    int pixelX = x + kx;  // X coordinate in image
                    int pixelY = y + ky;  // Y coordinate in image
                    
                    // Get grayscale value at this position
                    unsigned char pixelValue = grayscale.at<unsigned char>(pixelY, pixelX);
                    
                    /*
                     * Multiply pixel by kernel weight and accumulate
                     * ky+1, kx+1: Convert from -1..1 to 0..2 indices
                     */
                    gx += pixelValue * sobelX[ky + 1][kx + 1];
                    gy += pixelValue * sobelY[ky + 1][kx + 1];
                }
            }
            
            /*
             * Calculate gradient magnitude using Pythagoras theorem
             * magnitude = sqrt(gx² + gy²)
             * 
             * sqrt(): Square root function from <cmath>
             * pow() could also be used: pow(gx, 2) but gx*gx is faster
             */
            float magnitude = std::sqrt(gx * gx + gy * gy);
            
            // Store magnitude in gradient matrix
            gradient.at<float>(y, x) = magnitude;
            
            // Track maximum gradient for normalization
            if (magnitude > maxGradient) {
                maxGradient = magnitude;
            }
        }
    }
    
    /*
     * STEP 4: Create sketch effect from gradient magnitudes
     */
    for (int y = 0; y < input.rows; y++) {
        for (int x = 0; x < input.cols; x++) {
            float edgeStrength = 0.0f;
            
            /*
             * Check if pixel is interior (has gradient calculated)
             * Border pixels have no gradient, so edgeStrength remains 0
             */
            if (x > 0 && x < input.cols - 1 && y > 0 && y < input.rows - 1) {
                // Normalize gradient to 0-1 range (divide by maximum)
                edgeStrength = gradient.at<float>(y, x) / maxGradient;
            }
            
            /*
             * Apply threshold: edges below threshold become white (weak edges)
             * Pencil sketches typically emphasize strong edges only
             */
            if (edgeStrength < edgeThreshold) {
                edgeStrength = 0.0f;
            }
            
            /*
             * Create sketch value:
             * 1.0 - edgeStrength: Inverts (edges become dark, flat areas become light)
             * * 255: Scale to 0-255 range
             * 
             * Example: Strong edge (edgeStrength=1.0) -> (1-1)*255 = 0 (black)
             *          No edge (edgeStrength=0)    -> (1-0)*255 = 255 (white)
             */
            unsigned char sketchValue = static_cast<unsigned char>(
                (1.0f - edgeStrength) * 255.0f
            );
            
            /*
             * Apply non-linear contrast enhancement for better sketch look
             * pow(edgeStrength, 0.7f): Gamma correction - brightens mid-tones
             * 
             * std::pow(base, exponent): Power function from <cmath>
             */
            sketchValue = static_cast<unsigned char>(
                255.0f * (1.0f - std::pow(edgeStrength, 0.7f))
            );
            
            /*
             * Clamp values to valid range (0-255)
             * std::max(a, b): Returns larger value
             * std::min(a, b): Returns smaller value
             * This ensures value doesn't exceed limits
             */
            sketchValue = std::min<unsigned char>(255, sketchValue);
            sketchValue = std::max<unsigned char>(0, sketchValue);
            
            /*
             * Set pixel color (grayscale: all RGB channels equal)
             * cv::Vec3b(sketchValue, sketchValue, sketchValue) creates BGR triplet
             */
            output.at<cv::Vec3b>(y, x) = cv::Vec3b(
                sketchValue,  // Blue channel
                sketchValue,  // Green channel
                sketchValue   // Red channel
            );
        }
    }
    
    return output;
}