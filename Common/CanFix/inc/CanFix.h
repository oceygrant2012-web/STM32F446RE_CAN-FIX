/*
 * CanFix.h
 *
 *  Created on: Oct 24, 2026
 *      Author: oceyg
 */

#ifndef APPLICATION_USER_CORE_CANFIX_H_
#define APPLICATION_USER_CORE_CANFIX_H_
#include "main.h"
typedef struct
{
  uint32_t StdId;    /*!< Specifies the standard identifier.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x7FF. */

  uint32_t ExtId;    /*!< Specifies the extended identifier.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x1FFFFFFF. */

  uint32_t IDE;      /*!< Specifies the type of identifier for the message that will be transmitted.
                          This parameter can be a value of @ref CAN_identifier_type */

  uint32_t RTR;      /*!< Specifies the type of frame for the message that will be transmitted.
                          This parameter can be a value of @ref CAN_remote_transmission_request */

  uint32_t DLC;      /*!< Specifies the length of the frame that will be transmitted.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 8. */

  FunctionalState TransmitGlobalTime; /*!< Specifies whether the timestamp counter value captured on start
                          of frame transmission, is sent in DATA6 and DATA7 replacing pData[6] and pData[7].
                          @note: Time Triggered Communication Mode must be enabled.
                          @note: DLC must be programmed as 8 bytes, in order these 2 bytes are sent.
                          This parameter can be set to ENABLE or DISABLE. */

} CAN_FIX_TxHeaderTypeDef;

/**
  * @brief  CAN Rx message header structure definition
  */
typedef struct
{
  uint32_t StdId;    /*!< Specifies the standard identifier.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x7FF. */

  uint32_t ExtId;    /*!< Specifies the extended identifier.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x1FFFFFFF. */

  uint32_t IDE;      /*!< Specifies the type of identifier for the message that will be transmitted.
                          This parameter can be a value of @ref CAN_identifier_type */

  uint32_t RTR;      /*!< Specifies the type of frame for the message that will be transmitted.
                          This parameter can be a value of @ref CAN_remote_transmission_request */

  uint32_t DLC;      /*!< Specifies the length of the frame that will be transmitted.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 8. */

  uint32_t Timestamp; /*!< Specifies the timestamp counter value captured on start of frame reception.
                          @note: Time Triggered Communication Mode must be enabled.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0xFFFF. */

  uint32_t FilterMatchIndex; /*!< Specifies the index of matching acceptance filter element.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0xFF. */

} CAN_FIX_RxHeaderTypeDef;

struct CAN_FIX_Comms
{
	uint16_t StdId;
	uint8_t Count;
	char Description[50];
	char DataType[7];
	uint8_t Precision;
	float LowLimit;
	float HighLimit;
	char UnitOfMeasure[10];
};


//High Priority Pilot Control Inputs
#define HighPriorityFlapControlSwitchCanId_0 0x100
#define HighPriorityTrimControlSwitchCanId_0 0x102
#define HighPriorityElectricalControlSwitchCanId_0 0x104
#define HighPriorityLightingControlSwitchCanId_0 0x106
#define HighPriorityFuelPumpControlSwitchCanId_0 0x108
#define HighPriorityFuelValveControlSwitchCanId_0 0x10A
#define HighPriorityAutoPilotControlSwitchCanId_0 0x10C
#define HighPriorityVHFControlSwitchCanId_0 0x10E
#define HighPriorityTransponderControlSwitchCanId_0 0x110
#define HighPriorityStarterMagsControlSwitchCanId_0 0x112
#define HighPriorityLandingGearControlSwitchCanId_0 0x114
#define HighPriorityKeypadKeyControlCanId_0 0x116
#define HighPriorityGenericControlSwitchCanId_0 0x118

// These are set by CAN_FIX_SendHighPriorityControlPositionInt
//High Priority Measured Positions
#define HighPriorityPitchControlCanId 0x11A
#define HighPriorityRollControlCanId 0x11B
#define HighPriorityYawControlCanId 0x11C
#define HighPriorityCollectiveControlCanId 0x11D
#define HighPriorityAntiTorqueControlCanId 0x11E
#define HighPriorityFlapControlCanId 0x11F

