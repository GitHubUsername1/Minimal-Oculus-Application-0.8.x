#include<OVR.h>
#include<iostream>
#include <conio.h>
#include <Windows.h>

using namespace OVR;
using namespace std;

typedef struct ovr_6dof
{
	float yaw, pitch, roll;
	float x, y, z;
} ovr_6dof;

int main()
{
	ovr_6dof oculusData;
	ovr_6dof* output = &oculusData;

	ovrHmd HMD;
	double HmdFrameTiming;

	ovrResult result = ovr_Initialize(nullptr);		// initializing the rift
	if (!OVR_SUCCESS(result)) return 1;

	ovrGraphicsLuid luid;			// creating the HMD
	result = ovr_Create(&HMD, &luid);
	
	if (!OVR_SUCCESS(result)) return 1;

	if (!HMD) {
		return 1;
	}

	ovr_ConfigureTracking(HMD, ovrTrackingCap_Orientation |		// tracking options
		ovrTrackingCap_MagYawCorrection |
		ovrTrackingCap_Position, ovrTrackingCap_Orientation);

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(h, &bufferInfo);

	while (true)
	{
		HmdFrameTiming = ovr_GetPredictedDisplayTime(HMD, 0);
		ovrTrackingState ts = ovr_GetTrackingState(HMD, ovr_GetTimeInSeconds(), HmdFrameTiming);
		Posef pose = ts.HeadPose.ThePose;

		pose.Rotation.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&output->yaw, &output->pitch, &output->roll);
		output->x = pose.Translation.x;
		output->y = pose.Translation.y;
		output->z = pose.Translation.z;

		// code below is optional, just shows tracking info from the rift
		SetConsoleCursorPosition(h, bufferInfo.dwCursorPosition);
		cout << "yaw: " << RadToDegree(output->yaw) << endl;
		cout << "pitch: " << RadToDegree(output->pitch) << endl;
		cout << "roll: " << RadToDegree(output->roll) << endl<<endl;
		cout << "x: " << RadToDegree(output->x) << endl;
		cout << "y: " << RadToDegree(output->y) << endl;
		cout << "z: " << RadToDegree(output->z) << endl;

		if (_kbhit())	// optional: used to end the application gracefully
		{
			char keyPressed = _getch();
			if (keyPressed == 'q')
				break;			
		}

		Sleep(2);
	}

	ovr_Destroy(HMD);	
	ovr_Shutdown();		
	output = nullptr;

	return 0;
}
