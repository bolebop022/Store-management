cmake_minimum_required(VERSION 3.16)
project(Store VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        store.h store.cpp
        transactions.h transactions.cpp
        customer.h customer.cpp
        product.h
        book.h book.cpp
        magazine.h magazine.cpp
        iproductfactory.h
        bookfactory.h bookfactory.cpp
        magazine.h magazine.cpp
)

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Store APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Store
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(Store
        ${PROJECT_SOURCES}
    )
endif()


target_link_libraries(Store PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
# Windows Deployment (MinGW)
if(WIN32 AND MINGW)
    # Get Qt's MinGW bin path (where windeployqt.exe is)
    get_target_property(QT_QMAKE_EXECUTABLE Qt${QT_VERSION_MAJOR}::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
    set(WINDEPLOYQT_EXECUTABLE "${QT_BIN_DIR}/windeployqt.exe")

    # Run windeployqt after build
    add_custom_command(TARGET Store POST_BUILD
        COMMAND ${WINDEPLOYQT_EXECUTABLE}
                $<TARGET_FILE:Store>
                --verbose 1
                --no-compiler-runtime
                --no-opengl-sw
        COMMENT "Deploying Qt libraries with MinGW..."
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM
    )
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Store)
endif()
