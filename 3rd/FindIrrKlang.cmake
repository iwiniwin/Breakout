if(CMAKE_CL_64)
    # 64 bits

    find_path(IRRKLANG_INCLUDE_DIR NAMES irrKlang.h PATHS "${3RD_DIR}/irrKlang-64bit-1.6.0/include")

    IF(WIN32)
        if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
            message(STATUS "Using MSVC")
            set (IRRKLANG_LIB_DIR "${3RD_DIR}/irrKlang-64bit-1.6.0/lib/Winx64-visualStudio")
            set (IRRKLANG_BIN_DIR "${3RD_DIR}/irrKlang-64bit-1.6.0/bin/Winx64-visualStudio")
            find_library(IRRKLANG_LIBRARY NAMES irrKlang PATHS ${IRRKLANG_LIB_DIR})
        endif()
    endif()
else()
    # 32 bits
    find_path(IRRKLANG_INCLUDE_DIR NAMES irrKlang.h PATHS "${3RD_DIR}/irrKlang-1.6.0/include")

    IF(WIN32)

        if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
            message(STATUS "Using MSVC")
            set (IRRKLANG_LIB_DIR "${3RD_DIR}/irrKlang-1.6.0/lib/Win32-visualStudio")
            set (IRRKLANG_BIN_DIR "${3RD_DIR}/irrKlang-1.6.0/bin/Win32-visualStudio")
            find_library(IRRKLANG_LIBRARY NAMES irrKlang PATHS ${IRRKLANG_LIB_DIR})
        elseif("${CMAKE_CXX_COMPILED_ID}" STREQUAL "GNU")
            message(STATUS "Using GCC")
            set (IRRKLANG_LIB_DIR "${3RD_DIR}/irrKlang-1.6.0/lib/Win32-gcc")
            set (IRRKLANG_BIN_DIR "${3RD_DIR}/irrKlang-1.6.0/bin/Win32-gcc")
            find_library(IRRKLANG_LIBRARY NAMES libirrKlang.a PATHS ${IRRKLANG_LIB_DIR})
        endif()

    elseif(APPLE)
        set (IRRKLANG_BIN_DIR "${3RD_DIR}/irrKlang-1.6.0/bin/macosx-gcc")
        find_library(IRRKLANG_LIBRARY NAMES libirrklang.dylib PATHS "${3RD_DIR}/irrKlang-1.6.0/bin/macosx-gcc")

    elseif(UNIX AND NOT APPLE)
        set (IRRKLANG_BIN_DIR "${3RD_DIR}/irrKlang-1.6.0/bin/inux-gcc")
        find_library(IRRKLANG_LIBRARY NAMES IrrKlang PATHS "${3RD_DIR}/irrKlang-1.6.0/bin/linux-gcc")

    endif()

endif()

set(IRRKLANG_FOUND NO)
if(IRRKLANG_LIBRARY AND IRRKLANG_INCLUDE_DIR)
    set(IRRKLANG_FOUND YES)
endif(IRRKLANG_LIBRARY AND IRRKLANG_INCLUDE_DIR)

if(IRRKLANG_FOUND)
    message(STATUS "IrrKlang found")

    message(STATUS "IRRKLANG_LIBRARY = ${IRRKLANG_LIBRARY}")
    message(STATUS "IRRKLANG_INCLUDE_DIR = ${IRRKLANG_INCLUDE_DIR}")
    message(STATUS "IRRKLANG_BIN_DIR = ${IRRKLANG_BIN_DIR}")
else()
    message(STATUS "ERROR : IrrKlang NOT found !!!")
endif()

