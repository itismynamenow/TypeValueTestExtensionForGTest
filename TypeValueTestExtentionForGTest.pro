include(gtest_dependency.pri)

QMAKE_CXXFLAGS += -save-temps

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
    type_value_test.h \
    general_example.h \
    applied_example.h \
    things_to_test.h \
    lazy_example.h

SOURCES += \
        main.cpp
