# Mid-Term Project Technical Report

Part 1: Common Section
1.1. Team Members
•	Andrés Vidal Mira
•	Serigne Mansour Diop
1.2. Title and Assignment
•	Title: Implementation and Demonstration of Aesthetic Image Filter Effects.
•	Assignment: The objective is to design, implement, and demonstrate a set of image filters that produce visually distinctive, aesthetically valuable effects. The assignment requires the implementation of the filters from scratch and the creation of an application that allows the demostration for parameter experimentation.
1.3. Description of the Solution and Current Progress
Our solution involves implementing four distinct aesthetic filters with different image processing domains: spatial convolution for Emboss and Sharpen filters, color domain mapping for Posterize filter, and gradient analysis for Sobel Sketch filter.
•	Current Progress: We have successfully developed the initial mathematical logic for all four filters. Currently, we have a test scripts which load the images, apply the fixed mathematical kernels or color mappings, and use Matplotlib to display the comparison of the original and processed images.
•	Objectives and Final Solution Proposal: To fully meet the requirements of a demonstration application, our main goal for the final code is to upgrade these static tests into real-time interactive scripts. We will replace Matplotlib with OpenCV's capabilities, implementing cv2.createTrackbar. This will allow the user to dynamically adjust the intensity, thresholds, and color levels of each filter via sliders because with this we can see the aesthetic effects render in real-time.
1.4. Description of the Data
The project is being developed and tested using a dataset of the lecture tasks because in our opinion it is the best data to compare specific filter behaviors:
•	fit.jpg: Used to evaluate how spatial filters (Emboss) interact with architectural lines, and how color quantization (Posterize) flattens solid colors like the sky and roof.
•	lena.png: Used as a standard baseline to examine the aesthetic impact of contrast enhancement (Sharpen) and edge detection (Sobel) on smooth gradients and human facial features.
•	garden.jpg: Reserved for additional testing because the dense textures and structural complexity of the image obscured the visual impact of the applied filters.
1.5. Division of Labor
•	Andrés Vidal Mira: Implementation of the main interactive GUI framework. Development and analysis of spatial convolution filters like Image Relief (Emboss) and Highlighted Image (Sharpen).
•	Serigne Mansour Diop : Compilation of the final project documentation. Development and analysis of color and gradient-based filters like Quantized Image (Posterize) and Stylized Edges (Sobel Sketch).
Part 2: Individual Section - Andrés Vidal Mira
2.1. Summary of Studied Knowledge
I studied how image filters work using mathematical grids called "kernels" (usually 3x3 matrices). Sliding these matrices over an image, we can calculate new values based on the neighbors of the pixels.
•	For the Emboss filter, I learned how to use a matrix that subtracts values from one side and adds them to the other. This creates artificial light and shadow, giving the image a 3D appearance.
•	For the Sharpen filter, I studied how to use a kernel with a positive center and negative values. This amplifies the central pixels against their edges, increasing the overall contrast and making more details.

2.2. Planned Technologies and Libraries
•	Programming Language: Python
•	Libraries: We are using OpenCV because to load the images, generate the interactive GUI window and apply the matrices using the cv2.filter2D function.
o	NumPy: To create and multiply the numerical arrays required for the spatial filters.
o	Matplotlib: Used in the testing phase for static plotting.
2.3. Solution Proposal for the Actual Part
My goal for the final project is to turn my current static tests into interactive applications. I will use OpenCV to create a window with a slider because with this will control an intensity variable in a real-time loop. The code will take a neutral matrix, which leaves the image unchanged and gradually add the Emboss or Sharpen matrix to it, depending on the slider's position. This dynamic calculation will allow the user to smoothly transition from the original photo to the fully filtered image. With this we can apreciate how the parameters affect the aesthetics. 


Part 3: Individual Section - Serigne Mansour Diop
2.1. Summary of Studied Knowledge
My focus has been on how to group colors and how to find the outlines of objects in an image. For the Posterize effect, I studied how to reduce the number of colors in an image. Dividing and multiplying pixel values we can group similar colors together, replacing smooth gradients with flat blocks of color to create a comic book style. For the Sobel effect, I learned how to detect edges by reviewing the Sobel method, calculating the differences between neighboring pixels horizontally and vertically. By combining these differences and inverting the colors we can highlight the strong lines to mimic a pencil drawing on white paper.
2.2. Planned Technologies and Libraries
•	Programming Language: Python
•	Libraries: 
o	NumPy: used to perform mathematical operations on the whole image at once.
o	OpenCV: Utilized for color space conversions, gradient calculations...
2.3. Solution Proposal for the Actual Part
My plan is to turn my current static codes into fully interactive applications using OpenCV sliders. For the Posterize filter, the static math will be replaced by a trackbar that controls the color levels because the code will dynamically change the reduction factor and instantly flatten the colors on the screen. For the Sobel Sketch filter, I also will introduce a user-controlled threshold slider inside the main loop. Instead of just showing a fixed drawing with all the background noise, the user will be able to adjust the slider to hide the weak lines and keep only the strongest edges t osee better the results.
Part 4: Literature and Sources Used
•	Course materials and lecture slides covering Edge Detection and Gradient Analysis.
•	Course materials and lecture slides covering Noise and Optimal Filtering.
•	Gonzalez, R. C., & Woods, R. E. (2018). Digital Image Processing. Pearson. (Focus on Color Image Processing and Spatial Filtering).
•	Official OpenCV Documentation for Python (Image Gradients, Thresholding modules Image and Filtering modules).