//High Priority Controls
#define HighPriorityLeftBrakeControlCanId 0x120
#define HighPriorityRightBrakeControlCanId 0x121
#define HighPriorityEngineThrottleControlCanId_0 0x122
#define HighPriorityEnginePropControlCanId_0 0x126
#define HighPriorityEngineMixtureControlCanId_0 0x12A

//High Priority Measurements
#define HighPriorityElevatorMeasurementCanId 0x140
#define HighPriorityAileronMeasurementCanId 0x141
#define HighPriorityRudderMeasurementCanId 0x142
#define HighPriorityCollectiveMeasurementCanId 0x143
#define HighPriorityTailRotorMeasurementCanId 0x144
#define HighPriorityFlapMeasurementCanId 0x145
#define HighPriorityLandingGearPositionSwCanId 0x146

#define HighPriorityPitchAngleMeasurementCanId 0x180
#define HighPriorityRollAngleMeasurementCanId 0x181
#define HighPriorityAngleOfAttackMeasurementCanId 0x182
#define HighPriorityIndicatedAirspeedMeasurementCanId 0x183
#define HighPriorityIndicatedAltitudeMeasurementCanId 0x184
#define HighPriorityHeadingMeasurementCanId 0x185
#define HighPriorityVsiMeasurementCanId 0x186
#define HighPriorityVariometerVerticalSpeedMeasurementCanId 0x187
#define HighPriorityRadarAltitudeMeasurementCanId 0x188
#define HighPriorityYawMeasurementCanId 0x189
#define HighPriorityNormalAccelerationMeasurementCanId 0x18A
#define HighPriorityLateralAccelerationMeasurementCanId 0x18B
#define HighPriorityLongitudinalAccelerationMeasurementCanId 0x18C
#define HighPriorityTrueAirspeedMeasurementCanId 0x18D
#define HighPriorityCalibratedAirspeedMeasurementCanId 0x18E
#define HighPriorityMachAirspeedMeasurementCanId 0x18F
#define HighPriorityAltemeterSettingCanId 0x190
#define HighPriorityPressureAltitudeMeasurementCanId 0x191

#define HighPriorityILSDeviationCanId 0x1C0
#define HighPriorityGlideslopeDeviationCanId 0x1C1
#define HighPriorityPositionLatitudeCanId 0x1C2
#define HighPriorityPositionLongitudeCanId 0x1C3
#define HighPriorityGroundSpeedCanId 0x1C4
#define HighPriorityTrueGroundTrackCanId 0x1C5
#define HighPriorityMagneticGroundTrackCanId 0x1C6

#define HighPriorityGroundTrackErrorCanId 0x1C7
#define HighPrioritySelectedCourseCanId 0x1C8
#define HighPrioritySelectedVORRadialCanId 0x1C9
#define HighPrioritySelectedGlidePathAngleCanId 0x1CA
#define HighPrioritySelectedVerticalSpeedCanId 0x1CB
#define HighPrioritySelectedAltitudeCanId 0x1CC
#define HighPriorityRAIMStatusCanId 0x1CD
#define HighPriorityRAIMHorizontalErrorCanId 0x1CE
#define HighPriorityRAIMVerticalErrorCanId 0x1CF
#define HighPriorityADSBAirbornePositionLatitudeCanId 0x1D0
#define HighPriorityADSBAirbornePositionLongitudeCanId 0x1D1
#define HighPriorityADSBAirbornePositionAltitudeCanId 0x1D2
#define HighPriorityADSBSurfacePositionLatitudeCanId 0x1D3
#define HighPriorityADSBSurfacePositionLongitudeCanId 0x1D4
#define HighPriorityADSBSurfacePositionAltitudeCanId 0x1D5
#define HighPriorityADSBStatusCanId 0x1D6
#define HighPriorityADSBIdentificationCanId 0x1D7
#define HighPriorityADSBTypeCanId 0x1D8
#define HighPriorityADSBAirborneVelocityCanId 0x1D9
#define HighPriorityADSBAirborneBearingCanId 0x1DA
#define HighPriorityADSBAirborneRateOfClimbCanId 0x1DB
#define HighPriorityADSBEmergencyPriorityCanId 0x1DC
#define HighPriorityADSBCurrentTrajectoryChangePointCanId 0x1DD
#define HighPriorityADSBNextTrajectoryChangePointCanId 0x1DE
#define HighPriorityADSBOperationCoordMessageCanId 0x1DF
#define HighPriorityADSBOperationalStatusCanId 0x1E0

