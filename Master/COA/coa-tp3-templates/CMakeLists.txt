cmake_minimum_required(VERSION 3.10)

project(
  Templates
  VERSION 0.1
  DESCRIPTION "COA TP3 - Templates")

enable_testing()

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_subdirectory(tests)

