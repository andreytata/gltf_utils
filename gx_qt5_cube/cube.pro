QT += core gui widgets
TARGET = gx_qt5_cube         # TARGET  = ../bin/gx_qt5_cube
TEMPLATE = app
CONFIG += c++11              #CONFIG += console
CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp
SOURCES += mainwidget.cpp
SOURCES += geometryengine.cpp

HEADERS += mainwidget.h
HEADERS += geometryengine.h

RESOURCES +=  \
    shaders.qrc \
    textures.qrc

 #<BUILTIN> RiggedFigure            = C:/work/gen/py_gen_test/RiggedFigure.gltf
 #<BUILTIN> Nikita = D:/AUTODESK_GAME_EXPORT/fbx2gltf2.py/nikita.gltf
 #<BUILTIN> Renata = D:/GAME_EXPORT/Renata/Ren.gltf
#<BUILTIN> Slava_Model_With_Bones  = C:/work/EXP61/devicea/gx_fbx_test/Slava_Model_With_Bones.gltf
#<BUILTIN> Cube_01                 = C:/work/EXP61/devicea/gx_fbx_test/Cube_01.gltf
 #<BUILTIN> cube0                   = C:/work/EXP61/devicea/gx_fbx_test/cube0.gltf
 #<BUILTIN> Slava_Rig_01            = C:/work/EXP61/devicea/gx_fbx_test/Slava_Rig_01.gltf
 #<BUILTIN> Slava_Rig_2014_2015_NEW = C:/work/EXP61/devicea/gx_fbx_test/Slava_Rig_2014_2015_NEW.gltf
 #<BUILTIN> Slava_RIG_02            = D:/BLENDER_GAME_EXPORT/Slava_RIG_02.gltf
#<BUILTIN> Nikita                  = C:/work/EXP61/devicea/gx_fbx_test/Nikita.gltf
 #<BUILTIN> BoxTextured             = C:/WORK/EXP61/devicea/gx_gltf_test/BoxTextured.gltf


#HOWTO: PRINT SOME QMAKE VARIABLES
#  message("(==< gx_qt5_cube.pro >==)")
#  message($$sprintf(" QT = [ %1 ]", $$QT))
#  message($$sprintf(" CONFIG = [ %1 ]", $$CONFIG))
#  message($$sprintf(" MOC_DIR = [ %1 ]", $$MOC_DIR))
#  message($$sprintf(" PWD = [ %1 ]", $$PWD))
#  message($$sprintf(" OUT_PWD = [ %1 ]", $$OUT_PWD))

#HOWTO: QMAKE RELEASE/DEBUG Conditional
#  CONFIG(release, debug|release):message(Release build!) #will print
#  CONFIG(debug, debug|release):message(Debug build!)     #no print

#HOWTO: USE PYTHON FROM QMAKE, ON PRO-file CHANGED
#  py_gen_path = $$sprintf("%1/../py_gen_util/gx_pre_qmake.py",$$PWD)
#  message($$sprintf("( py_gen_path = [ %1 ]", $$py_gen_path))
#  length = $$system(python $$py_gen_path $$PWD $$CONFIG)
#  message($$sprintf("!!! gx_pre_qmake.py => %1", $$length))

#INCLUDE PYTHON_GENERATED_SOURCES & PYTHON_GENERATED_HEADERS
  include(cube.pro.builtins.pri)
  message($$sprintf("( SOURCES = [ %1 ]", $$SOURCES))
  message($$sprintf("( HEADERS = [ %1 ]", $$HEADERS))
