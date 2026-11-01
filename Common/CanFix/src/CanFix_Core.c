/*
 * CanFix_Core.c
 *
 *  Created on: Nov 1, 2026
 *      Author: oceyg
 */
#include <CanFix.h>
#include <CanFixHw.h>
#include <string.h>

/**
  * @brief  The ID of the node (can device number) sending or receiving the data
  */
uint16_t CAN_FIX_NodeId = 0;
CAN_FIX_TxHeaderTypeDef CAN_FIX_TxHeader;
uint8_t CanFixTxData[8];

/**
  * @brief  Initialize the CAN-FIX software.  Must be called before performing any other commands
  * nodeId: The ID of the node (can device number) sending or receiving the data (1.255)
  * nodeId should be issued either by the EFIS or stored in an eeprom
  */
void CAN_FIX_Initialize(uint32_t nodeId)
{
	CAN_FIX_TxHeader.StdId = 0;    /*!< Specifies the standard identifier.
	                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x7FF. */

	CAN_FIX_TxHeader.ExtId = 0;    /*!< Specifies the extended identifier.
	                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x1FFFFFFF. */

	CAN_FIX_TxHeader.IDE = CAN_ID_STD;      /*!< Specifies the type of identifier for the message that will be transmitted.
	                          This parameter can be a value of @ref CAN_identifier_type */

	CAN_FIX_TxHeader.RTR = CAN_RTR_DATA;      /*!< Specifies the type of frame for the message that will be transmitted.
	                          This parameter can be a value of @ref CAN_remote_transmission_request */

	CAN_FIX_TxHeader.DLC=0;      /*!< Specifies the length of the frame that will be transmitted.
	                          This parameter must be a number between Min_Data = 0 and Max_Data = 8. */

	CAN_FIX_TxHeader.TransmitGlobalTime = ENABLE; /*!< Specifies whether the timestamp counter value captured on start
	                          of frame transmission, is sent in DATA6 and DATA7 replacing pData[6] and pData[7].
	                          @note: Time Triggered Communication Mode must be enabled.
	                          @note: DLC must be programmed as 8 bytes, in order these 2 bytes are sent.
	                          This parameter can be set to ENABLE or DISABLE. */
	CAN_FIX_NodeId = nodeId;
	CanFixHw_Initialize(nodeId);
	//CAN_FIX does not give good options for hardware masks.
	//Disable the masks.
	CanFixHw_SetHardwareMask(0x0000);

}

void CAN_FIX_PeriodicCheck(void)
{
	CanFixHw_PeriodicCheck();
}

