cmake_minimum_required(VERSION 3.13)

project(MldNeuralNetwork VERSION 0.0.1 LANGUAGES C ASM)

set(CMAKE_C_STANDARD 99)

# Default Build Type to be Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

option(BUILD_SHARED_LIBS "Build library as shared." OFF)

if(BUILD_SHARED_LIBS AND UNIX)
  option(CMAKE_POSITION_INDEPENDENT_CODE "Build with Position Independant Code." ON)
endif()

include(CheckIncludeFile)
include(CheckSymbolExists)
include(GNUInstallDirs)

macro(setup_include_and_definitions TARGET_NAME)
  target_include_directories(${TARGET_NAME}
    PUBLIC  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  )
endmacro()

set(PROCESSOR_IS_RISCV FALSE)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^riscv")
  set(PROCESSOR_IS_RISCV TRUE)
endif()

macro(add_mld_headers_and_sources HDRS_LIST_NAME SRCS_LIST_NAME)
#  list(APPEND ${HDRS_LIST_NAME} ${PROJECT_SOURCE_DIR}/include/mld_common.h)
#  list(APPEND ${HDRS_LIST_NAME} ${PROJECT_SOURCE_DIR}/include/mld_asmdefs.h)
#  list(APPEND ${HDRS_LIST_NAME} ${PROJECT_SOURCE_DIR}/include/mld_matrix.h)

  if(PROCESSOR_IS_RISCV)
      file(GLOB IMPL_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*_riscv.S")
      list(APPEND ${SRCS_LIST_NAME} ${IMPL_SOURCES})
  else()
    message(FATAL_ERROR "Unsupported architecture ${CMAKE_SYSTEM_PROCESSOR}")
  endif()
endmacro()

#
# executable: mld_mnist
#

set(MLD_HDRS)
set(MLD_SRCS)
add_mld_headers_and_sources(MLD_HDRS MLD_SRCS)

add_executable(mld_mnist
	${PROJECT_SOURCE_DIR}/src/main.S
	${MLD_HDRS}
	${MLD_SRCS}
)
setup_include_and_definitions(mld_mnist)
add_executable(MldNeuralNetwork::mld_mnist ALIAS mld_mnist)
