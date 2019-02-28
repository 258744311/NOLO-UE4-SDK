#pragma once
#ifndef _NOLO_V_0_1_RC_API_H_
#define _NOLO_V_0_1_RC_API_H_
#include "nolo_math.h"
#include <stdlib.h>
#include <memory>
#include <string>
//#ifndef NOLO_IMPORT
//#define NOLO_IMPORT  __declspec(dllimport)
//#else
//#define NOLO_IMPORT
//#endif
//#if PLATFORM_WINDOWS
//typedef void(__cdecl *funcCallBack)(void * context);
//typedef void(__cdecl *expandMsgCallBack)(ENExpandMsgType expandMsgType, void * context);
//#endif

#ifdef __cplusplus
extern "C" {
#endif

	/**
	******************************************************************************
	* Function description��Search for NOLO device
	* Parameter��NULL
	* Return Value��NULL
	* Remarks��NULL
	******************************************************************************
	*/
	void  OpenNoloDevice();
	/*
	******************************************************************************
	* Function description��Close the connection with NOLO device and release resources
	* Parameter��NULL
	* Return Value��NULL
	* Remarks��NULL
	******************************************************************************
	*/
	void  CloseNoloDevice();

	//------------------------------------Android API--------------------------------------
	/**
	******************************************************************************
	* Function description��Get devices power information
	* Parameter��int
	0:hmd
	1:Left conroller
	2:Right controller
	3:basestation
	* Return Value��int
	******************************************************************************
	*/
	int  getElectricityByDeviceType(int type);

	/*
	******************************************************************************
	* Function description��Set vibration functions of NOLO controller
	* Parameter��Parameter devicetype is an enumeration type,Parameter intensity : Vibration intensity range from 0~100, the bigger the stronger
	* Return Value��Return bool type
	* Remarks��Parameter devicetype ��
	0:hmd
	1:Left conroller
	2:Left controller
	3:basestation
	******************************************************************************
	*/
	bool triggerHapticPulse(int deviceType, int intensity);

	void setHmdType(int hmdType);
	
	/**
	******************************************************************************
	* Function description��Get device tracking information
	* Parameter��int
	0:hmd
	1:Left conroller
	2:Right controller
	3:basestation
	* Return Value��Nolo_Pose
	******************************************************************************
	*/
	NTrackedDevicePose  getPoseByDeviceType(int type);

	/**
	******************************************************************************
	* Function description��Get the handle status information
	* Parameter��int
	0:hmd
	1:Left conroller
	2:Left controller
	3:basestation
	* Return Value��Nolo_ControllerStates
	******************************************************************************
	*/
	NControllerState  getControllerStatesByDeviceType(int type);

	/**
	******************************************************************************
	* Function description��
	* Parameter��
	******************************************************************************
	*/
	void setAppKey(const char* data);

	/**
	******************************************************************************
	* Function description��
	* Parameter��
	******************************************************************************
	*/

	void reportError(const char* data);

#ifdef __cplusplus
}
#endif

namespace nolovr {

	class NoloVrApi {
	public:

		NoloVrApi() {

		}
		// Deprecated factory-style create method.
		// TODO(btco): remove this once no one is using it.
		static std::unique_ptr<NoloVrApi> Create() {
			return std::unique_ptr<NoloVrApi>(new NoloVrApi());
		}

		void Search_Nolo_Device() {
#ifdef __ANDROID__
#else
			//search_Nolo_Device();
			OpenNoloDevice();
#endif 
		}

		void Close_Nolo_Device(){
#ifdef __ANDROID__
#else
			//close_Nolo_Device();
			 CloseNoloDevice();
#endif 
		}
		
		void SetHmdTrackingCenterByDeviceType(int deviceType) {
			setHmdType(deviceType);
		}

		bool TriggerHapticPulse(int deviceType, int intensity) {
			triggerHapticPulse(deviceType,intensity);
			return true;
		}
		
		NTrackedDevicePose GetPoseByDeviceType(int type) {
			NTrackedDevicePose nTrackedDevicePose{ { 0,0,0 },{ 0,0,0,0 },{ 0,0,0 },{ 0,0,0 },0,false };
			nTrackedDevicePose = getPoseByDeviceType(type);
			return nTrackedDevicePose;
		}

		int GetElectricityByDeviceType(int deviceType) {
			int battery = 0;
			battery = getElectricityByDeviceType(deviceType);
			return battery;
		}

		NControllerState GetControllerStateByDeviceType(int type) {
			NControllerState nControllerState{ 0,0,{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };
			nControllerState = getControllerStatesByDeviceType(type);
			return nControllerState;
		}

		void SetAppKey(const char *data) {

#ifdef __ANDROID__
			setAppKey(data);
#else
			OpenNoloDevice();
#endif 
		}	
		void ReportError(const char* data) {
#ifdef __ANDROID__
			reportError(data);
#else
#endif 
		}
	};
}

#endif // _NOLO_IMPORT_Version2_H_