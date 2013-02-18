TEMPLATE 	= app
CONFIG 		+= qt
DESTDIR 	= bin
OBJECTS_DIR = .tmp
LIBS 		= -lboost_filesystem -lboost_system -L/usr/lib/graphviz -lgvc -lgraph -lpathplan -lcdt -lgvplugin_dot_layout

HEADERS 	= 	headers/Action.h 		\
				headers/Exceptions.h 	\
				headers/IO.h 			\
				headers/GProcess.h 		\
				headers/GAction.h 		\
				headers/GSort.h 		\
				headers/GVCluster.h 	\
				headers/GVEdge.h 		\
				headers/GVGraph.h 		\
				headers/GVNode.h	 	\
				headers/GVSubGraph.h 	\
				headers/MainWindow.h 	\
				headers/MyArea.h 		\
				headers/PH.h 			\
				headers/PHScene.h		\
				headers/PHIO.h 			\
				headers/Process.h 		\
				headers/Sort.h \
    headers/Area.h \
    headers/TextArea.h \
    headers/TreeArea.h \
    headers/ColorerSequences.h \
    Connection.h \
    src/ui/connectionsettings.h \
    src/ui/ConnectionSettings.h \
    src/ui/ConnectionSettings.h \
    headers/ConnectionSettings.h \
    headers/ArgumentFrame.h \
<<<<<<< HEAD
    headers/FuncFrame.h
=======
    headers/FuncFrame.h \
    headers/FunctionForm.h
>>>>>>> 911acc14f9ffc05faf89444f2247e860eec78d0c
				
INCLUDEPATH = headers headers/axe headers/test

SOURCES			= 	src/gfx/GProcess.cpp	\
					src/gfx/GAction.cpp		\					
					src/gfx/GSort.cpp		\					
					src/gfx/PHScene.cpp		\
					src/gviz/GVGraph.cpp	\
					src/gviz/GVSubGraph.cpp	\
					src/io/IO.cpp			\
					src/io/PHIO.cpp			\
					src/ph/Action.cpp		\
					src/ph/PH.cpp			\					
					src/ph/Process.cpp		\
					src/ph/Sort.cpp			\
					src/ui/MainWindow.cpp 	\
					src/ui/MyArea.cpp \
    src/ui/TextArea.cpp \
    src/ui/TreeArea.cpp \
    src/ui/Area.cpp \
    src/ui/ColorerSequences.cpp \
    src/ui/ConnectionSettings.cpp \
    src/ui/ArgumentFrame.cpp \
<<<<<<< HEAD
    src/ui/FuncFrame.cpp
=======
    src/ui/FuncFrame.cpp \
    src/ui/FunctionForm.cpp
>>>>>>> 911acc14f9ffc05faf89444f2247e860eec78d0c

#So 2013 (needed for Axe)
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -ggdb

test {

	QMAKE_CXXFLAGS += -ggdb
	QT += testlib
	HEADERS +=	headers/test/PHIOTest.h
	SOURCES	+= 	src/test/TestRunner.cpp	\
				src/test/PHIOTest.cpp

} else {

	SOURCES	+= src/Main.cpp

}

FORMS +=
