#pragma once

#include "ofMain.h"

class ofxWinTouchEx
{
public:
	ofxWinTouchEx();
	~ofxWinTouchEx();

	void setup();

	void OnTranslate(GESTUREINFO gestureInfo);
	void OnScale(GESTUREINFO gestureInfo);
	void OnRotate(GESTUREINFO gestureInfo);

	// translate
	ofVec2f startPoint;
	// scale
	UINT64	ullArguments;
	ofVec3f scaleInfo;

	// event
	ofEvent<ofVec2f> eventPan;
	ofEvent<ofVec3f> eventZoom;
	ofEvent<float>	eventRotate;

private:

	HWND hWnd;
};

