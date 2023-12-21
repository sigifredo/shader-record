
find_package(PkgConfig)

pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.4 gstreamer-sdp-1.0>=1.4 gstreamer-video-1.0>=1.4 gstreamer-app-1.0>=1.4)

set (OF_ROOT /opt/software/of)

set (OF_INCLUDES
/usr/include/cairo/
${OF_ROOT}/libs/openFrameworks/
${OF_ROOT}/libs/openFrameworks/utils/
${OF_ROOT}/libs/tess2/include/
${OF_ROOT}/libs/utf8/include/
${OF_ROOT}/libs/openFrameworks/events/
${OF_ROOT}/libs/glm/include/
${OF_ROOT}/libs/json/include/
${OF_ROOT}/libs/openFrameworks/types/
${OF_ROOT}/libs/openFrameworks/math/
${OF_ROOT}/libs/openFrameworks/graphics/
${OF_ROOT}/libs/openFrameworks/communication/
${OF_ROOT}/libs/openFrameworks/gl/
${OF_ROOT}/libs/openFrameworks/app/
${OF_ROOT}/libs/openFrameworks/3d/
${OF_ROOT}/libs/openFrameworks/sound/
${OF_ROOT}/libs/kiss/include/
${OF_ROOT}/libs/openFrameworks/video/
)

set (OF_LIBRARIES
${OF_ROOT}/libs/openFrameworksCompiled/lib/linux64/libopenFrameworks.a
${OF_ROOT}/libs/kiss/lib/linux64/libkiss.a
${OF_ROOT}/libs/tess2/lib/linux64/libtess2.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoCrypto.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoData.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoEncodings.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoFoundation.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoJSON.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoJWT.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoNet.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoNetSSL.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoRedis.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoUtil.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoXML.a
${OF_ROOT}/addons/ofxPoco/libs/poco/lib/linux64/libPocoZip.a
GLEW
GL
X11
openal
mpg123
glfw
curl
freeimage
uriparser
sndfile
freetype
fontconfig
udev
PocoActiveRecord
PocoCrypto
PocoData
PocoDataMySQL
PocoDataODBC
PocoDataPostgreSQL
PocoDataSQLite
PocoEncodings
PocoFoundation
PocoJSON
PocoJWT
PocoMongoDB
PocoNet
PocoNetSSL
PocoRedis
PocoUtil
PocoXML
PocoZip
rtaudio
${GST_LIBRARIES}
)

include_directories(${OF_INCLUDES} ${GST_INCLUDE_DIRS})
add_definitions(${GST_CFLAGS})

# find_package(Qt6 REQUIRED COMPONENTS Core)
# qt_standard_project_setup()

# set(CMAKE_INCLUDE_CURRENT_DIR ON)

# if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
#     set(RDEPS pthread usb-1.0)
# else()
#     set(RDEPS pthread usb-1.0 libwiringPi.so)
# endif()