const struct CAN_FIX_Comms CAN_FIX_Commands[] = {
		{HighPriorityFlapControlSwitchCanId_0, 2, "Flap Control Switches", "BYTE", 0, 0, 0, "NONE"},
		{HighPriorityTrimControlSwitchCanId_0, 2, "Trim Switches", "BYTE", 0, 0, 0, "NONE"},
		{HighPriorityElectricalControlSwitchCanId_0, 2, "Electrical Bus Control Switches", "BYTE", 0, 0, 0, "NONE"},
		{HighPriorityLightingControlSwitchCanId_0, 2, "Lighting Control Switches", "BYTE", 0, 0, 0, "NONE"},
		{HighPriorityFuelPumpControlSwitchCanId_0, 2, "Fuel Pump System Switches", "BYTE", 0, 0, 0, "NONE"},
		{HighPriorityFuelValveControlSwitchCanId_0, 2, "Fuel Valve System Switches", "BYTE", 0, 0, 0, "NONE"},
		{HighPriorityAutoPilotControlSwitchCanId_0, 2, "AutoPilot Commands", "BYTE", 0, 0, 0, "NONE"},
		{HighPriorityVHFControlSwitchCanId_0, 2, "VHF Control Commands", "BYTE", 0, 0, 0, "NONE"},
		{HighPriorityTransponderControlSwitchCanId_0, 2, "Transponder Commands", "BYTE", 0, 0, 0, "NONE"},
		{HighPriorityStarterMagsControlSwitchCanId_0, 2, "Starter / Magneto Commands", "BYTE", 0, 0, 0, "NONE"},
		{HighPriorityLandingGearControlSwitchCanId_0, 2, "Landing Gear Control Position", "BYTE", 0, 0, 0, "NONE"},
		{HighPriorityKeypadKeyControlCanId_0, 2, "Keypad Input", "WORD", 0, 0, 0, "NONE"},
		{HighPriorityGenericControlSwitchCanId_0, 2, "Generic Switches", "BYTE", 0, 0, 0, "NONE"},

		{HighPriorityPitchControlCanId, 1, "Pitch Control Position", "INT", 2, -100.0, 100.0, "%"},
		{HighPriorityRollControlCanId, 1, "Roll Control Position", "INT", 2, -100.0, 100.0, "%"},
		{HighPriorityYawControlCanId, 1, "Yaw Control Position", "INT", 2, -100.0, 100.0, "%"},
		{HighPriorityCollectiveControlCanId, 1, "Collective Control Position", "INT", 2, -100.0, 100.0, "%"},
		{HighPriorityAntiTorqueControlCanId, 1, "Anti-Torque Pedals Position", "INT", 2, -100.0, 100.0, "%"},
		{HighPriorityFlapControlCanId, 1, "Flap Control Position", "INT", 2, -100.0, 100.0, "%"},
		{HighPriorityLeftBrakeControlCanId, 1, "Left Brake Control Position", "UINT", 2, 0.0, 100.0, "%"},
		{HighPriorityRightBrakeControlCanId, 1, "Right Brake Control Position", "UINT", 2, 0.0, 100.0, "%"},
		{HighPriorityEngineThrottleControlCanId_0, 4, "Engine Throttle Control Position", "UINT", 2, 0.0, 100.0, "%"},
		{HighPriorityEnginePropControlCanId_0, 4, "Engine Prop Control Position", "UINT", 2, 0.0, 100.0, "%"},
		{HighPriorityEngineMixtureControlCanId_0, 4, "Engine Mixture Control Position", "UINT", 2, 0.0, 100.0, "%"},
		{HighPriorityElevatorMeasurementCanId, 1, "Elevator Position", "INT", 2, -90.0, 90.0, "°"},
		{HighPriorityAileronMeasurementCanId, 1, "Aileron Position", "INT", 2, -90.0, 90.0, "°"},
		{HighPriorityRudderMeasurementCanId, 1, "Rudder Position", "INT", 2, -90.0, 90.0, "°"},
		{HighPriorityCollectiveMeasurementCanId, 1, "Collective Position", "INT", 2, -90.0, 90.0, "°"},
		{HighPriorityTailRotorMeasurementCanId, 1, "Tail Rotor Angle", "INT", 2, -90.0, 90.0, "°"},
		{HighPriorityFlapMeasurementCanId, 1, "Flap Position", "INT", 2, -90.0, 90.0, "°"},
		{HighPriorityLandingGearPositionSwCanId, 1, "Landing Gear Position Switches", "BYTE", 0, 0.0, 0, "NONE"},
		{HighPriorityPitchAngleMeasurementCanId, 1, "Pitch Angle", "INT", 2, -180.0, 180.0, "°"},
		{HighPriorityRollAngleMeasurementCanId, 1, "Roll Angle", "INT", 2, -180.0, 180.0, "°"},
		{HighPriorityAngleOfAttackMeasurementCanId, 1, "Angle of Attack", "INT", 2, -180.0, 180.0, "°"},
		{HighPriorityIndicatedAirspeedMeasurementCanId, 1, "Indicated Airspeed", "UINT", 1, 0, 999.9, "knots"},
		{HighPriorityIndicatedAltitudeMeasurementCanId, 1, "Indicated Altitude", "DINT", 0, -1000.0, 60000.0, "ft"},
		{HighPriorityHeadingMeasurementCanId, 1, "Heading", "UINT", 1, 0.0, 359.9, "°"},
		{HighPriorityVsiMeasurementCanId, 1, "Vertical Speed", "INT", 0, -30000.0, 30000.0, "ft/min"},
		{HighPriorityVariometerVerticalSpeedMeasurementCanId, 1, "TE Variometer Vertical Speed", "INT", 2, -300.0, 300.0, "knots"},
		{HighPriorityRadarAltitudeMeasurementCanId, 1, "Radar Altitude", "UINT", 0, 0.0, 60000.0, "ft"},
		{HighPriorityYawMeasurementCanId, 1, "Yaw Angle", "INT", 2, -180.0, 180.0, "°"},
		{HighPriorityNormalAccelerationMeasurementCanId, 1, "Normal Acceleration", "INT", 3, -30.0, 30.0, "g"},
		{HighPriorityLateralAccelerationMeasurementCanId, 1, "Lateral Acceleration", "INT", 3, -30.0, 30.0, "g"},
		{HighPriorityLongitudinalAccelerationMeasurementCanId, 1, "Longitudinal Acceleration", "INT", 3, -30.0, 30.0, "g"},
		{HighPriorityTrueAirspeedMeasurementCanId, 1, "True Airspeed", "UINT", 1, 0.0, 2000.0, "knots"},
		{HighPriorityCalibratedAirspeedMeasurementCanId, 1, "Calibrated Airspeed", "UINT", 1, 0.0, 2000.0, "knots"},
		{HighPriorityMachAirspeedMeasurementCanId, 1, "Mach Number", "UINT", 2, 0.0, 100.0, "Mach"},
		{HighPriorityAltemeterSettingCanId, 1, "Altimeter Setting", "UINT", 1, 0.0, 35.0, "inHg"},
		{HighPriorityPressureAltitudeMeasurementCanId, 1, "Pressure Altitude", "DINT", 1, -1000.0, 60000.0, "ft"},
		{0x192, 1, "Mach Number", "UINT", 2, 0.0, 100.0, "Mach"},
		{HighPriorityILSDeviationCanId, 1, "ILS Deviation", "UINT", 1, 0.0, 359.9, "°"},
		{HighPriorityGlideslopeDeviationCanId, 1, "Glideslope Deviation", "UINT", 2, 0.0, 45, "°"},
		{HighPriorityPositionLatitudeCanId, 1, "Aircraft Position Latitude", "FLOAT", 0, -1e99, 1e99, "°"},
		{HighPriorityPositionLongitudeCanId, 1, "Aircraft Position Longitude", "FLOAT", 0, -1e99, 1e99, "°"},
		{HighPriorityGroundSpeedCanId, 1, "Groundspeed", "UINT", 1, 0.0, 2000.0, "knots"},
		{HighPriorityTrueGroundTrackCanId, 1, "True Ground Track", "UINT", 1, 0.0, 359.9, "°"},
		{HighPriorityMagneticGroundTrackCanId, 1, "Magnetic Ground Track", "UINT", 1, 0.0, 359.9, "°"},
		{HighPriorityGroundTrackErrorCanId, 1, "Cross Track Error", "INT", 2, -1e99, 1e99, "nm"},
		{HighPrioritySelectedCourseCanId, 1, "Selected Course", "UINT", 1, 0.0, 359.9, "°"},
		{HighPrioritySelectedVORRadialCanId, 1, "Selected VOR Radial", "UINT", 1, 0.0, 359.9, "°"},
		{HighPrioritySelectedGlidePathAngleCanId, 1, "Selected Glidepath Angle", "UINT", 1, 0.0, 90, "°"},
		{HighPrioritySelectedVerticalSpeedCanId, 1, "Selected Vertical Speed", "INT", 0, -30000.0, 330000.0, "ft/min"},
		{HighPrioritySelectedAltitudeCanId, 1, "Selected Altitude", "DINT", 0, -1000.0, 60000.0, "ft"},
		{HighPriorityRAIMStatusCanId, 1, "RAIM Status", "USHORT", 0, 0.0, 100, "NONE"},
		{HighPriorityRAIMHorizontalErrorCanId, 1, "RAIM Horizontal Error", "UINT", 0, 0, 1e99, "ft"},
		{HighPriorityRAIMVerticalErrorCanId, 1, "RAIM Vertical Error", "UINT", 0, 0, 1e99, "ft"},
		{HighPriorityADSBAirbornePositionLatitudeCanId, 1, "ADS-B ES Airborne Position Latitude", "FLOAT", 0, -1e99, 1e99, "°"},
		{HighPriorityADSBAirbornePositionLongitudeCanId, 1, "ADS-B ES Airborne Position Longitude", "FLOAT", 0, -1e99, 1e99, "°"},
		{HighPriorityADSBAirbornePositionAltitudeCanId, 1, "ADS-B ES Airborne Position Altitude", "DINT", 0, -1000, 60000, "ft"},
		{HighPriorityADSBSurfacePositionLatitudeCanId, 1, "ADS-B ES Surface Position Latitude", "FLOAT", 0, -1e99, 1e99, "°"},
		{HighPriorityADSBSurfacePositionLongitudeCanId, 1, "ADS-B ES Surface Position Longitude", "FLOAT", 0, -1e99, 1e99, "°"},
		{HighPriorityADSBSurfacePositionAltitudeCanId, 1, "ADS-B ES Surface Position Altitude", "DINT", 0, -1000, 60000, "ft"},
//#define HighPriorityADSBAirborneVelocityCanId 0x1D9
//#define HighPriorityADSBAirborneBearingCanId 0x1DA
		{HighPriorityADSBAirborneVelocityCanId, 1, "ADS-B ES Airborne Velocity", "UINT", 1, 0, 2000, "knots"},
		{HighPriorityADSBAirborneBearingCanId, 1, "ADS-B ES Airborne Bearing", "UINT", 1, 0.0, 359.9, "°"},
		{HighPriorityADSBAirborneRateOfClimbCanId, 1, "ADS-B ES Airborne Rate of Climb", "INT", 0, -30000.0, 330000.0, "ft/min"},
//#define HighPriorityADSBEmergencyPriorityCanId 0x1DC
//#define HighPriorityADSBCurrentTrajectoryChangePointCanId 0x1DD
//#define HighPriorityADSBNextTrajectoryChangePointCanId 0x1DE
//#define HighPriorityADSBOperationCoordMessageCanId 0x1DF
//#define HighPriorityADSBOperationalStatusCanId 0x1E0

		{HighPriorityEngineRPMCanId_0, 4, "Engine RPM", "UINT", 0, 0, 1e99, "RPM"},
		{HighPriorityPropRPMCanId_0, 4, "Prop/Rotor RPM", "UINT", 0, 0, 1e99, "RPM"},
		{HighPriorityTorqueCanId_0, 4, "Torque", "INT", 0, -1e99, 1e99, ""},
		{HighPriorityTurbineInletTempCanId_0, 4, "Turbine Inlet Temperature", "UINT", 1, 0, 1e99, "°C"},
		{HighPriorityTurbineInterTempCanId_0, 4, "Inter-turbine Temperature", "UINT", 1, 0, 1e99, "°C"},
		{HighPriorityTurbineOutletTempCanId_0, 4, "Turbine Outlet Temperature", "UINT", 1, 0, 1e99, "°C"},
		{HighPriorityFuelPressureSwitchCanId_0, 4, "Fuel Pressure Switch", "SHORT", 1, -10, 10, ""},
		{HighPriorityOilPressureSwitchCanId_0, 4, "Oil Pressure Switch", "SHORT", 1, -10, 10, ""},
		{HighPriorityOilTemperatureSwitchCanId_0, 4, "Oil Temp Switch", "SHORT", 1, -10, 10, ""},
		{HighPriorityCoolantTemperatureSwitchCanId_0, 4, "Coolant Temp Switch", "SHORT", 1, -10, 10, ""},
		{HighPriorityFuelQuantitySwitchCanId_0, 4, "Fuel Quantity Switch", "SHORT", 1, -10, 10, ""},
		{HighPriorityOilQuantitySwitchCanId_0, 4, "Oil Quantity Switch", "SHORT", 1, -10, 10, ""},
		{HighPriorityCoolantQuantitySwitchCanId_0, 4, "Coolant Quantity Switch", "SHORT", 1, -10, 10, ""},
		{HighPriorityFuelFlowCanId_0, 4, "Fuel Flow", "UINT", 2, -1000, 1000, "gal/hr"},
		{0x238, 4, "Fuel Pressure", "UINT", 2, -1000, 1000, "psi"},
		{0x23C, 4, "Manifold Pressure", "UINT", 2, -1000, 1000, "inHg"},
		{0x240, 4, "Oil Pressure", "UINT", 2, -1000, 1000, "psi"},
		{0x244, 4, "Oil Temp", "UINT", 1, -1000, 1000, "°C"},
		{0x248, 4, "Coolant Temp", "UINT", 1, -1000, 1000, "°C"},
		{0x24C, 4, "Fuel Quantity", "UINT", 2, -1000, 1000, "gal"},
		{0x250, 4, "Fuel Pump Pressure", "UINT", 2, -1000, 1000, "psi"},
		{0x254, 4, "Oil Quantity", "UINT", 2, -1000, 1000, "gal"},
		{0x258, 4, "Coolant Quantity", "UINT", 2, -1000, 1000, "gal"},
		{0x262, 2, "Main Battery Current", "INT", 0, -1000, 1000, "A"},
		{0x264, 2, "Main Battery Temp", "UINT", 1, 0, 1000, "°C"},
		{0x266, 2, "Main Battery Charge", "UINT", 1, 0, 100, "%"},
//#define HighPriorityCabinPressureCanId 0x280
//#define HighPriorityCabinAltitudeCanId 0x281
		{NormalPrioritySpeedBrakeControlCanId, 1, "Speedbrake Control Position", "UINT", 2, 0, 100, "%"},
		{0x301, 1, "Cowl Flaps Control Position", "UINT", 2, 0, 100, "%"},
		{0x302, 1, "Pitch Trim Control Position", "INT", 2, -100, 100, "%"},
		{0x303, 1, "Roll Trim Control Position", "INT", 2, -100, 100, "%"},
		{0x304, 1, "Yaw Trim Control Position", "INT", 2, -100, 100, "%"},
		{0x305, 1, "Collective Trim Control Position", "INT", 2, -100, 100, "%"},
		{0x306, 1, "AntiTorque Trim Control Position", "INT", 2, -100, 100, "%"},
		{NormalPrioritySpeedBrakePositionCanId, 1, "Speedbrake Position", "INT", 2, -90, 90, "°"},
		{0x381, 1, "Cowl Flaps Position", "UINT", 2, 0, 100, "%"},
		{0x382, 1, "Pitch Trim Position", "INT", 2, -90, 90, "°"},
		{0x383, 1, "Roll Trim Position", "INT", 2, -90, 90, "°"},
		{0x384, 1, "Yaw Trim Position", "INT", 2, -90, 90, "°"},

		{0x385, 1, "Pitch Trim Motor Speed", "INT", 2, -100, 100, "%"},
		{0x386, 1, "Roll Trim Motor Speed", "INT", 2, -100, 100, "%"},
		{0x387, 1, "Yaw Trim Motor Speed", "INT", 2, -100, 100, "%"},
		{0x388, 1, "Collective Trim Motor Speed", "INT", 2, -100, 100, "%"},
		{0x389, 1, "AntiTorque Trim Motor Speed", "INT", 2, -100, 100, "%"},

		{NormalPriorityLightStatusCanId, 1, "Light Status", "BYTE", 0, 0, 0, "NONE"},
		{0x38B, 1, "Fuel Pump Status", "BYTE", 0, 0, 0, "NONE"},
		{0x38C, 1, "Fuel Valve Status", "BYTE", 0, 0, 0, "NONE"},

		{0x400, 1, "Pitch Rate", "INT", 1, -3000, 3000, "°"},
		{0x401, 1, "Roll Rate", "INT", 1, -3000, 3000, "°"},
		{0x402, 1, "Yaw Rate", "INT", 1, -3000, 3000, "°"},
		{0x403, 1, "Turn Rate", "INT", 1, -3000, 3000, "°"},
		{0x404, 1, "Static Pressure", "INT", 1, -3e99, 3e99, "inHg"},
		{0x405, 1, "Pitot Pressure", "INT", 1, -3e99, 3e99, "inHg"},
		{0x406, 1, "Total Air Temperature", "INT", 2, -300, 300, "°C"},
		{0x407, 1, "Static Air Temperature", "INT", 2, -300, 300, "°C"},
		{0x408, 1, "Density Altitude", "DINT", 0, -1000, 60000, "ft"},
		{0x409, 1, "True Altitude", "DINT", 0, -1000, 60000, "ft"},

		{0x40A, 1, "Wind Speed", "UINT", 1, 0, 2000, "knots"},
		{0x40B, 1, "Wind Direction", "UINT", 2, 0, 360, "°"},
};

