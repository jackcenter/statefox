find_package(Doxygen REQUIRED)

function(add_doxygen_target target_name project_name input_dir output_dir)
    set(DOXYFILE_IN "${CMAKE_SOURCE_DIR}/cmake/Doxyfile.in")
    set(DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile_${target_name}")

    file(MAKE_DIRECTORY "${output_dir}")

    set(PROJECT_NAME ${project_name})
    set(INPUT "${input_dir}")
    set(OUTPUT_DIRECTORY "${output_dir}")
    set(STRIP_FROM_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    add_custom_target(${target_name}_doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating Doxygen docs for ${target_name}"
        VERBATIM
    )
endfunction()
