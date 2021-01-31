
#include <gtest/gtest.h>
#include <tesseract/baseapi.h>

#include <array>
#include <filesystem>
#include <memory>
#include <numeric>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/text/ocr.hpp>
#include <string>
#include <thread>

#include "gmock/gmock.h"
namespace su {

namespace fs = std::filesystem;

static constexpr int IMAGE_WIDTH = 100;
static constexpr int IMAGE_HEIGHT = 100;
static cv::Mat createImage(const int red, const int green, const int blue) {
  return cv::Mat(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC3, cv::Scalar(blue, green, red));
}

cv::Mat drawNumberOnImage(const int number, bool save = false) {
  EXPECT_TRUE(0 <= number <= 9);
  cv::Mat image = createImage(87, 161, 50);

  const std::string text = std::to_string(number);
  constexpr double font_scale = IMAGE_WIDTH / 40;
  static const cv::Scalar color(0, 0, 0);
  constexpr int thickness = 3;

  int baseline = 0;
  cv::Size text_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, font_scale, thickness, &baseline);
  const int text_x = (IMAGE_WIDTH - text_size.width) / 2;
  const int text_y = IMAGE_HEIGHT - text_size.height / 2;
  cv::putText(image, text, cv::Point(text_x, text_y), cv::FONT_HERSHEY_SIMPLEX, font_scale, color, thickness);

  if (save) {
    cv::imwrite("/home/sudoku/image_" + text + ".png", image);
  }
  return image;
}

TEST(OCR, DrawnImage) {
  std::unique_ptr<tesseract::TessBaseAPI> api = std::make_unique<tesseract::TessBaseAPI>();
  // Initialize tesseract-ocr with English, without specifying tessdata path
  EXPECT_TRUE(api->SetVariable("classify_bln_numeric_mode", "1"));  // to set numeric-only mode.
  api->SetVariable("tessedit_char_blacklist", "OSxyz");

  if (api->Init(NULL, "eng")) {
    fprintf(stderr, "Could not initialize tesseract.\n");
    exit(1);
  }
  std::array<int, 10> numbers;
  std::iota(numbers.begin(), numbers.end(), 0);

  for (const auto number : numbers) {
    cv::Mat image = drawNumberOnImage(number, true);
    int bytes_per_pixel = image.channels();
    int bytes_per_line = image.step1();
    api->SetImage((uchar *)image.data, image.size().width, image.size().height, bytes_per_pixel, bytes_per_line);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    auto out_text = std::string(api->GetUTF8Text());
    out_text.erase(std::remove(out_text.begin(), out_text.end(), '\n'), out_text.end());

    EXPECT_EQ(out_text, std::to_string(number));
  }
  api->End();
}

}  // namespace su

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
