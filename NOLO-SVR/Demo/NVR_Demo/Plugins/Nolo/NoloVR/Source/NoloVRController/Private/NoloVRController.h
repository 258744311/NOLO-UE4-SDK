// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "INoloVRControllerPlugin.h"
#include "IInputDevice.h"
#include "XRMotionControllerBase.h"
#include "IHapticDevice.h"
#include "Engine.h"
#include "../../NoloVR/Private/NoloVRHMD.h"
#include "NoloVRControllerLibrary.h"
#define CONTROLLERS_PER_PLAYER	2             //
//#define MAX_NUM_PSEUDO_INPUT_CONTROLLERS    4 // We dont realy have any input controllers, this is a sham! :P
//#define NUM_PSEUDO_INPUT_BUTTONS			6 // I've only used the one button but w/evs
#define MaxTrackedDeviceCount  2
struct FNoloKey
{
	//Left Controller
	static const FKey Nolo_Left_TouchPadPress;
	static const FKey Nolo_Left_Trigger;
	static const FKey Nolo_Left_Menu;
	static const FKey Nolo_Left_System;
	static const FKey Nolo_Left_Grip;
	static const FKey Nolo_Left_TouchPadTouch;
	static const FKey Nolo_Left_TouchPadUp;
	static const FKey Nolo_Left_TouchPadDown;
	static const FKey Nolo_Left_TouchPadLeft;
	static const FKey Nolo_Left_TouchPadRight;

	//Right Controller
	static const FKey Nolo_Right_TouchPadPress;
	static const FKey Nolo_Right_Trigger;
	static const FKey Nolo_Right_Menu;
	static const FKey Nolo_Right_System;
	static const FKey Nolo_Right_Grip;
	static const FKey Nolo_Right_TouchPadTouch;
	static const FKey Nolo_Right_TouchPadUp;
	static const FKey Nolo_Right_TouchPadDown;
	static const FKey Nolo_Right_TouchPadLeft;
	static const FKey Nolo_Right_TouchPadRight;
};

struct FNoloAxis
{
	//Left Controller
	static const FKey Nolo_Left_Thumbstick_X;
	static const FKey Nolo_Left_Thumbstick_Y;
	//Right Controller
	static const FKey Nolo_Right_Thumbstick_X;
	static const FKey Nolo_Right_Thumbstick_Y;
};

struct FNoloKeyNames
{
	typedef FName Type;
	//Left Controller
	static const FName Nolo_Left_TouchPadPress;
	static const FName Nolo_Left_Trigger;
	static const FName Nolo_Left_Menu;
	static const FName Nolo_Left_System;
	static const FName Nolo_Left_Grip;
	static const FName Nolo_Left_TouchPadTouch;
	static const FName Nolo_Left_Thumbstick_X;
	static const FName Nolo_Left_Thumbstick_Y;
	static const FName Nolo_Left_TouchPadUp;
	static const FName Nolo_Left_TouchPadDown;
	static const FName Nolo_Left_TouchPadLeft;
	static const FName Nolo_Left_TouchPadRight;
	//Right Controller
	static const FName Nolo_Right_TouchPadPress;
	static const FName Nolo_Right_Trigger;
	static const FName Nolo_Right_Menu;
	static const FName Nolo_Right_System;
	static const FName Nolo_Right_Grip;
	static const FName Nolo_Right_TouchPadTouch;
	static const FName Nolo_Right_Thumbstick_X;
	static const FName Nolo_Right_Thumbstick_Y;
	static const FName Nolo_Right_TouchPadUp;
	static const FName Nolo_Right_TouchPadDown;
	static const FName Nolo_Right_TouchPadLeft;
	static const FName Nolo_Right_TouchPadRight;
};
/**
* Digital button state
*/
struct FNoloButtonState
{
	/** The Unreal button this maps to.  Different depending on whether this is the Left or Right hand controller */
	FName Key;

	/** Whether we're pressed or not.  While pressed, we will generate repeat presses on a timer */
	bool bIsPressed;

	/** Next time a repeat event should be generated for each button */
	double NextRepeatTime;


