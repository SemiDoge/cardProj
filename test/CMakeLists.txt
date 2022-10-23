enable_testing()

set (ctests sdlTests )
set (sdlTests_parts 1 2 3 4)

foreach(ctest ${ctests})
    if(NOT DEFINED "${ctest}_parts")
        set(${ctest}_parts "1")
    endif()
endforeach()

foreach(ctest ${ctests})
    set(ctestssrc ${ctestsrc} ${ctest}.cpp)
endforeach()

create_test_sourcelist(srclist test_runner.cpp ${ctestssrc})
add_executable(test_runner ${srclist} ../src/textureManager.cpp ../src/logging.cpp)
target_include_directories(test_runner PUBLIC ../inc/)
target_link_libraries(test_runner ${CONAN_LIBS} -lSDL2_image)


foreach(ctest ${ctests})
    foreach(part ${${ctest}_parts})
       add_test(test_${ctest}_${part}
       ${TEST_PATH}/../bin/test_runner ${ctest} ${part}) 
        set_tests_properties(test_${ctest}_${part} PROPERTIES 
            FAIL_REGULAR_EXPRESSION "ERROR;FAIL;Test failed")
    endforeach()
endforeach()
