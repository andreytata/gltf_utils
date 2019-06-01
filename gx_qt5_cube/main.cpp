#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "mainwidget.h"
#endif

// Main
// Create MainWidget "widget";
// Create Scene      "scene";  // dict with named transforms, sceletons, mesh/skin-cloned, etc..
// Use widget.set_scene("scenes/path") Or widget.set_scene(Scene*), as result
// all mesh/skin-shared instances must be inserted to widget geometry-engine.
// Use vizem-records to manipulate scene's uniform variables.

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("cube");
    app.setApplicationVersion("0.1");
#ifndef QT_NO_OPENGL
    MainWidget widget;
    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
