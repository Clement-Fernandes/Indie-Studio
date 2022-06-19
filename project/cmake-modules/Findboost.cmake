# Usage:
# FIND_PACKAGE(Boost REQUIRED)
# [...]
# TARGET_LINK_LIBRARIES(target_name Boost)

find_package(Boost REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
