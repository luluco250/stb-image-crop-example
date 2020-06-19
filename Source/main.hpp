#ifndef STB_IMAGE_CROP_EXAMPLE_MAIN_HPP
#define STB_IMAGE_CROP_EXAMPLE_MAIN_HPP

#include "color.hpp"

void write_test_image();

void generate_uv_image(int width, int height, Color* data);

void crop_image_vertical(
	int width,
	int height,
	int new_height,
	Color* data);

#endif // Include guard.
