cmake_minimum_required(VERSION 3.26.3)
project(Tempest VERSION 0.1.0)
add_executable(Tempest main.c glad.c)

target_include_directories(${PROJECT_NAME}
	PUBLIC ./vendor/GLFW/include
	PUBLIC ./vendor/glad/include)

