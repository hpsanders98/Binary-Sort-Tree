cmake_minimum_required(VERSION 3.23)

project(binarySortTree LANGUAGES CXX VERSION 1.0.0)

configure_file(binarySortTreeConfig.h.in binarySortTreeConfig.h)
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

find_package(GTest REQUIRED)

add_library(binarySortTree SHARED)
target_compile_features(binarySortTree PUBLIC cxx_std_17)
target_sources(binarySortTree
    PRIVATE
        binarySortTree.cpp
        node.cpp
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS ${PROJECT_SOURCE_DIR}
            FILES binarySortTree.hpp
            FILES node.hpp
)
target_include_directories(binarySortTree
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(binarySortTree_unittests)
target_compile_features(binarySortTree_unittests PUBLIC cxx_std_17)
target_sources(binarySortTree_unittests PRIVATE binarySortTree_unittests.cpp)
target_include_directories(binarySortTree_unittests PRIVATE "${GTEST_INCLUDE_DIRS}")
target_link_libraries(binarySortTree_unittests
    PRIVATE
        ${GTEST_LIBRARIES}
        ${GTEST_MAIN_LIBRARIES}
        binarySortTree
)

install(TARGETS binarySortTree
    EXPORT binarySortTreeTargets
    FILE_SET HEADERS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)

install(EXPORT binarySortTreeTargets
    FILE binarySortTreeTargets.cmake
    NAMESPACE binarySortTree::
    DESTINATION lib/cmake/binarySortTree)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "binarySortTreeConfigVersion.cmake"
    VERSION ${binarySortTree_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(
    FILES
        "binarySortTreeConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/binarySortTreeConfigVersion.cmake"
    DESTINATION lib/cmake/binarySortTree
)
