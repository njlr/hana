# Copyright Louis Dionne 2013-2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
#
#
# This CMake module finds the Brigand include directory. This module sets the
# following CMake variables:
#
# BRIGAND_FOUND
#   Set to 1 when the MPL11 include directory is found, 0 otherwise.
#
# BRIGAND_INCLUDE_DIR
#   If the Brigand include directory is found, this is set to the path of that
#   directory. Otherwise, this is not set.
#
#
# The following variables can be used to customize the behavior of the module:
#
# BRIGAND_INCLUDE_DIR
#   The path to the Brigand include directory. When set, this will be used as-is.
#
# BRIGAND_CLONE_IF_MISSING
#   If the Brigand include directory can't be found and this is set to true,
#   the Brigand project will be cloned locally.

if (NOT EXISTS "${BRIGAND_INCLUDE_DIR}")
    find_path(BRIGAND_INCLUDE_DIR NAMES brigand/brigand.hpp
                                  DOC "Brigand library header files")
endif()

if (NOT EXISTS "${BRIGAND_INCLUDE_DIR}" AND BRIGAND_CLONE_IF_MISSING)
    include(ExternalProject)
    ExternalProject_Add(Brigand EXCLUDE_FROM_ALL 1
        GIT_REPOSITORY https://github.com/edouarda/brigand
        TIMEOUT 5
        CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        BUILD_COMMAND ""   # Disable build step
        INSTALL_COMMAND "" # Disable install step
        TEST_COMMAND ""    # Disable test step
    )

    ExternalProject_Get_Property(Brigand SOURCE_DIR)
    set(BRIGAND_INCLUDE_DIR "${SOURCE_DIR}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Brigand DEFAULT_MSG BRIGAND_INCLUDE_DIR)
