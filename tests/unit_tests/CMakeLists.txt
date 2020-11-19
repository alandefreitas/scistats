#######################################################
### External Libs                                   ###
#######################################################
CPMAddPackage(NAME ut GIT_REPOSITORY https://github.com/boost-ext/ut/ GIT_TAG master VERSION 1.1.8.1)

#######################################################
### Unit Tests                                      ###
#######################################################
# Common
add_executable(ut_common ut_common.cpp)
target_link_libraries(ut_common PRIVATE scistats boost.ut)
add_test(NAME common_statistics COMMAND ut_common)

# Math
add_executable(ut_math ut_math.cpp)
target_link_libraries(ut_math PRIVATE scistats boost.ut)
add_test(NAME math_statistics COMMAND ut_math)

# Descriptive statistics
add_executable(ut_descriptive ut_descriptive.cpp)
target_link_libraries(ut_descriptive PRIVATE scistats boost.ut)
add_test(NAME descriptive_statistics COMMAND ut_descriptive)

# Probability Distributions
add_executable(ut_distribution ut_distribution.cpp)
target_link_libraries(ut_distribution PRIVATE scistats boost.ut)
add_test(NAME distribution_statistics COMMAND ut_distribution)

# Hypothesis Tests
add_executable(ut_hypothesis ut_hypothesis.cpp)
target_link_libraries(ut_hypothesis PRIVATE scistats boost.ut)
add_test(NAME hypothesis_statistics COMMAND ut_hypothesis)

# Bayesian statistics
add_executable(ut_bayesian ut_bayesian.cpp)
target_link_libraries(ut_bayesian PRIVATE scistats boost.ut)
add_test(NAME bayesian_statistics COMMAND ut_bayesian)
