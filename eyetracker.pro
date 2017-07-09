TEMPLATE = app

QT += qml quick network
CONFIG += c++11

SOURCES += main.cpp \
    messagedialog.cpp \
    streammanager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ios {
    CONFIG -= bitcode
    INCLUDEPATH += "/users/matthewjurewicz/documents/opencv/opencv2.framework/Headers"
    LIBS += \
        -F"/users/matthewjurewicz/documents/opencv"\
        -framework opencv2
    DEFINES += "iosflag=1"
}

android {
    #OpenCV
    INCLUDEPATH += "/users/matthewjurewicz/documents/opencv/android-sdk/sdk/native/jni/include"
    LIBS += \
        -L"/users/matthewjurewicz/documents/opencv/android-sdk/sdk/native/libs/armeabi-v7a"\
        -L"/users/matthewjurewicz/documents/opencv/android-sdk/sdk/native/3rdparty/libs/armeabi-v7a"\
        -libopencv_calib3d\
        -libopencv_core\
        -libopencv_features2d\
        -libopencv_flann\
        -libopencv_highgui\
        -libopencv_imgcodecs\
        -libopencv_imgproc\
        -libopencv_java3\
        -libopencv_ml\
        -libopencv_objdetect\
        -libopencv_photo\
        -libopencv_shape\
        -libopencv_stitching\
        -libopencv_superres\
        -libopencv_video\
        -libopencv_videoio\
        -libopencv_videostab\
        -libllmlmf\
        -liblibjasper\
        -liblibjpeg\
        -liblibpng\
        -liblibtiff\
        -liblibwebp\
        -libtbb\
        -libtegra_hal
    ANDROID_SOURCE_PACKAGE_DIR = "$$_PRO_FILE_PWD_/android/armeabi-v7a"
    DEFINES += "androidflag=1"
}

HEADERS += \
    messagedialog.h \
    streammanager.h