	/** Default constructor that just sets sensible defaults */
	FNoloButtonState()
		: Key(NAME_None),
		bIsPressed(false),
		NextRepeatTime(0.0)
	{
	}
};
/**
* Buttons on the NOLOVR controller
*/
enum class ENoloVRControllerButton
{
	TouchPadPress,
	Trigger,
	Menu,
	System,
	Grip,
	TouchPadTouch,
	TouchPadUp,
	TouchPadDown,
	TouchPadLeft,
	TouchPadRight,

	/** Max number of controller buttons.  Must be < 256 */
	TotalButtonCount

};

/**
* Input state for an Nolo motion controller
*/
struct FNoloControllerState
{
	/** Thumbstick */
	FVector2D ThumbstickAxes;

	FNoloButtonState Buttons[(int32)ENoloVRControllerButton::TotalButtonCount];

	FNoloControllerState(const EControllerHand Hand) :ThumbstickAxes(FVector2D::ZeroVector) {
		for (FNoloButtonState& Button : Buttons)
		{
			Button.bIsPressed = false;
			Button.NextRepeatTime = 0.0;
		}
		Buttons[(int32)ENoloVRControllerButton::TouchPadPress].Key = (Hand == EControllerHand::Left) ? FNoloKeyNames::Nolo_Left_TouchPadPress : FNoloKeyNames::Nolo_Right_TouchPadPress;
		Buttons[(int32)ENoloVRControllerButton::Trigger].Key = (Hand == EControllerHand::Left) ? FNoloKeyNames::Nolo_Left_Trigger : FNoloKeyNames::Nolo_Right_Trigger;
		Buttons[(int32)ENoloVRControllerButton::Menu].Key = (Hand == EControllerHand::Left) ? FNoloKeyNames::Nolo_Left_Menu : FNoloKeyNames::Nolo_Right_Menu;
		Buttons[(int32)ENoloVRControllerButton::System].Key = (Hand == EControllerHand::Left) ? FNoloKeyNames::Nolo_Left_System : FNoloKeyNames::Nolo_Right_System;
		Buttons[(int32)ENoloVRControllerButton::Grip].Key = (Hand == EControllerHand::Left) ? FNoloKeyNames::Nolo_Left_Grip : FNoloKeyNames::Nolo_Right_Grip;
		Buttons[(int32)ENoloVRControllerButton::TouchPadTouch].Key = (Hand == EControllerHand::Left) ? FNoloKeyNames::Nolo_Left_TouchPadTouch : FNoloKeyNames::Nolo_Right_TouchPadTouch;
		Buttons[(int32)ENoloVRControllerButton::TouchPadUp].Key = (Hand == EControllerHand::Left) ? FNoloKeyNames::Nolo_Left_TouchPadUp : FNoloKeyNames::Nolo_Right_TouchPadUp;
		Buttons[(int32)ENoloVRControllerButton::TouchPadDown].Key = (Hand == EControllerHand::Left) ? FNoloKeyNames::Nolo_Left_TouchPadDown : FNoloKeyNames::Nolo_Right_TouchPadDown;
		Buttons[(int32)ENoloVRControllerButton::TouchPadLeft].Key = (Hand == EControllerHand::Left) ? FNoloKeyNames::Nolo_Left_TouchPadLeft : FNoloKeyNames::Nolo_Right_TouchPadLeft;
		Buttons[(int32)ENoloVRControllerButton::TouchPadRight].Key = (Hand == EControllerHand::Left) ? FNoloKeyNames::Nolo_Left_TouchPadRight : FNoloKeyNames::Nolo_Right_TouchPadRight;
	}

	/** Default constructor does nothing.  Don't use it.  This only exists because we cannot initialize an array of objects with no default constructor on non-C++ 11 compliant compilers (VS 2013) */
	FNoloControllerState()
	{
	}
};

/**
* A pair of wireless motion controllers, one for either hand
*/
struct FNoloControllerPair
{
	/** The Unreal controller index assigned to this pair */
	int32 UnrealControllerIndex;
	/** Current device state for either hand */
	FNoloControllerState ControllerStates[2];

	/** Default constructor that sets up sensible defaults */
	FNoloControllerPair() :UnrealControllerIndex(INDEX_NONE), ControllerStates()
	{
		ControllerStates[(int32)EControllerHand::Left] = FNoloControllerState(EControllerHand::Left);
		ControllerStates[(int32)EControllerHand::Right] = FNoloControllerState(EControllerHand::Right);
	}
};

