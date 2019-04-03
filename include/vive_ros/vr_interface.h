#ifndef _VR_INTERFACE_H_
#define _VR_INTERFACE_H_

#include <openvr.h>
#include <boost/function.hpp>

typedef boost::function<void(const std::string&)> DebugMsgCallback;
typedef boost::function<void(const std::string&)> InfoMsgCallback;
typedef boost::function<void(const std::string&)> ErrorMsgCallback;

const int BUTTON_NUM = 4;
const int AXES_NUM = 2;
const long long int HTC_VIVE_MENU_BUTTON = (1LL << 1);
const long long int HTC_VIVE_TRIGGER_BUTTON = (1LL << 33);
const long long int HTC_VIVE_TRACKPAD_BUTTON = (1LL << 32);
const long long int HTC_VIVE_GRIP_BUTTON = (1LL << 2);

class VRInterface
{
  public:
    VRInterface();
    ~VRInterface();
    
    bool Init();
    void Shutdown();
    
    void Update();
    void UpdateCalibration();
    void HandleInput();
    void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, int usDurationMicroSec);
    
    int GetDeviceMatrix(int index, double pMatrix[3][4]);
    int GetDeviceVel(int index, double lin_vel[3], double ang_vel[3]);
    bool IsDeviceConnected(int index);
    
    
    void setErrorMsgCallback(ErrorMsgCallback fn);
    void setInfoMsgCallback(InfoMsgCallback fn);
    void setDebugMsgCallback(DebugMsgCallback fn);
    
    vr::VRControllerState_t trackedDeviceStates[vr::k_unMaxTrackedDeviceCount];
  private:
    vr::IVRSystem *pHMD_;
    vr::IVRChaperone *pChaperone_;
    
    uint max_devices_;
    vr::TrackedDevicePose_t device_poses_[vr::k_unMaxTrackedDeviceCount];
    
  private:
    DebugMsgCallback debug_;
    InfoMsgCallback info_;
    ErrorMsgCallback error_;
    
    vr::ChaperoneCalibrationState cal_state_;
    float play_area_[2];
    vr::HmdQuad_t play_quat_;
    
    std::string GetTrackedDeviceString(vr::IVRSystem *pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError *peError = NULL);
};

#endif  // _VR_INTERFACE_H_