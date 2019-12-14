project(FOSL-ILI9341)

add_library(
	${PROJECT_NAME}

	./FOSL/ILI9341.hpp
	./FOSL/ILI9341/Base-impl.hpp
	./FOSL/ILI9341/Base.hpp
	./FOSL/ILI9341/Color.hpp
	./FOSL/ILI9341/Point.hpp
	./FOSL/ILI9341/COMMAND.hpp
	./FOSL/ILI9341/ROTATION.hpp
)

target_include_directories(
	${PROJECT_NAME} PUBLIC

	${PROJECT_SOURCE_DIR}
)

target_link_libraries(
	${PROJECT_NAME}

	FOSL-Utilities
)
