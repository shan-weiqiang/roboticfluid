########################## define functions ####################################
function(_find_fastddsidl_compiler)
    set(FASTDDSIDL_COMPILER_CANDIDATES "${FastDDS_PREFIX}/bin/fastddsgen")
    foreach (candidate ${FASTDDSIDL_COMPILER_CANDIDATES})
        if (EXISTS ${candidate})
            set(FASTDDSIDL_COMPILER ${candidate} PARENT_SCOPE)
            return()
        endif ()
    endforeach ()
    message(FATAL_ERROR "FASTDDSIDL_COMPILER_CANDIDATES:" ${FASTDDSIDL_COMPILER_CANDIDATES})
    message(FATAL_ERROR "Couldn't find fastddsgen  compiler. Please ensure that fastddsgen is properly installed to /usr/local from source. Checked the following paths: ${FASTDDSIDL_COMPILER_CANDIDATES}")
endfunction()

# ==================== FASTDDSILD_GENERATE_CXX  ==========================
function(fastdds_generate)
    include(CMakeParseArguments)

    set(_options "")
    set(_singleargs CXX_OUT_VAR HPP_OUT_VAR OUT_DIR)
    set(_multiargs IDLS IMPORT_DIRS)
    cmake_parse_arguments(fastdds_generate "${_options}" "${_singleargs}" "${_multiargs}" "${ARGN}")
    _find_fastddsidl_compiler()

    string(MAKE_C_IDENTIFIER "${fastdds_generate_OUT_DIR}" target_suffix)
    set(target_name "fastdds_generate_${target_suffix}")

    set(generated_cxx)
    set(generated_hpp)
    foreach(idl_file ${fastdds_generate_IDLS})
        get_filename_component(idl_name ${idl_file} NAME_WE)
        list(APPEND generated_cxx 
            "${fastdds_generate_OUT_DIR}/${idl_name}.cxx"
            "${fastdds_generate_OUT_DIR}/${idl_name}PubSubTypes.cxx"
            )
        list(APPEND generated_hpp
            "${fastdds_generate_OUT_DIR}/${idl_name}.h"
            "${fastdds_generate_OUT_DIR}/${idl_name}PubSubTypes.h"
        )
    endforeach()

    add_custom_command(
        OUTPUT ${generated_cxx} ${generated_hpp}
        COMMAND ${FASTDDSIDL_COMPILER}
        ARGS -I ${fastdds_generate_IMPORT_DIRS}
        -d ${fastdds_generate_OUT_DIR}
        -t ${CMAKE_CURRENT_BINARY_DIR}
        -cs -replace
        ${fastdds_generate_IDLS}
        DEPENDS ${fastdds_generate_IDLS}
        COMMENT "Generating FastDDS code for ${fastdds_generate_IDLS}"
        VERBATIM
    )

    add_custom_target(${target_name} ALL
        DEPENDS ${generated_cxx} ${generated_hpp}
    )

    set(${fastdds_generate_CXX_OUT_VAR} ${generated_cxx} PARENT_SCOPE)
    set(${fastdds_generate_HPP_OUT_VAR} ${generated_hpp} PARENT_SCOPE)
    set_property(GLOBAL APPEND PROPERTY FASTDDS_GENERATE_TARGETS ${target_name})
endfunction()
