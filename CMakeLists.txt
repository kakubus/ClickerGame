cmake_minimum_required(VERSION 3.14)

project(cmakeTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

#  !! Dodatkowe paczki "importy" z QML

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2)


# -----------------------------

set(PROJECT_SOURCES
        main.cpp
        clickergame.cpp
        ranking.cpp
        qml.qrc
)

set(PROJECT_HEADERS #Zmodyfikowane, dodano naglowki do dolaczenia
        clickergame.h
        ranking.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(cmakeTest
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET cmakeTest APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(cmakeTest SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(cmakeTest
          ${PROJECT_SOURCES}
          ${PROJECT_HEADERS} #Zmodyfikowane, naglowki sie wczytuja
        )
    endif()
endif()

target_compile_definitions(cmakeTest
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(cmakeTest
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

#  !! Tutaj tez dodatkowe wpisy:

target_link_libraries(cmakeTest PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2)

# -----------------------------
set_target_properties(cmakeTest PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(cmakeTest)
    qt_finalize_executable(cmakeTest)
endif()