#define HighPriorityEngineRPMCanId_0 0x200
#define HighPriorityPropRPMCanId_0 0x204
#define HighPriorityTorqueCanId_0 0x208
#define HighPriorityTurbineInletTempCanId_0 0x20C
#define HighPriorityTurbineInterTempCanId_0 0x210
#define HighPriorityTurbineOutletTempCanId_0 0x214
#define HighPriorityFuelPressureSwitchCanId_0 0x218
#define HighPriorityOilPressureSwitchCanId_0 0x21C
#define HighPriorityOilTemperatureSwitchCanId_0 0x220
#define HighPriorityCoolantTemperatureSwitchCanId_0 0x224
#define HighPriorityFuelQuantitySwitchCanId_0 0x228
#define HighPriorityOilQuantitySwitchCanId_0 0x22C
#define HighPriorityCoolantQuantitySwitchCanId_0 0x230

//Base CanID for SendEngineSensorReading
#define HighPriorityFuelFlowCanId_0 0x234
//Final value for SendEngineSensorReading
#define HighPriorityMainBatCharge_3 0x267

#define HighPriorityCabinPressureCanId 0x280
#define HighPriorityCabinAltitudeCanId 0x281
#define NormalPrioritySpeedBrakeControlCanId 0x300
#define NormalPrioritySpeedBrakePositionCanId 0x380
#define NormalPriorityLightStatusCanId 0x38A



typedef enum
{
	Pilot,
	CoPilot
}PilotLocationTypedef;





///////////////////////////////////////////////////////////////////////////////////////////////////////////#define CanFix_Switch_0 0x01
#define CanFix_Switch_1 0x02
#define CanFix_Switch_2 0x04
#define CanFix_Switch_3 0x08
#define CanFix_Switch_4 0x10
#define CanFix_Switch_5 0x20
#define CanFix_Switch_6 0x40
#define CanFix_Switch_7 0x80

typedef enum
{
	EngineRpm,
	PropRpm,
} RpmTypedef;

typedef enum
{
	InletTemp,
	InterTemp,
	OutletTemp,
} TurbineTempTypedef;

typedef enum{
	Min = 0b0001,
	Max = 0b0010,
	LowWarn = 0b0100,
	LowAlarm = 0b0101,
	HighWarn = 0b0110,
	HIghAlarm = 0b0111,
}RpmMetadataTypedef;

typedef enum {
	Angle_Min = 1,
	Angle_Max = 2
}AttitudeAngleTypedef;

typedef enum {
	FlapPosition_Up = 0x01,
	FlapPosition_Down = 0x02,
	FlapPosition_1 = 0x04,
	FlapPosition_2 = 0x08,
	FlapPosition_3 = 0x10,
	FlapPosition_4 = 0x20,
	FlapPosition_5 = 0x40,
	FlapPosition_6 = 0x80
} FlapPositionTypedef;

typedef enum {
	TrimPosition_PitchUp = 0x0001,
	TrimPosition_PitchDown = 0x0002,
	TrimPosition_PitchCenter = 0x0004,
	TrimPosition_RollLeft = 0x0008,
	TrimPosition_RollRight = 0x0010,
	TrimPosition_RollCenter = 0x0020,
	TrimPosition_YawLeft = 0x0040,
	TrimPosition_YawRight = 0x0080,
	TrimPosition_YawCenter = 0x0100,
	TrimPosition_CollectiveUp = 0x0200,
	TrimPosition_CollectiveDown = 0x0400,
	TrimPosition_AtPedalsLeft = 0x0800,
	TrimPosition_AtPedalsRight = 0x1000,
	TrimPosition_AtPedalsCenter = 0x2000
} TrimPositionTypedef;



