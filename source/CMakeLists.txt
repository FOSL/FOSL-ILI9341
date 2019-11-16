project(fosl-ili9341)

add_library(
	${PROJECT_NAME}

	./fosl/ili9341/base.cpp
	./fosl/ili9341/base.h
	./fosl/ili9341/color.h
	./fosl/ili9341/defs.h
	# ./fosl/ili9341/font/example.h
	./fosl/ili9341/point.h
)

target_include_directories(
	${PROJECT_NAME} PUBLIC

	${PROJECT_SOURCE_DIR}
	${fosl-math_SOURCE_DIR}
	${fosl-util_SOURCE_DIR}
)
