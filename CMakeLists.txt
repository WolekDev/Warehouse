project(Warehouse VERSION 1.0.0)

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/helpers.cmake)
  message(
    FATAL_ERROR
      "This cmake list should NOT be the root of the project! Please open the parent folder."
  )
endif()

include(${CMAKE_SOURCE_DIR}/helpers.cmake)

add_lab_targets()
