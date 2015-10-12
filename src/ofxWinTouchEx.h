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
	void OnSingleTap(GESTUREINFO gestureInfo);
	void OnSecondaryTap(GESTUREINFO gestureInfo);

	ofVec2f startPoint;
	UINT64	ullArguments;
	ofVec3f scaleInfo;

	// event
	ofEvent<ofVec2f> eventPan;
	ofEvent<ofVec3f> eventZoom;
	ofEvent<float>	eventRotate;
	ofEvent<void>	eventSingleTap;
	ofEvent<void>	eventSecondaryTap;

private:

	HWND hWnd;
};

