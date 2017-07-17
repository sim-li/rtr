# PROJECT FILE FOR RTRAPP

# We want the most current C++ standard.
# i.e. for std::make_unique
CONFIG += c++14

# QT MODULES TO BE USED
QT           += gui widgets

# HEADERS TO BE PROCESSED BY QT
HEADERS      += \
    camera.h \
    appwindow.h \
    material.h \
    node.h \
    rtrglwidget.h \
    scene.h \
    geometries/cube.h \
    geometries/parametric.h \
    mesh/bbox.h \
    mesh/objloader.h \
    mesh/indexbuffer.h \
    mesh/mesh.h \
    mesh/vertexbuffer.h \
    mesh/geometrybuffers.h

# C++ SOURCE FILES TO BE COMPILED AND LINKED TOGETHER
SOURCES      += \
    main.cpp \
    appwindow.cpp \
    camera.cpp \
    material.cpp \
    node.cpp \
    scene.cpp \
    geometries/cube.cpp \
    mesh/bbox.cpp \
    mesh/geometrybuffers.cpp \
    mesh/objloader.cpp \
    mesh/indexbuffer.cpp \
    mesh/mesh.cpp \
    rtrglwidget.cpp \
    geometries/parametric.cpp

# RESOURCE FILES TO BE PROCESSED BY QT
RESOURCES    += \
    assets.qrc

# UI DEFINITION FILES TO BE PROCESSED BY QT (FROM DESIGNER APP)
FORMS        += \
                appwindow.ui

# additional libs needed on Windows
win32: LIBS += -lopengl32

