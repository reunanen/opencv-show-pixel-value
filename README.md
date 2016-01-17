# opencv-show-pixel-value

Display images using OpenCV so that pixel values are displayed on mouse hover.

## Usage

In place of:

	cv::imshow("MyImage", myImage);
	cv::waitKey(0);

try:

	ShowPixelValue show("MyImage", myImage);
	cv::waitKey(0);

Then, when the image is shown, hover your mouse on top of it.
