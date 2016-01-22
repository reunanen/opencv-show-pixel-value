# opencv-show-pixel-value

Display images using OpenCV so that pixel values are displayed on mouse hover.

## Basic usage

In place of:

	cv::imshow("MyImage", myImage);
	cv::waitKey(0);

try:

	ShowPixelValue show("MyImage", myImage);
	cv::waitKey(0);

Then, when the image is shown, hover your mouse on top of it.

## Connecting windows to each other

In order to connect several windows (usually presenting intermediate or final results related to a single input), try:

	ShowPixelValueConnecter connecter;
	connecter
		.Add("Input", inputImage)
		.Add("Intermediate result 1", intermediateResult1)
		.Add("Intermediate result 2", intermediateResult2)
		.Add("Intermediate result 3", intermediateResult3)
		.Add("Result", result);
	cv::waitKey(0);

Then, hover your mouse on top of one window to see the corresponding points and values in the other windows.