cmake_minimum_required(VERSION 3.0)
project(TCore)

set(TCORE_VERSION 1.0)

include_directories(include)

add_library(TCore SHARED src/tInit.c src/tRegisterPlugin.c src/tStart.c src/tDestroy.c)

target_include_directories(TCore PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

set_target_properties(TCore PROPERTIES OUTPUT_NAME "TCore")

set_target_properties(TCore PROPERTIES VERSION ${TCORE_VERSION})

install(TARGETS TCore
  EXPORT TCoreTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(FILES include/t.h DESTINATION include)

install(EXPORT TCoreTargets
  FILE TCoreTargets.cmake
  DESTINATION lib/cmake/TCore
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "TCoreConfigVersion.cmake"
  VERSION ${TCORE_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/TCoreConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/TCoreConfigVersion.cmake"
  DESTINATION lib/cmake/TCore
)

export(EXPORT TCoreTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/TCoreTargets.cmake"
  NAMESPACE TCore::
)
