
#include <filesystem>

#include <tesseract/baseapi.h>

#include "opencv2/core/mat.hpp"
#include "opencv2/opencv.hpp"

namespace su
{

  namespace fs = std::filesystem;

  cv::Mat importImage(const fs::path &image_path)
  {
    if (!fs::exists(image_path))
    {
      throw std::runtime_error("File does not exist.");
    }
    cv::Mat image = cv::imread(image_path.string());
    return image;
  }

  // void OCRTester(const char* imgname, const char* groundtruth, const char* tessdatadir, const char* lang) {
  //   // log.info() << tessdatadir << " for language: " << lang << std::endl;
  //   char* outText;
  //   std::locale loc("");  // You can also use "" for the default system locale
  //   std::ifstream file(groundtruth);
  //   file.imbue(loc);  // Use it for file input
  //   std::string gtText((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  //   std::unique_ptr<tesseract::TessBaseAPI> api(new tesseract::TessBaseAPI());
  //   ASSERT_FALSE(api->Init(tessdatadir, lang)) << "Could not initialize tesseract.";
  //   Pix* image = pixRead(imgname);
  //   ASSERT_TRUE(image != nullptr) << "Failed to read test image.";
  //   api->SetImage(image);
  //   outText = api->GetUTF8Text();
  //   EXPECT_EQ(gtText, outText) << "Phototest.tif OCR does not match ground truth for " <<
  //   ::testing::PrintToString(lang); api->End(); delete[] outText; pixDestroy(&image);
  // }

} // namespace su

int main() { std::cout << "Hello, Wolrd!" << std::endl; }
