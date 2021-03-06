
#
# test based on googletest
#

include(FetchContent)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG master
    GIT_SHALLOW 1
)

FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("${googletest_SOURCE_DIR}" "${googletest_BINARY_DIR}" EXCLUDE_FROM_ALL)
endif()

add_library(GTest::Main ALIAS gtest_main)
add_library(GMock::Main ALIAS gmock_main)

target_compile_features(gtest PUBLIC cxx_std_17)
target_compile_features(gtest_main PUBLIC cxx_std_17)
target_compile_features(gmock PUBLIC cxx_std_17)
target_compile_features(gmock_main PUBLIC cxx_std_17)

option(USE_ASAN "Use address sanitizer by adding -fsanitize=address -fno-omit-frame-pointer flags" OFF)
option(USE_UBSAN "Use address sanitizer by adding -fsanitize=undefined -fno-sanitize-recover=all -fno-omit-frame-pointer flags" OFF)

function(ADD_UNIT_TEST TEST_NAME TEST_SOURCE)
    add_executable(${TEST_NAME} "${TEST_SOURCE}")

    set_target_properties(${TEST_NAME} PROPERTIES POSITION_INDEPENDENT_CODE 1)
    target_link_libraries(
            ${TEST_NAME}
        PRIVATE
            GMock::Main
            Threads::Threads
    )
    target_include_directories(
        ${TEST_NAME}
            PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
    )
    add_test(NAME gtest_${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)

    if(USE_ASAN)
        target_compile_options(${TEST_NAME} PUBLIC -fsanitize=address -fno-omit-frame-pointer)
        target_link_libraries(${TEST_NAME} PUBLIC -fsanitize=address)
    endif()

    if(USE_UBSAN)
        target_compile_options(${TEST_NAME} PUBLIC -fsanitize=undefined -fno-sanitize-recover=all -fno-omit-frame-pointer)
        target_link_libraries(${TEST_NAME} PUBLIC -fsanitize=undefined)
    endif()
endfunction()

option(BUILD_GOOGLE_BASED_TESTS "Enable building googletest-based unit tests." OFF)
if (${BUILD_GOOGLE_BASED_TESTS})
    ADD_UNIT_TEST(runtime_polymorphism runtime_polymorphism.cpp)
endif (${BUILD_GOOGLE_BASED_TESTS})