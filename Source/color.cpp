#include "color.hpp"

#include <cstdint>
#include <utility>
#include <cmath>

Color::Color() {
	_data.rgba = 0;
	_data.comp.a = 255;
}

Color::Color(std::uint32_t rgba) {
	_data.rgba = rgba;
}

Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
	_data.comp.r = r;
	_data.comp.g = g;
	_data.comp.b = b;
	_data.comp.a = a;
}

Color::Color(Color&& other) {
	_data = std::move(other._data);
}

Color::Color(const Color& other) {
	_data = other._data;
}

Color& Color::operator =(Color&& other) {
	_data = std::move(other._data);
	return *this;
}

Color& Color::operator =(const Color& other) {
	_data = other._data;
	return *this;
}

std::uint32_t Color::rgba() const {
	return _data.rgba;
}

void Color::rgba(std::uint32_t value) {
	_data.rgba = value;
}

std::uint8_t Color::r() const {
	return _data.comp.r;
}

void Color::r(std::uint8_t value) {
	_data.comp.r = value;
}

std::uint8_t Color::g() const {
	return _data.comp.g;
}

void Color::g(std::uint8_t value) {
	_data.comp.g = value;
}

std::uint8_t Color::b() const {
	return _data.comp.b;
}

void Color::b(std::uint8_t value) {
	_data.comp.b = value;
}

std::uint8_t Color::a() const {
	return _data.comp.a;
}

void Color::a(std::uint8_t value) {
	_data.comp.a = value;
}

std::uint32_t Color::argb() const {
	union {
		std::uint32_t argb;

		struct {
			std::uint8_t a, r, g, b;
		} comp;
	} result;

	result.comp = {_data.comp.a, _data.comp.r, _data.comp.g, _data.comp.b};
	return result.argb;
}

std::uint32_t Color::abgr() const {
	union {
		std::uint32_t abgr;

		struct {
			std::uint8_t a, b, g, r;
		} comp;
	} result;

	result.comp = {_data.comp.a, _data.comp.b, _data.comp.g, _data.comp.r};
	return result.abgr;
}

void Color::to_gamma(float gamma) {
	apply_rgb([gamma](std::uint8_t c) -> std::uint8_t {
		return std::pow(c / 255.f, gamma) * 255.f;
	});
}

void Color::to_linear(float gamma) {
	to_gamma(1.f / gamma);
}
