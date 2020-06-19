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

static constexpr std::string_view TestImageFullFileName = "full.bmp";
static constexpr std::string_view TestImageCropFileName = "crop.bmp";
static constexpr int TestImageWidth = 256;
static constexpr int TestImageHeight = 256;

int main() {
	try {
		write_test_image();
		std::cout << "Wrote test images.\n";

		return 0;
	} catch (const std::exception& e) {
		std::cerr << "Fatal error: " << e.what() << '\n';
		return 1;
	}
}

void write_test_image() {
	std::array<Color, TestImageWidth * TestImageHeight> img;

	generate_uv_image(TestImageWidth, TestImageHeight, img.data());

	if (
		stbi_write_bmp(
			TestImageFullFileName.data(),
			TestImageWidth,
			TestImageHeight,
			4,
			img.data()) == 0
	) {
		throw std::runtime_error("Failed to write full test image file");
	}

	constexpr int new_height = TestImageWidth / (2560.f / 1080.f);

	crop_image_vertical(
		TestImageWidth,
		TestImageHeight,
		new_height,
		img.data());

	if (
		stbi_write_bmp(
			TestImageCropFileName.data(),
			TestImageWidth,
			new_height,
			4,
			img.data()) == 0
	) {
		throw std::runtime_error("Failed to write test image file");
	}
}

void generate_uv_image(int width, int height, Color* data) {
	for (auto y = 0; y < height; ++y) {
		for (auto x = 0; x < width; ++x) {
			auto& pixel = data[x + width * y];

			pixel.r(float(x) / width * 255.f);
			pixel.g(float(y) / height * 255.f);

			pixel.to_gamma();
		}
	}
}

void crop_image_vertical(
	int width,
	int height,
	int new_height,
	Color* data
) {
	if (new_height > height)
		throw std::logic_error(
			"The new height must be smaller than the original");

	if (new_height == height)
		return;

	// Height of the letterboxes.
	int crop = (height - new_height) / 2;

	// Shift pixels.
	for (auto y = 0; y < new_height; ++y)
		for (auto x = 0; x < width; ++x)
			data[x + width * y] = std::move(data[x + width * (y + crop)]);
}
