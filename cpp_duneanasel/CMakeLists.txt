cmake_minimum_required(VERSION 3.20)
project(rntuplecaf_examples_duneanasel)

if(CMAKE_INSTALL_PREFIX STREQUAL "" OR CMAKE_INSTALL_PREFIX STREQUAL
  "/usr/local")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")
elseif(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")
endif()

add_library(rntuplecaf_examples_duneanasel INTERFACE)

# --- duneanaobj ---

include(FetchContent)
FetchContent_Declare(
  srproxy
  GIT_REPOSITORY https://github.com/cafana/SRProxy
  GIT_TAG        main
)
FetchContent_MakeAvailable(srproxy)

# if(NOT DUNE_ANAOBJ_BRANCH)
#   set(DUNE_ANAOBJ_BRANCH v04_01_00)
# endif()

find_package(duneanaobj)
if(NOT duneanaobj_FOUND) # need to fetch it
  include(FetchContent)
  FetchContent_Declare(
      duneanaobj
      GIT_REPOSITORY https://github.com/DUNE/duneanaobj.git
      GIT_TAG        c808e0 # special branch which handles the standard record root dictionaries diffeently
    )
  set(SKIP_CET ON)
  FetchContent_MakeAvailable(duneanaobj)
endif()

target_include_directories(rntuplecaf_examples_duneanasel INTERFACE
  "${duneanaobj_SOURCE_DIR}")

if(TARGET duneanaobj::StandardRecord)
  target_link_libraries(rntuplecaf_examples_duneanasel INTERFACE
    duneanaobj::StandardRecord
)
elseif(TARGET StandardRecord)
  target_link_libraries(rntuplecaf_examples_duneanasel INTERFACE
    StandardRecord
)
else()
  message(FATAL_ERROR "Could not find a duneanaobj StandardRecord target")
endif()

# --- duneanasel ---

find_package(duneanasel)
if(NOT duneanasel_FOUND)
  # downloaf CPM
  file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.43.1/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  )
  include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

  CPMAddPackage(
    NAME duneanasel
    GITHUB_REPOSITORY DUNE/duneanasel
    GIT_TAG           main
    DOWNLOAD_ONLY     YES
  )
endif()

target_include_directories(rntuplecaf_examples_duneanasel INTERFACE
  "${duneanasel_SOURCE_DIR}")

# --- ROOT ---

find_package(ROOT 6 REQUIRED)

target_link_libraries(rntuplecaf_examples_duneanasel INTERFACE
  ROOT::Core
  ROOT::Tree
  ROOT::RIO
  ROOT::ROOTNTuple
  ROOT::ROOTNTupleUtil
)

foreach(app
  selection_duneanasel
)
  add_executable(${app} ${app}.cpp)
  target_link_libraries(${app} PUBLIC
    rntuplecaf_examples_duneanasel)
endforeach()