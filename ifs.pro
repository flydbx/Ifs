DESTDIR = ../../lib

TEMPLATE = lib
CONFIG += staticlib c++11
INCLUDEPATH += ..

NAME = ifs

CONFIG(release, debug|release) {
    TARGET = $$NAME
} else {
    TARGET = $${NAME}_d

}

HEADERS += \
  Ifs.h \
  IfsWrlLoader.h \
  IfsWrlSaver.h \
  IfsLoader.h \
  IfsSaver.h \
  tokenizer.h

SOURCES += \
  Ifs.cpp \
  IfsWrlLoader.cpp \
  IfsWrlSaver.cpp \
  IfsLoader.cpp \
  IfsSaver.cpp \
  tokenizer.cpp