const struct CAN_FIX_Comms CAN_FIX_NullCommand = {0xFFFF, 0, "Bad", "Bad", 0,0,0,"Bad"};

const struct CAN_FIX_Comms* FindCanFixComms(uint16_t canId)
{
	int length = sizeof(CAN_FIX_Commands) / sizeof(CAN_FIX_Commands[0]);
	int i;
	for(i = 0; i < length; i++ )
	{
		if(CAN_FIX_Commands[i].StdId == canId)
			break;
	}
	if(i >= length)
		return &CAN_FIX_NullCommand;
	return &CAN_FIX_Commands[i];
}


void CAN_FIX_SendNodeAlarm(uint16_t alarm, uint8_t* alarmData, uint8_t alarmDataLength)
{
	if(alarmDataLength > 6)
		return;
	CAN_FIX_TxHeader.DLC = 2 + alarmDataLength;
	CAN_FIX_TxHeader.StdId = CAN_FIX_NodeId;
	ConvertUInt16ToBytes(alarm, CanFixTxData);
	memcpy(&CanFixTxData[2], alarmData, alarmDataLength);
	CanFixHw_SendMessage(&CAN_FIX_TxHeader,CanFixTxData);
}

void CAN_FIX_SendDataMessage(uint16_t canId, uint8_t index, uint8_t functionCode, uint8_t* messageData, uint8_t dataLength)
{
	//Must be less than 11 bits
	if(canId & 0xf800)
		return;
	//Message Data cannot be greater than 5
	if(dataLength > 5)
		return;
	CAN_FIX_TxHeader.StdId = canId;
	CAN_FIX_TxHeader.DLC = 3 + dataLength;
	CanFixTxData[0] = CAN_FIX_NodeId;
	CanFixTxData[1] = index;
	CanFixTxData[2] = functionCode;
	memcpy(&CanFixTxData[3], messageData, dataLength);
	CanFixHw_SendMessage(&CAN_FIX_TxHeader,CanFixTxData);
}
