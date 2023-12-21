

// Own
#include <OFApp.hpp>

OFApp::OFApp(const int& iWidth, const int& iHeight)
{
    _iHeight = iHeight;
    _iWidth = iWidth;

    _pFbo = new ofFbo();
    _pShader = new ofShader();
    _pVidRecorder = new ofxVideoRecorder();
}

OFApp::~OFApp()
{
    delete _pFbo;
    delete _pShader;
    delete _pVidRecorder;
}

void OFApp::draw()
{
    double dTime = ofGetElapsedTimef() * 0.5;
    if (dTime > 80.0) {
        keyReleased('c');
        ofExit();
    }
    _pFbo->begin();

	_pShader->begin();
    {
        _pShader->setUniform2f("u_resolution", _iWidth, _iHeight);
        _pShader->setUniform1f("u_time", dTime);
	    ofDrawRectangle(0, 0, _iWidth, _iHeight);
    }
	_pShader->end();

    ofSetColor(255, 255, 255);

    if (_bDebug)
    {
        std::stringstream ss;
        ss << "video queue size: " << _pVidRecorder->getVideoQueueSize() << std::endl
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

    _pFbo->end();

    if (_bRecording)
    {
        ofPixels pixels;
        _pFbo->readToPixels(pixels);
        _pVidRecorder->addFrame(pixels);
    }

    _pFbo->draw(0, 0);
}

void OFApp::exit()
{
    ofRemoveListener(_pVidRecorder->outputFileCompleteEvent, this, &OFApp::recordingComplete);
    _pVidRecorder->close();
}

void OFApp::keyReleased(const int& iKey)
{
    if (iKey == 'r')
    {
        _bRecording = !_bRecording;

        if (_bRecording && !_pVidRecorder->isRecording())
        {
            _pVidRecorder->start();
            std::cout << "===> Inicia la grabación" << std::endl;
        }
    }
    if (iKey == 'c')
    {
        if (_bRecording)
        {
            _bRecording = false;
            _pVidRecorder->close();
        }
    }
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
    _pVidRecorder->setVideoCodec("prores");
    _pVidRecorder->setVideoBitrate("2000k");
    // vidRecorder.setVideoBitrate("800k");
    // vidRecorder.setPixelFormat("rgb24");
    // vidRecorder.setAudioCodec("mp3");
    // vidRecorder.setAudioBitrate("192k");
    _pVidRecorder->setup("output.mov", _iWidth, _iHeight, 30);
    // vidRecorder.setup("output.mov", ofGetWidth(), ofGetHeight(), 30);
    _pFbo->allocate(_iWidth, _iHeight, GL_RGB);

    ofAddListener(_pVidRecorder->outputFileCompleteEvent, this, &OFApp::recordingComplete);

    _bRecording = false;

	if (ofIsGLProgrammableRenderer())
    {
        std::cerr << "ERROR: No se ha podido cargar el shader." << std::endl;
	}
    else
    {
		_pShader->load("../data/shaders/shader");
	}
    keyReleased('r');
}

void OFApp::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args)
{
    std::cout << "The recoded video file is now complete." << std::endl;
}