typedef enum{
	AutoPilot_Engage = 0x01,
	AutoPilot_Disengage = 0x02,
	AutoPilot_VSMode = 0x04,
	AutoPilot_AltHoldMode = 0x08,
	AutoPilot_AltSelectMode = 0x10,
	AutoPilot_HeadingIncrement = 0x20,
	AutoPilot_HeadingDecrement = 0x40
} AutopilotTypedef;



typedef enum{
	VHF_PTT = 0x01,
	VHF_Swap = 0x02,
	VHF_Next = 0x04,
	VHF_Last = 0x08
} VHFTypedef;



typedef enum{
	Transponder_Ident = 0x01,
	Transponder_Alt1 = 0x02,
	Transponder_Stby = 0x04,
	Transponder_Alt2 = 0x08,
	Transponder_VFR = 0x10,
	Transponder_OFF = 0x20,
	Transponder_Squat = 0x40
} TransponderTypedef;



typedef enum{
	LandingGear_Down  = 0,
	LandingGear_Up = 1,
	LandingGear_Nose = 0x01,
	LandingGear_Left = 0x02,
	LandingGear_Right = 0x04
} LandingGearTypedef;

typedef enum{
	ControlSurfaceControl_Pitch,
	ControlSurfaceControl_Roll,
	ControlSurfaceControl_Yaw,
	ControlSurfaceControl_Collective,
	ControlSurfaceControl_AntiTorquePedals,
	ControlSurfaceControl_Flaps
}ControlSurfaceControlsTypedef;

typedef enum{
	ControlLever_LeftBrake,
	ControlLever_RightBrake,
	ControlLever_EngineThrottle,
	ControlLever_EngineProp,
	ControlLever_EngineMixture,
}ControlLeverTypedef;

typedef enum{
	ControlSurfaceMeasurement_Flaps,
	ControlSurfaceMeasurement_Elevator,
	ControlSurfaceMeasurement_Aileron,
	ControlSurfaceMeasurement_Rudder,
	ControlSurfaceMeasurement_Collective,
	ControlSurfaceMeasurement_TailRotor
}ControlSurfaceMeasurementsTypedef;

typedef enum
{
	SpeedBrakeControl,
	CowlFlapsControl,
	PitchTrimControl,
	RollTrimControl,
	YawTrimControl,
	PilotControlMaxValue

} PilotControlInputTypedef;

//


typedef enum
{
	SpeedBrakePosition,
	CowlFlapsPosition,
	PitchTrimPosition,
	RollTrimPosition,
	YawTrimPosition,
	PitchTrimMotorSpeed,
	RollTrimMotorSpeed,
	YawTrimMotorSpeed,
	CollectiveTrimMotorSpeed,
	AntiTorqueTrimMotorSpeed,
	MesuredPositionsMaxValue

} NormalPositionMeasurementsTypedef;

typedef enum
{
	LightStatus,
	FuelPumpStatus,
	FuelValveStatus,
	NormalStatusMaxValue
} NormalStatusTypedef;

typedef enum
{
	FuelFlow,
	FuelPressure, //4
	ManifoldPressure, //8
	OilPressure, //12
	OilTemp, //16
	CoolantTemp, //20
	FuelQuanity, //24
	FuelPumpPressure, //28
	OilQuantity, //32
	CoolantQuantity, //36
	ElectPropMotorCurrent, //40
	MainPropBusCurrent, //44
	MainBatCurrent, //48
	MainBatTemp, //52
	MainBatCharge, //56
	SystemSensorMaxValue //60

} SystemSensorTypedef;


#define LandingGear_NoseUpFlag 0x0001
#define LandingGear_NoseDownFlag 0x0002
#define LandingGear_LeftUpFlag 0x0004
#define LandingGear_LeftDownFlag 0x0008
#define LandingGear_RightUpFlag 0x0010
#define LandingGear_RightDownFlag 0x0020
#define LandingGear_NoseNotDown 0x0040
#define LandingGear_LeftNotDown 0x0080

typedef enum {
	Attitude_Pitch,
	Attitude_Roll
}AttitudeTypedef;

typedef enum {
	Aoa_Min = 0b0001,
	Aoa_Max = 0b0010,
	Aoa_0g = 0b0111,
	Aoa_Warn = 0b1000,
	Aoa_Stall = 0b1001

}AngleOfAttackTypedef;

