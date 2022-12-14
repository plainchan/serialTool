cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR )

project(CuteCom)

set (CuteCom_MAJOR_VERSION 0)
set (CuteCom_MINOR_VERSION 51)
set (CuteCom_PATCH_VERSION 0)
set (CuteCom_VERSION
     ${CuteCom_MAJOR_VERSION}.${CuteCom_MINOR_VERSION}.${CuteCom_PATCH_VERSION})

include(GNUInstallDirs)

configure_file (
  "${PROJECT_SOURCE_DIR}/version.h.in"
  "${PROJECT_SOURCE_DIR}/version.h"
)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find the Qt libraries
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5SerialPort REQUIRED)
find_package(Qt5Network REQUIRED)

qt5_wrap_ui(uiHeaders controlpanel.ui  mainwindow.ui statusbar.ui sessionmanager.ui searchpanel.ui
    macroplugin.ui macrosettings.ui netproxyplugin.ui netproxysettings.ui counterplugin.ui)
set(cutecomSrcs main.cpp mainwindow.cpp controlpanel.cpp  devicecombo.cpp
    serialdevicelistmodel.cpp  settings.cpp statusbar.cpp sessionmanager.cpp
    datadisplay.cpp datahighlighter.cpp searchpanel.cpp timeview.cpp ctrlcharacterspopup.cpp 
    plugin.cpp pluginmanager.cpp macroplugin.cpp macrosettings.cpp netproxyplugin.cpp netproxysettings.cpp
    counterplugin.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# C++14: set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
#add_definitions("-std=c++11")

set(exeType)
set(binInstallDir "${CMAKE_INSTALL_BINDIR}")

if(APPLE)
   set(exeType MACOSX_BUNDLE)
   set(binInstallDir /Applications )
endif(APPLE)

add_executable(cutecom ${exeType} ${cutecomSrcs} ${uiHeaders} resources.qrc)


target_link_libraries(cutecom Qt5::Core Qt5::Gui Qt5::Widgets Qt5::SerialPort Qt5::Network)

if (APPLE)
   set_target_properties(cutecom PROPERTIES OUTPUT_NAME CuteCom)
endif (APPLE)

install(TARGETS cutecom DESTINATION ${binInstallDir} )

if (NOT APPLE)
   install(FILES cutecom.desktop DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
   install(FILES com.gitlab.cutecom.cutecom.appdata.xml DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo)
   install(FILES images/cutecom.svg DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps)
   install(FILES distribution/cutecom.png DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/32x32/apps)
endif()

install(FILES cutecom.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

set (CPACK_PACKAGE_VERSION ${CuteCom_VERSION})
set (CPACK_SOURCE_GENERATOR "TGZ")
set (CPACK_GENERATOR "RPM")
set (CPACK_PACKAGE_NAME "cutecom")
set (CPACK_PACKAGE_RELEASE 1)
set (CPACK_PACKAGE_VENDOR "cyc1insir")
set (CPACK_PACKAGE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")

set (CPACK_RPM_USER_BINARY_SPECFILE "${CMAKE_CURRENT_BINARY_DIR}/cutecom.spec")
set (CPACK_SOURCE_PACKAGE_FILE_NAME 
       "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set (CPACK_SOURCE_IGNORE_FILES
       "${CMAKE_CURRENT_BINARY_DIR};/.git/;~$;${CPACK_SOURCE_IGNORE_FILES}")
include (CPack)

add_custom_target(dist COMMAND git archive --format tar --prefix=cutecom-${CuteCom_VERSION}/ HEAD | gzip > ${CMAKE_CURRENT_BINARY_DIR}/${CPACK_SOURCE_PACKAGE_FILE_NAME}.tgz WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

