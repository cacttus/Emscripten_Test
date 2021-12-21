
#
# emcmake cmake -S~/Desktop/em_test/ -B~/Desktop/em_test/build && cmake --build ~/Desktop/em_test/build
#
# We need to merge this with em++
#
# em++ -g -g4 -std=c++17 -pthread -s PTHREAD_POOL_SIZE=16 -s PTHREAD_POOL_SIZE_STRICT=4 -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s FULL_ES3=1 ~/Desktop/em_test/hello.cpp -s -o ~/Desktop/em_test/hello.html
##

cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Utils
function(GET_ARCH_CONFIG)
  set(ARCH_CONFIG "_")  

  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_SIZE Lib)
    string(APPEND ARCH_CONFIG x86)
  else()
    string(APPEND ARCH_CONFIG x64) 
  endif()
   
  # Target
  if(GENERATOR_IS_MULTI_CONFIG)
    message("Error: Generator is MULTI CONFIG")
    return()
    # "Multi-config generators use CMAKE_CONFIGURATION_TYPES as the set of configurations and ignore CMAKE_BUILD_TYPE."
  else()
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(ARCH_CONFIG ${ARCH_CONFIG}d PARENT_SCOPE)
    else ()
      set(ARCH_CONFIG ${ARCH_CONFIG}r PARENT_SCOPE)
    endif()
  endif() 
endfunction()  
  
message("CMAKE_MODULE_PATH='" ${CMAKE_MODULE_PATH} "' CMAKE_PREFIX_PATH='" ${CMAKE_PREFIX_PATH} "' CMAKE_TOOLCHAIN_PATH='" ${CMAKE_TOOLCHAIN_PATH} "'")
    
# ** Global Directories **  
set(EMSCRIPTEN_TEST_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
set(EMSCRIPTEN_TEST_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/)
set(EMSCRIPTEN_TEST_BIN_DEBUG_DIR ${EMSCRIPTEN_TEST_BIN_DIR})
set(EMSCRIPTEN_TEST_BIN_RELEASE_DIR ${EMSCRIPTEN_TEST_BIN_DIR})


# VG 
set(EMSCRIPTEN_TEST_PROJECT_VERSION 0.0.1)
set(EMSCRIPTEN_TEST_TARGET_NAME Emscripten_Test)
project(${EMSCRIPTEN_TEST_TARGET_NAME} VERSION ${EMSCRIPTEN_TEST_PROJECT_VERSION} LANGUAGES CXX C)

if(WIN32) 
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/ext/") 
message("Set Module Path to " ${CMAKE_MODULE_PATH} "Win32")
endif() 

# VG
add_executable(${EMSCRIPTEN_TEST_TARGET_NAME} 
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/src/lodepng.cpp 
)
  
get_arch_config()  
 
set(EMSCRIPTEN_TEST_OUTPUT_NAME ${EMSCRIPTEN_TEST_TARGET_NAME}-${PROJECT_VERSION}${ARCH_CONFIG})
message("Output: " ${EMSCRIPTEN_TEST_OUTPUT_NAME})
 
set_target_properties(${PROJECT_NAME} PROPERTIES 
  OUTPUT_NAME ${EMSCRIPTEN_TEST_OUTPUT_NAME}
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EMSCRIPTEN_TEST_BIN_DEBUG_DIR}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EMSCRIPTEN_TEST_BIN_RELEASE_DIR}
  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${EMSCRIPTEN_TEST_BIN_DEBUG_DIR}
  RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${EMSCRIPTEN_TEST_BIN_DEBUG_DIR}
  ARCHIVE_OUTPUT_DIRECTORY ${EMSCRIPTEN_TEST_LIB_DIR}
)
  
# Packages
find_package(Threads REQUIRED) #This is better than -pthread

#set(OpenGL_GL_PREFERENCE LEGACY) #GLVND or LEGACY
find_package(OpenGL REQUIRED)



if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_SDL=2 -s USE_FREETYPE=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
  find_package(SDL2 REQUIRED)
  #find_package(Vulkan REQUIRED)  
  find_package(glm REQUIRED)
  if(UNIX)
    find_package(X11 REQUIRED)
  endif()
endif()


 
# Includes
target_include_directories(${PROJECT_NAME} PUBLIC 
${SDL2_INCLUDE_DIRS} 
"./third_party/"
#${SDLNET_INCLUDE_DIR} 
#${VULKAN_INCLUDE_DIRS} 
#${LUA_INCLUDE_DIR} 
#${LUAINTF_INCLUDE_DIR}
)