typedef enum  {
	Airspeed_Min = 0b0001,
	Airspeed_Max = 0b0010,
	Airspeed_V1 = 0b0011,
	Airspeed_V2 = 0b0100,
	Airspeed_Vne = 0b0101,
	Airspeed_Vfe = 0b0110,
	Airspeed_Vmc = 0b0111,
	Airspeed_Va = 0b1000,
	Airspeed_Vno = 0b1001,
	Airspeed_Vs = 0b1010,
	Airspeed_Vs0 = 0b1011,
	Airspeed_Vx = 0b1110,
	Airspeed_Vy = 0b1111
} AirspeedMetadataTypedef;

typedef enum
{
	FlapControlSwitches,      //100
	TrimControlSwitches,      //102
	ElectricalBusControlSwitches, //104
	LightingControlSwitches,  //106
	FuelPumpControlSwitches,//108
	FuelValveControlSwitches, //10A
	AutoPilotControlSwitches,     //10C
	VhfControlSwitches,    //10E
	TransponderControlSwitches,   //110
	StarterMagnetoControlSwitches, //112
	LandingGearControlSwitches,    //114
	GenericControlSwitches,       //118

} ControlSwitchTypedef;

typedef enum
{
	LandingGearPositionIndicatorSwitch, //146
	FuelPressureIndicatorSwitch, //218
	OilPressureIndicatorSwitch, //21C
	OilTemperatureIndicatorSwitch, //220
	CoolantTemperatureIndicatorSwitch, //224
	FuelQuantityIndicatorSwitch, //228
	OilQuantityIndicatorSwitch, //22C
	CoolantQuantityIndicatorSwitch //230

} IndicatorSwitchTypedef;

typedef enum
{
	FuelPressureSwitch,
	OilPressureSwitch,
	OilTempSwitch,
	CoolantTempSwitch,
	FuelQuantitySwitch,
	OilQuantitySwitch,
	CoolantQuantitySwitch,
	SystemMaxValue
} EngineFluidSwitchTypedef;


typedef enum int8_t
{
	Normal = 0,
	High = 1,
	Low = -1
}SwitchValueTypedef;

