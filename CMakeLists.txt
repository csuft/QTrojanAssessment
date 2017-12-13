CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
PROJECT(QTrojanAssessment C CXX)

################################################################################
# Compiler and linker options
ADD_DEFINITIONS(-Wall -DWIN32_LEAN_AND_MEAN -DUNICODE)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON) 
SET(CMAKE_CXX_STANDARD 11) 

################################################################################
# Sources and libraries
FILE(GLOB CHARTDIRECTOR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/ChartDirector/*")
FILE(GLOB MANOMETER "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/Manometer/*")
FILE(GLOB BUSINESSLAYER "${CMAKE_CURRENT_SOURCE_DIR}/base/BusinessLayer/*")
FILE(GLOB CUSTOMCONTROL "${CMAKE_CURRENT_SOURCE_DIR}/base/CustomControl/*")
FILE(GLOB ABOUTDIALOG "${CMAKE_CURRENT_SOURCE_DIR}/forms/AboutDialog/*")
FILE(GLOB ASSESSMENTTAB "${CMAKE_CURRENT_SOURCE_DIR}/forms/AssessmentTab/*")
FILE(GLOB CACHETAB "${CMAKE_CURRENT_SOURCE_DIR}/forms/CacheTab/*")
FILE(GLOB FILEMONITORTAB "${CMAKE_CURRENT_SOURCE_DIR}/forms/FileMonitorTab/*")
FILE(GLOB IETAB "${CMAKE_CURRENT_SOURCE_DIR}/forms/IETab/*")
FILE(GLOB MAINFORM "${CMAKE_CURRENT_SOURCE_DIR}/forms/MainForm/*")
FILE(GLOB MEMORYTAB "${CMAKE_CURRENT_SOURCE_DIR}/forms/MemoryTab/*")
FILE(GLOB NETWORKTAB "${CMAKE_CURRENT_SOURCE_DIR}/forms/NetworkTab/*")
FILE(GLOB PROCESSTAB "${CMAKE_CURRENT_SOURCE_DIR}/forms/ProcessTab/*")
FILE(GLOB REGISTRYTAB "${CMAKE_CURRENT_SOURCE_DIR}/forms/RegistryTab/*")
FILE(GLOB TITLEWIDGET "${CMAKE_CURRENT_SOURCE_DIR}/forms/TitleWidget/*") 
 
SET(RESOURCES 
  ${CMAKE_CURRENT_SOURCE_DIR}/resource/images/app.rc
  ${CMAKE_CURRENT_SOURCE_DIR}/resource/trojanassessment.qrc) 


FIND_PACKAGE(Qt5 COMPONENTS Core Widgets Xml Gui REQUIRED) 
qt5_wrap_ui(UI_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/resource/cacheentrydetail.ui)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/ChartDirector/lib/)
################################################################################
# Compile target
ADD_EXECUTABLE ( ${PROJECT_NAME} 
				${CHARTDIRECTOR} 
				${MANOMETER} 
				${BUSINESSLAYER}
				${CUSTOMCONTROL}
				${RESOURCES}
				${UI_HEADERS}
				${ABOUTDIALOG}
				${ASSESSMENTTAB} 
				${CACHETAB}
				${FILEMONITORTAB}
				${IETAB}
				${MAINFORM}
				${MEMORYTAB}
				${NETWORKTAB}
				${PROCESSTAB}
				${REGISTRYTAB}
				${TITLEWIDGET}
				${CMAKE_CURRENT_SOURCE_DIR}/base/main.cpp)
# https://www.kdab.com/using-cmake-with-qt-5/
qt5_use_modules(${PROJECT_NAME} Core Widgets Gui Xml) 
TARGET_LINK_LIBRARIES(${PROJECT_NAME} chartdir51.lib)