# Libraries
set(ADDL_LIBS "")
if(WIN32)
  set(EMSCRIPTEN_TEST_WIN32_COMPILE_OPTS "")

  #Unicode required for building with Unicode Character Set (vs MBCS)
  string(APPEND EMSCRIPTEN_TEST_WIN32_COMPILE_OPTS " -DUNICODE")
  string(APPEND EMSCRIPTEN_TEST_WIN32_COMPILE_OPTS " -D_UNICODE")

  #Suppress error
  string(APPEND EMSCRIPTEN_TEST_WIN32_COMPILE_OPTS " -D_CRT_NO_VA_START_VALIDATION")

  #Multicore build
  string(APPEND EMSCRIPTEN_TEST_WIN32_COMPILE_OPTS /MP) #NOte: originally CMAKE_CXX_FLAGS

  target_compile_options(${EMSCRIPTEN_TEST_TARGET_NAME} PRIVATE "$<$<CONFIG:RELEASE>:" ${EMSCRIPTEN_TEST_WIN32_COMPILE_OPTS})
  target_compile_options(${EMSCRIPTEN_TEST_TARGET_NAME} PRIVATE "$<$<CONFIG:DEBUG>:" ${EMSCRIPTEN_TEST_WIN32_COMPILE_OPTS} -D_DEBUG -D_GLIBCXX_DEBUG)
 
  find_package(SDL2_net REQUIRED)
  set(EMSCRIPTEN_TEST_ADDL_LIBS "ws2_32.lib" "winmm.lib" "imm32.lib" "version.lib" "dbghelp.lib" "setupapi.lib" "iphlpapi.lib")
elseif(CMAKE_COMPILER_IS_GNUCXX OR MINGW OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
set(EMSCRIPTEN_TEST_GCC_LINK_GLOBAL -pthread) 

  target_compile_options(${EMSCRIPTEN_TEST_TARGET_NAME} PRIVATE "$<$<CONFIG:DEBUG>:" -D_DEBUG -D_GLIBCXX_DEBUG ">")
  target_compile_options(${EMSCRIPTEN_TEST_TARGET_NAME} PRIVATE "$<$<CONFIG:RELEASE>:" -Ofast ">")

  target_link_options(${EMSCRIPTEN_TEST_TARGET_NAME} PRIVATE "$<$<CONFIG:RELEASE>:" ${EMSCRIPTEN_TEST_GCC_LINK_GLOBAL} ">")
  target_link_options(${EMSCRIPTEN_TEST_TARGET_NAME} PRIVATE "$<$<CONFIG:DEBUG>:" ${EMSCRIPTEN_TEST_GCC_LINK_GLOBAL} ">")
   
  #set(VULKAN_LIBRARIES vulkan)
  #set(SDLNET_LIBRARIES SDL2_net) 
 # set(EMSCRIPTEN_TEST_ADDL_LIBS ncurses)
endif() 
target_link_directories(${PROJECT_NAME} PRIVATE ${EMSCRIPTEN_TEST_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE 
#${VULKAN_LIBRARIES} 
${OPENGL_LIBRARIES} 
${SDL2_LIBRARIES} 
#${SDLNET_LIBRARIES} 
${EMSCRIPTEN_TEST_ADDL_LIBS} 
${X11_LIBRARIES} 
#${LUA_LIBRARIES}

#${CMAKE_CURRENT_SOURCE_DIR}/../VulkanGame/lib/libVulkanGame-0.4.1_x86d.a
)

 
#Compile shaders.

#set(shader_path ${CMAKE_CURRENT_LIST_DIR}/)
#file(GLOB shaders RELATIVE ${CMAKE_SOURCE_DIR} "${shader_path}*.vs" "${shader_path}*.fs")
#foreach(shader ${shaders})
#  set(input_glsl "${CMAKE_CURRENT_LIST_DIR}/${shader}")
#  set(output_spv "${input_glsl}.spv")
#  execute_process(COMMAND "glslc" "${input_glsl}" "-o" "${output_spv}")
#endforeach()

#--CMakeLists.txt--
#file(GLOB_RECURSE SHADER_FILES ${CMAKE_CURRENT_LIST_DIR}/*.vs *.fs *.gs)
#add_custom_target(compile_shaders ALL
#COMMAND ${CMAKE_CURRENT_LIST_DIR}/compile_shaders.sh 
#SOURCES ${SHADER_FILES} 
#DEPENDS ${SHADER_FILES}
#WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})


#--compile_shaders.sh--
# FILE=./shaderc/bin/glslc
# if test -f "$FILE"; then
#   echo "Compiling Shaders."
#   ./shaderc/bin/glslc -fshader-stage=vertex ./test.vs -o ./test_vs.spv
#   ./shaderc/bin/glslc -fshader-stage=fragment ./test.fs -o ./test_fs.spv
# else 
#   echo "./shaderc not found - Download shaderc and place in project root:"
#   echo "https://github.com/google/shaderc#downloads"
# fi
    