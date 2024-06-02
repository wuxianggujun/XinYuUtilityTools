
#zlib-cmake
set(ZLIB_TEST OFF)

# libxlsxwriter
set(BUILD_TESTS OFF)


add_subdirectory(fltk)
add_subdirectory(zlib-cmake)
add_subdirectory(libxlsxwriter)


function(FLTK_RUN_FLUID TARGET SOURCES)
    set (FLUID_FILES ${${TARGET}})
    foreach(src ${SOURCES})
        if ("${src}" MATCHES "\\.fl$")
            string(REGEX REPLACE "(.*).fl" \\1 basename ${src})
            get_filename_component (src_name ${src} NAME)
            get_filename_component (src_absolute ${src} ABSOLUTE)
            get_filename_component (srcdir_absolute ${src_absolute} DIRECTORY)
            add_custom_command(
                    WORKING_DIRECTORY "${srcdir_absolute}"
                    COMMAND fltk::fluid -c ${src_name}
                    DEPENDS ${src}
                    OUTPUT "${basename}.cpp"
                    OUTPUT "${basename}.h"
            )
            list(APPEND FLUID_FILES "${PROJECT_SOURCE_DIR}/${basename}.cpp")
            list(APPEND FLUID_FILES "${PROJECT_SOURCE_DIR}/${basename}.h")
            list(APPEND FLUID_FILES "${PROJECT_SOURCE_DIR}/${basename}.fl")
        endif ("${src}" MATCHES "\\.fl$")
        set (${TARGET} ${FLUID_FILES} PARENT_SCOPE)
    endforeach(src)
endfunction(FLTK_RUN_FLUID TARGET SOURCES)