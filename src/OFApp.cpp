

// Own
#include <OFApp.hpp>


void OFApp::draw()
{
    double dTime = ofGetElapsedTimef() * 0.5;
    if (dTime > 80.0) {
        keyReleased('c');
        ofExit();
    }
    _fbo.begin();

	_shader.begin();
    {
        _shader.setUniform2f("u_resolution", _iWidth, _iHeight);
        _shader.setUniform1f("u_time", dTime);
	    ofDrawRectangle(0, 0, _iWidth, _iHeight);
    }
	_shader.end();

    ofSetColor(255, 255, 255);

    if (_bDebug)
    {
        std::stringstream ss;
        ss << "video queue size: " << _vidRecorder.getVideoQueueSize() << std::endl
        << "u_time: " << dTime << std::endl
        << "FPS: " << ofGetFrameRate() << std::endl
        << (_bRecording?"pause":"start") << " recording: r" << std::endl
        << (_bRecording?"close current video file: c":"") << std::endl;

        ofSetColor(0,0,0,100);
        ofDrawRectangle(0, 0, 260, 75);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(ss.str(),15,15);

        if (_bRecording)
        {
            ofSetColor(255, 0, 0);
            ofDrawCircle(_iWidth - 20, 20, 5);
        }
    }

    _fbo.end();

    if (_bRecording)
    {
        ofPixels pixels;
        _fbo.readToPixels(pixels);
        _vidRecorder.addFrame(pixels);
    }

    _fbo.draw(0, 0);
}

void OFApp::setup()
{
    _bDebug = false;
    // int sampleRate = 44100;
    // int channels = 2;

    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(true);
    // vidRecorder.setFfmpegLocation(ofFilePath::getAbsolutePath("ffmpeg")); // use this is you have ffmpeg installed in your data folder

    // override the default codecs if you like
    // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
    // vidRecorder.setVideoCodec("mpeg4");
    _vidRecorder.setVideoCodec("prores");
    _vidRecorder.setVideoBitrate("2000k");
    // vidRecorder.setVideoBitrate("800k");
    // vidRecorder.setPixelFormat("rgb24");
    // vidRecorder.setAudioCodec("mp3");
    // vidRecorder.setAudioBitrate("192k");
    _vidRecorder.setup("output.mov", _iWidth, _iHeight, 30);
    // vidRecorder.setup("output.mov", ofGetWidth(), ofGetHeight(), 30);
    _fbo.allocate(_iWidth, _iHeight, GL_RGB);

    ofAddListener(_vidRecorder.outputFileCompleteEvent, this, &OFApp::recordingComplete);

    _bRecording = false;

	if (ofIsGLProgrammableRenderer())
    {
        std::cerr << "ERROR: No se ha podido cargar el shader." << std::endl;
	}
    else
    {
		_shader.load("../data/shaders/shader");
	}
    keyReleased('r');
}

void OFApp::update()
{
}

void OFApp::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args)
{
    std::cout << "The recoded video file is now complete." << std::endl;
}

void OFApp::dragEvent(ofDragInfo dragInfo)
{
}

void OFApp::gotMessage(ofMessage msg)
{
}

void OFApp::keyPressed(int key)
{
}

void OFApp::keyReleased(int key)
{
    if (key == 'r')
    {
        _bRecording = !_bRecording;

        if (_bRecording && !_vidRecorder.isRecording())
        {
            _vidRecorder.start();
            std::cout << "===> Inicia la grabación" << std::endl;
        }
    }
    if (key == 'c')
    {
        if (_bRecording)
        {
            _bRecording = false;
            _vidRecorder.close();
        }
    }
}

void OFApp::mouseDragged(int x, int y, int button)
{
}

void OFApp::mouseEntered(int x, int y)
{
}

void OFApp::mouseExited(int x, int y)
{
}

void OFApp::mouseMoved(int x, int y)
{
}

void OFApp::mousePressed(int x, int y, int button)
{
}

void OFApp::mouseReleased(int x, int y, int button)
{
}

void OFApp::windowResized(int w, int h)
{
}

void OFApp::exit()
{
    ofRemoveListener(_vidRecorder.outputFileCompleteEvent, this, &OFApp::recordingComplete);
    _vidRecorder.close();
}
