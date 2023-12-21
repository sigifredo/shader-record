

// Own
#include <OFApp.hpp>


void OFApp::draw()
{
    double u_time = ofGetElapsedTimef() * 0.5;
    if (u_time > 80.0) {
        keyReleased('c');
        ofExit();
    }
    fbo.begin();

	_shader.begin();
    {
        _shader.setUniform2f("u_resolution", _iWidth, _iHeight);
        _shader.setUniform1f("u_time", u_time);
	    ofDrawRectangle(0, 0, _iWidth, _iHeight);
    }
	_shader.end();

    ofSetColor(255, 255, 255);

    if (bDebug)
    {
        stringstream ss;
        ss << "video queue size: " << vidRecorder.getVideoQueueSize() << endl
        << "u_time: " << u_time << endl
        << "FPS: " << ofGetFrameRate() << endl
        << (bRecording?"pause":"start") << " recording: r" << endl
        << (bRecording?"close current video file: c":"") << endl;

        ofSetColor(0,0,0,100);
        ofDrawRectangle(0, 0, 260, 75);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(ss.str(),15,15);

        if (bRecording)
        {
            ofSetColor(255, 0, 0);
            ofDrawCircle(_iWidth - 20, 20, 5);
        }
    }

    fbo.end();

    if (bRecording){
        ofPixels pixels;
        fbo.readToPixels(pixels);
        vidRecorder.addFrame(pixels);
    }

    fbo.draw(0, 0);
}

void OFApp::setup()
{
    bDebug = false;
    // int sampleRate = 44100;
    // int channels = 2;

    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(true);
    // vidRecorder.setFfmpegLocation(ofFilePath::getAbsolutePath("ffmpeg")); // use this is you have ffmpeg installed in your data folder

    // override the default codecs if you like
    // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
    // vidRecorder.setVideoCodec("mpeg4");
    vidRecorder.setVideoCodec("prores");
    vidRecorder.setVideoBitrate("2000k");
    // vidRecorder.setVideoBitrate("800k");
    // vidRecorder.setPixelFormat("rgb24");
    // vidRecorder.setAudioCodec("mp3");
    // vidRecorder.setAudioBitrate("192k");
    vidRecorder.setup("output.mov", _iWidth, _iHeight, 30);
    // vidRecorder.setup("output.mov", ofGetWidth(), ofGetHeight(), 30);
    fbo.allocate(_iWidth, _iHeight, GL_RGB);

    ofAddListener(vidRecorder.outputFileCompleteEvent, this, &OFApp::recordingComplete);

    bRecording = false;

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

void OFApp::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args){
    cout << "The recoded video file is now complete." << endl;
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
        bRecording = !bRecording;

        if (bRecording && !vidRecorder.isRecording())
        {
            vidRecorder.start();
            std::cout << "===> Inicia la grabación" << std::endl;
        }
    }
    if (key == 'c')
    {
        if (bRecording) {
            bRecording = false;
            vidRecorder.close();
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
    ofRemoveListener(vidRecorder.outputFileCompleteEvent, this, &OFApp::recordingComplete);
    vidRecorder.close();
}
