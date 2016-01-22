#include "show-pixel-value.h"
#include <memory>

// A means to connect multiple ShowPixelValue windows to each other
class ShowPixelValueConnecter {
public:
    ~ShowPixelValueConnecter();

    ShowPixelValueConnecter& Add(const std::string& windowName, const cv::Mat& input);

private:
    std::vector<std::unique_ptr<ShowPixelValue>> windows;
};
