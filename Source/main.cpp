#include "main.hpp"

#include <iostream>
#include <filesystem>
#include <array>
#include <cstdint>
#include <string_view>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "color.hpp"

namespace fs = std::filesystem;

static constexpr std::string_view TestImageFileName = "test.bmp";
static constexpr int TestImageWidth = 256;
static constexpr int TestImageHeight = 256;

int main() {
	try {
		if (true || !fs::exists(TestImageFileName)) {
			write_test_image();
			std::cout << "Wrote test image to '" << TestImageFileName << "'.\n";
			return 0;
		}

		return 0;
	} catch (const std::exception& e) {
		std::cerr << "Fatal error: " << e.what() << '\n';
		return 1;
	}
}

void write_test_image() {
	std::array<Color, TestImageWidth * TestImageHeight> img_data;

	for (auto y = 0; y < TestImageHeight; ++y) {
		for (auto x = 0; x < TestImageWidth; ++x) {
			auto& pixel = img_data[x + TestImageWidth * y];

			pixel.r(float(y) / TestImageHeight * 255.f);
			pixel.g(float(x) / TestImageWidth * 255.f);
		}
	}

	std::array<Color, TestImageWidth * (TestImageHeight / 2)> cropped_img_data;

	for (auto y = 0; y < TestImageHeight / 2; ++y) {
		for (auto x = 0; x < TestImageWidth; ++x) {
			cropped_img_data[x + TestImageWidth * y] =
				std::move(img_data[x + TestImageWidth * (y + TestImageHeight / 2)]);
		}
	}

	if (stbi_write_bmp(
		TestImageFileName.data(),
		TestImageWidth,
		TestImageHeight / 2,
		4,
		cropped_img_data.data()) == 0
	) {
		throw std::runtime_error("Failed to write test image file");
	}
}
