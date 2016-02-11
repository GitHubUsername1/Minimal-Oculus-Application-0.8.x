This guide is an updated version of this https://github.com/dleen/Minimal-Oculus-Application-0.4.x/tree/master/MinOc
I have no relation to the original author

INTRODUCTION

This tutorial will walk you through creating a simple console application that will read out some values from the Oculus Rift DK2 using Visual Studio 2015 Community and Oculus Rift 0.8 SDK

PROJECT CREATION

Click File -> New -> New Project. In the pop-up window choose Win32 Console Application.

Give the project a name, like MinimalOculus. Then pressOK.

In the Application Wizard popup, click on Application Settings. Under Application Type, choose Console Application. Under Additional Settings, choose Empty Project. Click Finish.

In the Solution Explorer, right-click on the Source Files folder and choose Add" -> "New Item. In the pop-up window click on C++ File (.cpp), give it a name like Main.cpp, then click Add. Copy and paste the code from Main.cpp in github to your own Main.cpp

PROJECT CONFIGURATION

You need to tell visual studio where to find the header and library files needed in order to use the oculus rift functions in your code.

Click on Project from the top menu or by right clicking your project in solution explorer, select Properties, expand Configuration Properties, in the menu's that appear find the C/C++ menu item, expand it, then find General, expand that. In the Additional Include Directories add:

	C:\<wherever you downloaded the 0.8 sdk to>\OculusSDK\LibOVRKernel\Src
	C:\<wherever you downloaded the 0.8 sdk to>\OculusSDK\LibOVR\Include

Find the  VC++ Directories menu item, expand it, then in Library Directories add:

	C:\<wherever you downloaded the 0.8 sdk to>\OculusSDK\LibOVR\Lib\Windows\Win32\Release\VS2015;$(LibraryPath)
	
Find the Linker menu item, expand it and find the Input sub menu, expand it and in Additional Dependencies add:

	libovr.lib;
	
SOURCE CODE EXPLANATION

The line below will pull in the header file needed to interface with the Oculus Rift SDK:

	#include "OVR.h"
	
We are using the OVR namespace, to make the code more compact:

	using namespace OVR;

This struct will store our head and positional tracking data obtained from the rift:

	typedef struct ovr_6dof
	{
		float yaw, pitch, roll;
		float x, y, z;
	} ovr_6dof;
	
We create our variable of type ovr_6dof and a pointer to point to it:
	
	ovr_6dof oculusData;
	ovr_6dof* output = &oculusData;

We initialize the SDK:
	
	ovrResult result = ovr_Initialize(nullptr);		
	
We then create the HMD:

	result = ovr_Create(&HMD, &luid);

We setup what tracking and positional data we want:
	
		ovr_ConfigureTracking(HMD, ovrTrackingCap_Orientation |		
		ovrTrackingCap_MagYawCorrection |
		ovrTrackingCap_Position, ovrTrackingCap_Orientation);
		
We enter the loop where data is returned to our struct. For more information refer to https://developer.oculus.com/documentation/pcsdk/latest/concepts/dg-sensor/

To exit the loop press q. Doing so calls:

	ovr_Destroy(HMD);	
	ovr_Shutdown();	
	
This free's resources and closes the library before the program exits.

OK. That's it! Now is the time to compile and run the application (Control + F5) and see what happens. If your Oculus Rift developer kit is plugged in, you should start seeing some head and positional tracking data values. 
