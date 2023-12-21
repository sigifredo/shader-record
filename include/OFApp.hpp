

#ifndef OFAPP_HPP
#define OFAPP_HPP

#include <ofMain.h>
#include <ofxVideoRecorder.hpp>

class OFApp : public ofBaseApp {
public:
    OFApp(const int& iWidth, const int& iHeight);
    ~OFApp();

    void draw();
    void exit();
    void keyReleased(const int& iKey);
    void setup();

private:
    bool _bDebug;
    bool _bRecording;
    int _iHeight;
    int _iWidth;
    ofFbo * _pFbo;
    ofShader * _pShader;
    ofxVideoRecorder * _pVidRecorder;

    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);
};

#endif
