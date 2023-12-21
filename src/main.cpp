

// Own
#include <OFApp.hpp>

int main()
{
    int width = 3840;
    int height = 2160;
    // int width = 1920;
    // int height = 1080;

    ofSetupOpenGL(width, height, OF_WINDOW);
    ofRunApp(new OFApp(width, height));
}
