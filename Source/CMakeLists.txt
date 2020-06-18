set_property(TARGET test PROPERTY CXX_STANDARD 17)

# target_compile_options(
# 	test
# 	PRIVATE
# 		$<$<CXX_COMPILER_ID:MSVC>>
# )

target_include_directories(
	test
	PRIVATE
		"${PROJECT_SOURCE_DIR}/Dependencies/stb")

target_sources(
	test
	PRIVATE
		color.hpp color.cpp
		main.hpp main.cpp)
