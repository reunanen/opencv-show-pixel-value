#include <opencv2/core/core.hpp>

// A wrapper for cv::imshow that shows individual pixel values on mouse hover
struct ShowPixelValue {
public:
    // Show the input image in a window named windowName.
    ShowPixelValue(const std::string& windowName, const cv::Mat& input);
    ~ShowPixelValue();

private:
    const cv::Mat input;
    const std::string windowName;

    cv::Mat output;

    static void OnMouse(int event, int mouseX, int mouseY, int flags, void* userdata);
};
