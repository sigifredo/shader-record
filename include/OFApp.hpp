

#ifndef OFAPP_HPP
#define OFAPP_HPP

#include <ofMain.h>
#include <ofxVideoRecorder.hpp>

class OFApp : public ofBaseApp {
public:
    OFApp(const int& iWidth, const int& iHeight): _iWidth(iWidth), _iHeight(iHeight) { }

    void draw();
    void setup();
    void update();
    void exit();

    /* Events */
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseDragged(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void mouseMoved(int x, int y);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);

private:
    ofShader _shader;

    // ofVideoGrabber vidGrabber;
    ofxVideoRecorder vidRecorder;
    ofFbo fbo;
    bool bRecording;
    bool bDebug;
    int _iWidth;
    int _iHeight;

    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);
};

#endif
