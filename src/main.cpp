

// Own
#include <OFApp.hpp>

int main()
{
    // 4k
    // int width = 3840;
    // int height = 2160;
    // full-hd
    // int width = 1920;
    // int height = 1080;
    int iWidth = 1080;
    int iHeight = 1920;

    ofSetupOpenGL(iWidth, iHeight, OF_WINDOW);
    ofRunApp(new OFApp(iWidth, iHeight));
}
