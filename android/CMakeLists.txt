cmake_minimum_required(VERSION 3.21.3)

if(ANDROID)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out_a)
    set(CMAKE_SYSTEM_NAME Android)
    set(CMAKE_SYSTEM_VERSION 21)
    set(CMAKE_ANDROID_STL_TYPE gnustl_static)
    set(MODNAME gdmod)

    project(${MODNAME} VERSION 1.0.0 LANGUAGES CXX C)

    add_library(${MODNAME} SHARED
        main.cpp
        gdsymbols.cpp
        networking.cpp

        GameObjectFactory.cpp
        hooks.cpp

        Rainix/LC/main.cpp
        Rainix/LC/cJSON.c

        Rainix/LC/KittyMemory/KittyMemory.cpp
        Rainix/LC/KittyMemory/KittyUtils.cpp
        Rainix/LC/KittyMemory/MemoryBackup.cpp
        Rainix/LC/KittyMemory/MemoryPatch.cpp
    )

    target_include_directories(${MODNAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gd
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cocos2dx
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cocos2dx/platform
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cocos2dx/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cocos2dx/kazmath/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cocos2dx/platform/android
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cocos2dx/platform/third_party/android/prebuit/libcurl/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/extensions
	${CMAKE_CURRENT_SOURCE_DIR}/Rainix/LC
	${CMAKE_CURRENT_SOURCE_DIR}/Rainix/LC/KittyMemory
    )

    target_link_libraries(${MODNAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_ANDROID_ARCH_ABI}/libcocos2dcpp.so)
    target_link_libraries(${MODNAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_ANDROID_ARCH_ABI}/libfmod.so)
    target_link_libraries(${MODNAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_ANDROID_ARCH_ABI}/libeveryplay.so)
    target_link_libraries(${MODNAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_ANDROID_ARCH_ABI}/libdobby.a)
    target_link_libraries(${MODNAME} log)

    install(TARGETS ${MODNAME} LIBRARY)
endif()
