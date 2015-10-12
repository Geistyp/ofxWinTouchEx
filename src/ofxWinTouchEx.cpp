#include "ofxWinTouchEx.h"

ofxWinTouchEx* winTouchPtr = NULL;

//------And the subclass Proc that now catches the WM_TOUCH and WM_GESTURE messages: ------------
LRESULT CALLBACK windowProcSubclass(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch (message)
	{
	case WM_POINTERDOWN:
		//printf("CATCH A wm_pointer!!\n");
		break;
	case WM_TOUCH:
		//printf("CATCH A WM_TOUCH!!\n");
		break;
	case WM_GESTURENOTIFY:
		//printf("WM_GESTURENOTIFY!!\n");
		break;
	case WM_GESTURE:
	{
		//printf("CATCH A WM_GESTURE!!\n");
		GESTUREINFO gi;

		ZeroMemory(&gi, sizeof(GESTUREINFO));

		gi.cbSize = sizeof(GESTUREINFO);

		BOOL bResult = GetGestureInfo((HGESTUREINFO)lParam, &gi);
		BOOL bHandled = FALSE;

		if (bResult)
		{
			switch (gi.dwID)
			{
			case GID_ZOOM:
				winTouchPtr->OnScale(gi);
				bHandled = TRUE;
				break;
			case GID_PAN:
				winTouchPtr->OnTranslate(gi);
				bHandled = TRUE;
				break;
			case GID_ROTATE:
				winTouchPtr->OnRotate(gi);
				bHandled = TRUE;
				break;
			case GID_TWOFINGERTAP:
				winTouchPtr->OnSingleTap(gi);
				bHandled = TRUE;
				break;
			case GID_PRESSANDTAP:
				winTouchPtr->OnSecondaryTap(gi);
				bHandled = TRUE;
				break;
			default:
				// A gesture was not recognized
				break;
			}
		}
		else {
			DWORD dwErr = GetLastError();
			if (dwErr > 0) {
				//MessageBoxW(hWnd, L"Error!", L"Could not retrieve a GESTUREINFO structure.", MB_OK);
			}
		}
		if (bHandled) {
			return 0;
		}
		else {
			return DefSubclassProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	default:
		return DefSubclassProc(hWnd, message, wParam, lParam);
	}
	return DefSubclassProc(hWnd, message, wParam, lParam);
}

ofxWinTouchEx::ofxWinTouchEx()
{
}


ofxWinTouchEx::~ofxWinTouchEx()
{
}

void ofxWinTouchEx::setup()
{
	hWnd = ofGetWin32Window();

	// Unregister from receiving WM_TOUCH messages as WM_TOUCH and WM_GESTURE are
	// mutually exclusvie
	UnregisterTouchWindow(hWnd);

	// WM_GESTURE configuration
	DWORD panWant = GC_PAN
		| GC_PAN_WITH_SINGLE_FINGER_VERTICALLY
		| GC_PAN_WITH_SINGLE_FINGER_HORIZONTALLY
		| GC_PAN_WITH_INERTIA;
	GESTURECONFIG gestureConfig[] =
	{
		{ GID_PAN, panWant, GC_PAN_WITH_GUTTER },
		{ GID_ZOOM, GC_ZOOM, 0 },
		{ GID_ROTATE, GC_ROTATE, 0 },
		{ GID_TWOFINGERTAP, GC_TWOFINGERTAP, 0 },
		{ GID_PRESSANDTAP, GC_PRESSANDTAP, 0 }
	};
	SetGestureConfig(hWnd, 0, 5, gestureConfig, sizeof(GESTURECONFIG));

	//----SUBCLASS THE WINDOW
	UINT_PTR uIdSubclass;
	DWORD_PTR dwRefData;

	bool resultsc = SetWindowSubclass(
		ofGetWin32Window(),
		windowProcSubclass,
		uIdSubclass,
		dwRefData
		);
	//if (resultsc) cout << "Window Subclassed with success\n";

	winTouchPtr = this;
}

void ofxWinTouchEx::OnTranslate(GESTUREINFO gestureInfo)
{
	POINT p;

	switch (gestureInfo.dwFlags)
	{
	case GF_BEGIN:
		p.x = gestureInfo.ptsLocation.x;
		p.y = gestureInfo.ptsLocation.y;
		ScreenToClient(hWnd, &p);

		startPoint.x = (WORD)p.x;
		startPoint.y = (WORD)p.y;

		break;
	default:
		p.x = gestureInfo.ptsLocation.x;
		p.y = gestureInfo.ptsLocation.y;
		ScreenToClient(hWnd, &p);

		startPoint.x = (WORD)p.x;
		startPoint.y = (WORD)p.y;

		ofNotifyEvent(eventPan, startPoint);

		break;
	}
}

void ofxWinTouchEx::OnScale(GESTUREINFO gestureInfo)
{
	POINT p;

	switch (gestureInfo.dwFlags)
	{
	case GF_BEGIN:
		p.x = gestureInfo.ptsLocation.x;
		p.y = gestureInfo.ptsLocation.y;
		ScreenToClient(hWnd, &p);

		scaleInfo.x = (WORD)p.x;
		scaleInfo.y = (WORD)p.y;
		ullArguments = gestureInfo.ullArguments;

		break;
	default:
		p.x = gestureInfo.ptsLocation.x;
		p.y = gestureInfo.ptsLocation.y;
		ScreenToClient(hWnd, &p);

		scaleInfo.z = (FLOAT)gestureInfo.ullArguments / (FLOAT)ullArguments;
		
		scaleInfo.x = (WORD)p.x;
		scaleInfo.y = (WORD)p.y;

		ofNotifyEvent(eventZoom, scaleInfo);

		break;
	}
}

void ofxWinTouchEx::OnRotate(GESTUREINFO gestureInfo)
{
	POINT p;

	switch (gestureInfo.dwFlags)
	{
	case GF_BEGIN:
		p.x = gestureInfo.ptsLocation.x;
		p.y = gestureInfo.ptsLocation.y;
		ScreenToClient(hWnd, &p);

		//ullArguments = gestureInfo.ullArguments;

		break;
	default:
		p.x = gestureInfo.ptsLocation.x;
		p.y = gestureInfo.ptsLocation.y;
		ScreenToClient(hWnd, &p);

		// convert radian to degrees
		float angle = 180.0f*(FLOAT)GID_ROTATE_ANGLE_FROM_ARGUMENT(LOWORD(gestureInfo.ullArguments)) / PI;

		ofNotifyEvent(eventRotate, angle);

		break;
	}
}

void ofxWinTouchEx::OnSingleTap(GESTUREINFO gestureInfo)
{
	ofNotifyEvent(eventSingleTap);
}

void ofxWinTouchEx::OnSecondaryTap(GESTUREINFO gestureInfo)
{
	ofNotifyEvent(eventSecondaryTap);
}
