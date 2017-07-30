cmake_minimum_required(VERSION 3.6)
project(moonlanding)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    geometries/cube.cpp
    geometries/cube.h
    geometries/parametric.cpp
    geometries/parametric.h
    mesh/bbox.cpp
    mesh/bbox.h
    mesh/geometrybuffers.cpp
    mesh/geometrybuffers.h
    mesh/indexbuffer.cpp
    mesh/indexbuffer.h
    mesh/mesh.cpp
    mesh/mesh.h
    mesh/objloader.cpp
    mesh/objloader.h
    mesh/vertexbuffer.h
    appwindow.cpp
    appwindow.h
    camera.cpp
    camera.h
    cubemap.cpp
    cubemap.h
    imagedisplaybutton.cpp
    imagedisplaybutton.h
    imagedisplaydialog.cpp
    imagedisplaydialog.h
    main.cpp
    material.cpp
    material.h
    node.cpp
    node.h
    nodenavigator.cpp
    nodenavigator.h
    rtrglwidget.cpp
    rtrglwidget.h
    scene.cpp
    scene.h)

add_executable(moonlanding ${SOURCE_FILES})