#include "show-pixel-value-connecter.h"

ShowPixelValueConnecter::~ShowPixelValueConnecter()
{
    const size_t count = windows.size();
    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < count; ++j) {
            if (i != j) {
                (*windows[i]).StopUpdating(windows[j].get());
            }
        }
    }
}

ShowPixelValueConnecter& ShowPixelValueConnecter::Add(const std::string& windowName, const cv::Mat& input)
{
    std::unique_ptr<ShowPixelValue> newWindow(new ShowPixelValue(windowName, input));
    for (std::unique_ptr<ShowPixelValue>& previousWindow : windows) {
        previousWindow->KeepUpdating(newWindow.get());
        newWindow->KeepUpdating(previousWindow.get());
    }
    windows.push_back(std::move(newWindow));
    return *this;
}
