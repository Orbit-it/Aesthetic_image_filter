/*
 * Include headers
 * "" for local headers (our filters.h)
 * <> for system headers (OpenCV)
 */
#include "filters.h"  // Our filter functions
#include <iostream>   // Standard I/O (cout, cerr)
#include <string>     // String class for filenames

/**
 * Main function - Program entry point
 * @return 0 on success, non-zero on error
 * 
 * int main(): Every C++ program must have a main function
 * The operating system calls this when program starts
 */
int main() {
    /*
     * std::string: C++ string class (safer than C char arrays)
     * = "input.jpg": Initialize with filename
     */
    std::string inputFilename = "input.jpg";
    
    /*
     * cv::imread(): OpenCV function to read image from file
     * Parameters: 
     *   - filename: Path to image file
     *   - cv::IMREAD_COLOR: Load as color image (3 channels)
     * Returns: cv::Mat object containing image data
     * 
     * Auto type deduction (C++11): compiler deduces type from right side
     */
    auto inputImage = cv::imread(inputFilename, cv::IMREAD_COLOR);
    
    /*
     * .empty(): Checks if cv::Mat has no data (file not found or corrupt)
     */
    if (inputImage.empty()) {
        /*
         * std::cerr: Standard error stream (for error messages)
         * <<: Stream insertion operator (like print)
         * std::endl: End line and flush buffer
         */
        std::cerr << "Error: Could not read input image: " << inputFilename << std::endl;
        return 1;  // Return non-zero indicates error to OS
    }
    
    /*
     * Display original image information
     * inputImage.size(): Returns cv::Size object with width and height
     * .width, .height: Access dimensions
     * inputImage.channels(): Number of color channels (3 for BGR)
     */
    std::cout << "Image loaded successfully!" << std::endl;
    std::cout << "Dimensions: " << inputImage.cols << "x" << inputImage.rows << std::endl;
    std::cout << "Channels: " << inputImage.channels() << std::endl;
    std::cout << "------------------------" << std::endl;
    
    /*
     * APPLY POSTERIZE FILTER
     */
    std::cout << "Applying Posterize filter..." << std::endl;
    
    /*
     * Call posterizeFilter function
     * Args: 
     *   - inputImage: The original image
     *   - 6: Use 6 intensity levels per channel (216 total colors)
     * Returns: New image with posterized effect
     */
    cv::Mat posterized = posterizeFilter(inputImage, 6);
    
    /*
     * Save posterized image
     * cv::imwrite(): Write image to file
     * Parameters:
     *   - "posterized.jpg": Output filename (extension determines format)
     *   - posterized: Image data to save
     * Returns: true on success, false on failure
     */
    bool success = cv::imwrite("posterized.jpg", posterized);
    if (success) {
        std::cout << "✓ Posterized image saved as 'posterized.jpg'" << std::endl;
    } else {
        std::cerr << "✗ Failed to save posterized image" << std::endl;
    }
    
    /*
     * APPLY SOBEL SKETCH FILTER
     */
    std::cout << "Applying Sobel Sketch filter..." << std::endl;
    
    /*
     * Call sobelSketchFilter
     * Args:
     *   - inputImage: Original image
     *   - 0.25f: Edge threshold (25% strength needed to show edge)
     *           'f' suffix indicates float literal
     */
    cv::Mat sketch = sobelSketchFilter(inputImage, 0.25f);
    
    success = cv::imwrite("sketch.jpg", sketch);
    if (success) {
        std::cout << "✓ Sketch image saved as 'sketch.jpg'" << std::endl;
    } else {
        std::cerr << "✗ Failed to save sketch image" << std::endl;
    }
    
    /*
     * APPLY POSTERIZE WITH DIFFERENT COLOR LEVELS
     * Demonstrate different parameter
     */
    std::cout << "\nApplying Posterize with 2 levels (extreme posterization)..." << std::endl;
    cv::Mat extremePosterized = posterizeFilter(inputImage, 2);  // 8 total colors
    cv::imwrite("posterized_extreme.jpg", extremePosterized);
    std::cout << "✓ Saved as 'posterized_extreme.jpg'" << std::endl;
    
    /*
     * APPLY SKETCH WITH DIFFERENT THRESHOLD
     * Lower threshold shows more edges
     */
    std::cout << "Applying Sketch with low threshold (more edges)..." << std::endl;
    cv::Mat detailedSketch = sobelSketchFilter(inputImage, 0.1f);
    cv::imwrite("sketch_detailed.jpg", detailedSketch);
    std::cout << "✓ Saved as 'sketch_detailed.jpg'" << std::endl;
    
    /*
     * OPTIONAL: Display images using OpenCV window
     * Only if DISPLAY_IMAGES macro is defined
     */
    #ifdef DISPLAY_IMAGES
    /*
     * cv::namedWindow(): Create window for display
     * cv::WINDOW_NORMAL: Allows window resizing
     */
    cv::namedWindow("Original", cv::WINDOW_NORMAL);
    cv::namedWindow("Posterized", cv::WINDOW_NORMAL);
    cv::namedWindow("Sketch", cv::WINDOW_NORMAL);
    
    /*
     * cv::imshow(): Display image in window
     */
    cv::imshow("Original", inputImage);
    cv::imshow("Posterized", posterized);
    cv::imshow("Sketch", sketch);
    
    /*
     * cv::waitKey(): Wait for keyboard input
     * 0 means wait indefinitely
     * Returns ASCII code of pressed key
     */
    std::cout << "\nPress any key to close windows..." << std::endl;
    cv::waitKey(0);
    
    /*
     * cv::destroyAllWindows(): Close all OpenCV windows
     */
    cv::destroyAllWindows();
    #endif
    
    /*
     * Return 0 to indicate successful completion
     */
    std::cout << "\nAll operations completed successfully!" << std::endl;
    return 0;
}