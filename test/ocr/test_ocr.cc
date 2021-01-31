
#include <gtest/gtest.h>
#include <tesseract/baseapi.h>

#include <filesystem>

#include "gmock/gmock.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/opencv.hpp"

namespace su {

namespace fs = std::filesystem;

static constexpr int IMAGE_WIDTH = 200;
static constexpr int IMAGE_HEIGHT = 200;
static cv::Mat createImage(const int red, const int green, const int blue) {
  return cv::Mat(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC3,
                 cv::Scalar(blue, green, red));
}

// cv::Mat importImage(const fs::path &image_path)
// {
//   if (!fs::exists(image_path))
//   {
//     throw std::runtime_error("File does not exist.");
//   }
//   cv::Mat image = cv::imread(image_path.string());
//   return image;
// }

// void OCRTester(const char* imgname, const char* groundtruth, const char*
// tessdatadir, const char* lang) {
//   // log.info() << tessdatadir << " for language: " << lang << std::endl;
//   char* outText;
//   std::locale loc("");  // You can also use "" for the default system locale
//   std::ifstream file(groundtruth);
//   file.imbue(loc);  // Use it for file input
//   std::string gtText((std::istreambuf_iterator<char>(file)),
//   std::istreambuf_iterator<char>()); std::unique_ptr<tesseract::TessBaseAPI>
//   api(new tesseract::TessBaseAPI()); ASSERT_FALSE(api->Init(tessdatadir,
//   lang)) << "Could not initialize tesseract."; Pix* image = pixRead(imgname);
//   ASSERT_TRUE(image != nullptr) << "Failed to read test image.";
//   api->SetImage(image);
//   outText = api->GetUTF8Text();
//   EXPECT_EQ(gtText, outText) << "Phototest.tif OCR does not match ground
//   truth for " <<
//   ::testing::PrintToString(lang); api->End(); delete[] outText;
//   pixDestroy(&image);
// }
// testing::Matcher(IsBetween, int number, int lo, int hi) {
//   return lo <= number <= hi;
// }

static cv::Mat drawNumberOnImage(int number) {
  EXPECT_TRUE(0 <= number <= 9);
  cv::Mat green_image = createImage(87, 171, 50);

  //   void cv::putText	(	InputOutputArray 	img,
  // const String & 	text,
  // Point 	org,
  // int 	fontFace,
  // double 	fontScale,
  // Scalar 	color,
  // int 	thickness = 1,
  // int 	lineType = LINE_8,
  // bool 	bottomLeftOrigin = false
  // )
  constexpr int middle_point = IMAGE_WIDTH / 2;
  constexpr double font_scale = IMAGE_WIDTH / 40;
  static const cv::Scalar color(0, 0, 0);
  cv::putText(green_image, std::to_string(number),
              cv::Point(middle_point, middle_point), cv::FONT_HERSHEY_SIMPLEX,
              font_scale, color);
  // cv::Mat image = cv::imdecode(green_image, cv::IMREAD_COLOR);
  cv::imwrite("/home/sudoku/image.png", green_image);
  return green_image;
}

TEST(OCR, DrawnImage) {
  auto image = drawNumberOnImage(0);
  ASSERT_TRUE(true);
}

}  // namespace su

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