void CAN_FIX_SendHighPriortyNodeAlarm(uint16_t alarm, uint8_t* alarmData, uint8_t alarmDataLength);
void CAN_FIX_SendHighPriorityKeyPress( PilotLocationTypedef pilot, uint8_t index, uint8_t functionCode, uint8_t key, uint8_t altFunction);
void CAN_FIX_SendHighPriorityFlapControlSwitch(PilotLocationTypedef device, FlapPositionTypedef button);
void CAN_FIX_SendHighPriorityTrimControlSwitch(PilotLocationTypedef device, TrimPositionTypedef button);
void CAN_FIX_SendAutopilotControl(PilotLocationTypedef device, AutopilotTypedef button);
void CAN_FIX_SendVHFControl(PilotLocationTypedef device, VHFTypedef button);
void CAN_FIX_SendTransponderControl(PilotLocationTypedef device, TransponderTypedef button);
void CAN_FIX_SendLandingGearControl(PilotLocationTypedef device, LandingGearTypedef button);
void CAN_FIX_SendSwitchControl(ControlSwitchTypedef surface, uint8_t index, uint8_t button);
void CAN_FIX_SendControlSurfaceControlPosition(ControlSurfaceControlsTypedef surface, float position );
void CAN_FIX_SendControlLeverPosition(ControlLeverTypedef lever, uint8_t element, float position, uint8_t index );
void CAN_FIX_SendControlAngle(ControlSurfaceMeasurementsTypedef surface, float angle, uint8_t index, AttitudeAngleTypedef metaData );
//NOte:  for a specified gear neither down nor up, both the respective flags
// are to be set to zero.
void CAN_FIX_SendLandingGearPosition(uint8_t flags, uint8_t index , AirspeedMetadataTypedef metaData );
void CAN_FIX_SendAttitude (AttitudeTypedef attitude, float angle, uint8_t index, AttitudeAngleTypedef metaData );
void CAN_FIX_SendAngleOfAttack(float aoa, uint8_t index, AngleOfAttackTypedef metaData );
void CAN_FIX_SendIndicatedAirspeed(float airspeed, uint8_t index, AirspeedMetadataTypedef metaData );
void CAN_FIX_SendIndicatedAltitude(float altitude, uint8_t index, AirspeedMetadataTypedef metaData );
void CAN_FIX_SendIndicatedHeading(float heading, uint8_t index, AirspeedMetadataTypedef metaData );
void CAN_FIX_SendVerticalSpeed(float vsi, uint8_t index, AttitudeAngleTypedef metadata );
void CAN_FIX_SendVariometerVerticalSpeed(float vsi, uint8_t index, AttitudeAngleTypedef metadata );
void CAN_FIX_SendRadarAltitude(float altitude, uint8_t index, AttitudeAngleTypedef metadata  );
void CAN_FIX_SendYawMeasurement(float yaw, uint8_t index, AttitudeAngleTypedef metadata );
void CAN_FIX_SendNormalAcceleration(float acceleration, uint8_t index, AttitudeAngleTypedef metadata  );
void CAN_FIX_SendLateralAcceleration(float acceleration, uint8_t index, AttitudeAngleTypedef metadata  );
void CAN_FIX_SendLongitudinalAcceleration(float acceleration, uint8_t index, AttitudeAngleTypedef metadata );
void CAN_FIX_SendTrueAirspeed(float airspeed, uint8_t index, AttitudeAngleTypedef metaData );
void CAN_FIX_SendCalibratedAirspeed(float airspeed, uint8_t index, AttitudeAngleTypedef metaData );
void CAN_FIX_SendMachAirspeed(float airspeed, uint8_t index, AttitudeAngleTypedef metaData );
void CAN_FIX_SendAltimeterSetting(float alt, uint8_t index, AttitudeAngleTypedef metaData );
void CAN_FIX_SendPressureAltitude(float presAlt, uint8_t index, AttitudeAngleTypedef metaData );


///////////////////////// CanFix Core //////////////////////////////////////////////////////
//Initialize CAN-Fix and set up the CAN hardware
void CAN_FIX_Initialize(uint32_t canId);
//If interrupts do not work for the platform, a periodic check can check if anything
//is in the receive buffer
void CAN_FIX_PeriodicCheck(void);

const struct CAN_FIX_Comms* FindCanFixComms(uint16_t canId);

//Standard CAN ID is 11-bits
void CAN_FIX_HandleCanRxMessage(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);
void CAN_FIX_SendNodeAlarm(uint16_t alarm, uint8_t* alarmData, uint8_t alarmDataLength);
void CAN_FIX_SendDataMessage(uint16_t canId, uint8_t index, uint8_t functionCode, uint8_t* messageData, uint8_t dataLength);

///////////////////////// CanFix Send //////////////////////////////////////////////////////

void CAN_FIX_SendNodeAlarm(uint16_t alarm, uint8_t* alarmData, uint8_t alarmDataLength);
void CAN_FIX_SendFloatMeasurement(const struct CAN_FIX_Comms* comms, uint16_t canId, uint8_t index, uint8_t functionCode, float floatData);

///////////////////////// CanFix Receive //////////////////////////////////////////////////////

//Handle Incoming data.  Override the function that is neccessary for the specific need
/* Define the default function with __weak attribute */
void CAN_FIX_HandleHighPriorityNodeAlarm(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleHighPriorityPilotControlInput(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleHighPriorityMeasuredPosition(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleHighPriorityFlightData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleHighPriorityNavigationData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleHighPriorityEngineAircraftData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleHighPriorityAuxiliaryData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleNormalPriorityPilotControlInput(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleNormalPriorityMeasuredPosition(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleNormalPriorityFlightData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleNormalPriorityNavigationData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleNormalPriorityEngineAircraftData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleNormalPriorityAuxiliaryData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleTwoWayConnectionChannelData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);

/* Define the default function with __weak attribute */
void CAN_FIX_HandleNodeSpecificMessage(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData);
#endif /* APPLICATION_USER_CORE_CANFIX_H_ */