class FNoloVRController : public IInputDevice, public FXRMotionControllerBase, public IHapticDevice
{
	FNoloVRHMD* GetNoloVRHMD() const
	{
		FNoloVRHMD* noloVR;
		TArray<INoloVRDevice*> NoloVRDevices = IModularFeatures::Get().GetModularFeatureImplementations<INoloVRDevice>(INoloVRDevice::GetModularFeatureName());

		for (auto NoloVRDevice : NoloVRDevices)
		{
			//UE_LOG(LogTemp, Log, TEXT("==============NoloVRDevice===%d=============\n"), NoloVRDevice->getFlag());
			if (NoloVRDevice != nullptr)
			{
				noloVR = static_cast<FNoloVRHMD*>(NoloVRDevice);
				if (noloVR != nullptr) {
					//UE_LOG(LogTemp, Log, TEXT("============== noloVR->test===%d=====%d=====%d=====%x=\n"), noloVR->test(), noloVR->test2(), noloVR->test3(),noloVR);
					return noloVR;
				}
			}
		}
		return nullptr;
	}

public:
	FNoloVRController(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);
	virtual ~FNoloVRController();

	void PreInit();

	void SetTouchDPadMapping(ENoloVRTouchDPadMapping NewMapping);

	static ENoloVRTouchDPadMapping DefaultDPadMapping;
public:

	// 通过 IInputDevice 继承
	virtual void Tick(float DeltaTime) override;
	virtual void SendControllerEvents() override;
	virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;
	virtual bool Exec(UWorld * InWorld, const TCHAR * Cmd, FOutputDevice & Ar) override;
	virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
	virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues & values) override;
	virtual bool IsGamepadAttached() const override;
	//// 通过 IMotionController 继承
	static FName DeviceTypeName;
	virtual FName GetMotionControllerDeviceTypeName() const override
	{
		return DeviceTypeName;
	}
	/**
	* Returns the calibration-space orientation of the requested controller's hand.
	*
	* @param ControllerIndex	The Unreal controller (player) index of the contoller set
	* @param DeviceHand		Which hand, within the controller set for the player, to get the orientation and position for
	* @param OutOrientation	(out) If tracked, the orientation (in calibrated-space) of the controller in the specified hand
	* @param OutPosition		(out) If tracked, the position (in calibrated-space) of the controller in the specified hand
	* @return					True if the device requested is valid and tracked, false otherwise
	*/
	virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const EControllerHand DeviceHand, FRotator& OutOrientation, FVector& OutPosition, float WorldToMetersScale) const;
	/**
	* Returns the tracking status (e.g. not tracked, intertial-only, fully tracked) of the specified controller
	*
	* @return	Tracking status of the specified controller, or ETrackingStatus::NotTracked if the device is not found
	*/
	virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const EControllerHand DeviceHand) const override;

	//IHapticDevice overrides
	IHapticDevice* GetHapticDevice() override { return (IHapticDevice*)this; }
	virtual void SetHapticFeedbackValues(int32 ControllerId, int32 Hand, const FHapticFeedbackValues & Values) override;
	virtual void GetHapticFrequencyRange(float & MinFrequency, float & MaxFrequency) const override;
	virtual float GetHapticAmplitudeScale() const override;

private:
	/** Delay before sending a repeat message after a button was first pressed */
	float InitialButtonRepeatDelay; // How long a button is held for before you send a 2nd event

									/** Delay before sending a repeat message after a button has been pressed for a while */
	float ButtonRepeatDelay; // How long a button is held for before you send a 3rd/4th/e.t.c event

							 /** The recipient of motion controller input events */
	TSharedPtr< FGenericApplicationMessageHandler > MessageHandler;
	//FGamepadKeyNames::Type Buttons[CONTROLLERS_PER_PLAYER][ENoloVRControllerButton::TotalButtonCount];

private:
	//FNoloButtonState ButtonState[CONTROLLERS_PER_PLAYER][(int32)ENoloVRControllerButton::TotalButtonCount];
	FNoloControllerState ControllerStates[CONTROLLERS_PER_PLAYER];

	/** Mapping of controller buttons */
	FGamepadKeyNames::Type Buttons[MaxTrackedDeviceCount][(int32)ENoloVRControllerButton::TotalButtonCount];


	//用来监听双击menu用的时间记录
	float curTime;
	float preLSDoubleSystemTime;
	float preRSDoubleSystemTime;
};