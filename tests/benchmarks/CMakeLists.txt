#######################################################
### Google benchmark                                ###
#######################################################
# Force some options for the google benchmark library
if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DNDEBUG)
    set(LLVMAR_EXECUTABLE ON CACHE BOOL "Release mode" FORCE)
    set(LLVMNM_EXECUTABLE ON CACHE BOOL "Release mode" FORCE)
    set(LLVMRANLIB_EXECUTABLE ON CACHE BOOL "Release mode" FORCE)
    set(GCC_AR ON CACHE BOOL "Release mode" FORCE)
    set(GCC_RANLIB ON CACHE BOOL "Release mode" FORCE)
endif ()
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Enable installation of benchmark" FORCE)

# Find or get the google benchmark library
# Note that CPM will try to find(benchmark) before downloading it
CPMAddPackage(
        NAME benchmark
        GITHUB_REPOSITORY google/benchmark
        VERSION 1.5.1
        OPTIONS
        "BENCHMARK_ENABLE_TESTING Off"
)

if (benchmark_ADDED)
    # patch google benchmark target
    set_target_properties(benchmark PROPERTIES CXX_STANDARD 17)
    target_compile_definitions(benchmark PUBLIC -DNDEBUG)
endif ()

#######################################################
### Benchmarks                                      ###
#######################################################
# These benchmarks are fundamental to find out when
# the parallel algorithms are worth it
# For longer tests with statistical significance, run them with:
# "--benchmark_repetitions=30 --benchmark_display_aggregates_only=true --benchmark_out=data_structure_benchmark.csv --benchmark_out_format=csv"
add_executable(benchmark_mean benchmark_mean.cpp)
target_link_libraries(benchmark_mean PRIVATE scistats benchmark)