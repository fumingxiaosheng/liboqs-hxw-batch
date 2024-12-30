# Install script for directory: /home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/hxw/oqs-provider-hxw/.local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/common/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/kem/bike/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/kem/ntruprime/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/kem/kyber/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/kem/ml_kem/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/kem/oskrprime/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/sig/dilithium/cmake_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/liboqs" TYPE FILE FILES
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/liboqsConfig.cmake"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/liboqsConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/liboqs.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/lib/liboqs.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liboqs/liboqsTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liboqs/liboqsTargets.cmake"
         "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/CMakeFiles/Export/lib/cmake/liboqs/liboqsTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liboqs/liboqsTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liboqs/liboqsTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/liboqs" TYPE FILE FILES "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/CMakeFiles/Export/lib/cmake/liboqs/liboqsTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/liboqs" TYPE FILE FILES "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/src/CMakeFiles/Export/lib/cmake/liboqs/liboqsTargets-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/oqs" TYPE FILE FILES
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/oqs.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/common/aes/aes_ops.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/common/common.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/common/rand/rand.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/common/sha2/sha2_ops.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/common/sha3/sha3_ops.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/common/sha3/sha3x4_ops.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/kem/kem.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/sig/sig.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/sig_stfl/sig_stfl.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/kem/bike/kem_bike.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/kem/ntruprime/kem_ntruprime.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/kem/kyber/kem_kyber.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/kem/ml_kem/kem_ml_kem.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/kem/oskrprime/kem_oskrprime.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/src/sig/dilithium/sig_dilithium.h"
    "/home/hxw/oqs-provider-hxw/liboqs-hxw-batch/_build/include/oqs/oqsconfig.h"
    )
endif()

