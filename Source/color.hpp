#ifndef STB_IMAGE_CROP_EXAMPLE_COLOR_HPP
#define STB_IMAGE_CROP_EXAMPLE_COLOR_HPP

#include <cstdint>

class Color {
private:
	union {
		std::uint32_t rgba;

		struct {
			std::uint8_t r, g, b, a;
		} comp;
	} _data;

public:
	Color();
	Color(std::uint32_t rgba);
	Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255);
	Color(Color&& other);
	Color(const Color& other);

	Color& operator =(Color&& other);
	Color& operator =(const Color& other);

	std::uint32_t rgba() const;
	void rgba(std::uint32_t value);

	std::uint8_t r() const;
	void r(std::uint8_t value);

	std::uint8_t g() const;
	void g(std::uint8_t value);

	std::uint8_t b() const;
	void b(std::uint8_t value);

	std::uint8_t a() const;
	void a(std::uint8_t value);

	std::uint32_t argb() const;

	std::uint32_t abgr() const;
};

#endif // Include guard.
