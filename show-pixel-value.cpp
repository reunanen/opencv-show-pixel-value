#include "show-pixel-value.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/types_c.h> // for cvScalarAll

ShowPixelValue::ShowPixelValue(const std::string& windowName, const cv::Mat& input)
    : windowName(windowName), input(input)
{
    assert(input.type() == CV_8UC1 || input.type() == CV_8UC3);

    cv::imshow(windowName, input);
    cv::setMouseCallback(windowName, ShowPixelValue::OnMouse, this);    
}

ShowPixelValue::~ShowPixelValue()
{
    cv::setMouseCallback(windowName, NULL, this);
}

cv::Scalar GetOuterColor()
{
    return cvScalarAll(0);
}

cv::Scalar GetInnerColor(int imageType)
{
    return imageType == CV_8UC3
        ? cv::Scalar(128, 255, 128)
        : cv::Scalar(255, 255, 255);
}

void PutText(cv::Mat& input, const std::string& text, const cv::Point& origin)
{
    const double fontSize = 1.0;
    cv::putText(input, text, origin, cv::FONT_HERSHEY_PLAIN, fontSize, GetOuterColor(), 3);
    cv::putText(input, text, origin, cv::FONT_HERSHEY_PLAIN, fontSize, GetInnerColor(input.type()), 1);
}

std::string GetPixelValueText(const cv::Mat& input, int mouseX, int mouseY)
{
    std::ostringstream oss;
    if (input.type() == CV_8UC1) {
        int value = input.at<unsigned char>(cv::Point(mouseX, mouseY));
        oss << value;
    }
    else if (input.type() == CV_8UC3) {
        cv::Vec3b value = input.at<cv::Vec3b>(cv::Point(mouseX, mouseY));
        if (value[0] == value[1] && value[1] == value[2]) {
            oss << static_cast<int>(value[0]) << "*";
        }
        else {
            oss << static_cast<int>(value[0]) << "," << static_cast<int>(value[1]) << "," << static_cast<int>(value[2]);
        }
    }
    else {
        // TODO: implement support for other input image types as needed.
        oss << "Error: unsupported image type (" << input.type() << ")";
    }
    return oss.str();
}

std::string GetCoordinatesText(int mouseX, int mouseY)
{
    std::ostringstream oss;
    oss << "X=" << mouseX << ", Y=" << mouseY;
    return oss.str();
}

void ShowPixelValue::OnMouse(int event, int mouseX, int mouseY, int flags, void* userdata)
{
    ShowPixelValue* showPixelValue = reinterpret_cast<ShowPixelValue*>(userdata);

    if (showPixelValue == NULL) {
        return;
    }

    showPixelValue->Update(mouseX, mouseY, false);
    showPixelValue->UpdateOthers(mouseX, mouseY);
}

void ShowPixelValue::Update(int mouseX, int mouseY, bool showPoint)
{
    if (input.data == NULL) {
        return;
    }

    if (mouseX < 0 || mouseY < 0 || mouseX >= input.cols || mouseY >= input.rows) {
        return;
    }

    input.copyTo(output);

    cv::Point pixelValueOrigin(mouseX + 4, mouseY - 4);
    cv::Point coordinatesOrigin(pixelValueOrigin.x, pixelValueOrigin.y + 20);

    PutText(output, GetPixelValueText(input, mouseX, mouseY), pixelValueOrigin);
    PutText(output, GetCoordinatesText(mouseX, mouseY), coordinatesOrigin);

    if (showPoint) {
        cv::Point point(mouseX, mouseY);
        cv::circle(output, point, 1, GetOuterColor(), 1);
        cv::circle(output, point, 0, GetInnerColor(input.type()), 1);
    }

    cv::imshow(windowName, output);
}

void ShowPixelValue::UpdateOthers(int mouseX, int mouseY)
{
    for (ShowPixelValue* updateTarget : updateTargets) {
        updateTarget->Update(mouseX, mouseY, true);
    }
}

void ShowPixelValue::KeepUpdating(ShowPixelValue* other)
{
    assert(updateTargets.find(other) == updateTargets.end());
    updateTargets.insert(other);
}

void ShowPixelValue::StopUpdating(ShowPixelValue* other)
{
    assert(updateTargets.find(other) != updateTargets.end());
    updateTargets.erase(other);
}
