add_executable(example_descriptive descriptive.cpp)
target_link_libraries(example_descriptive PRIVATE scistats)

find_package(Matplot++)
if (Matplot++_FOUND)
    add_executable(example_plots experiment_control.cpp)
    target_link_libraries(example_plots PRIVATE scistats Matplot++::matplot)

    add_executable(example_timing timing.cpp)
    target_link_libraries(example_timing PRIVATE scistats Matplot++::matplot)
endif ()