/*
 * CanFix_Send.c
 *
 *  Created on: Nov 1, 2026
 *      Author: oceyg
 */
#include <CanFix.h>
#include <CanFixHw.h>
#include <string.h>



void CAN_FIX_SendHighPriorityKeyPress( PilotLocationTypedef pilot, uint8_t index, uint8_t functionCode, uint8_t key, uint8_t altFunction)
{
	uint16_t canId = HighPriorityKeypadKeyControlCanId_0;
	const struct CAN_FIX_Comms* comms = FindCanFixComms(canId);
	//Verify comms did not return null: StdId = 0xFFFF
	if(comms->StdId == 0xFFFF)
		return;
	//Verify the element argument is not greater than the possible
	//elements
	if(pilot >= comms->Count)
		return;
	canId += pilot;

	uint8_t data[2];
	data[0] = key;
	data[1] = altFunction;
	CAN_FIX_SendDataMessage(canId, index, functionCode, data, 2);
}

//This function is used by several functions below to convert float data to bytes
//The operation shifts the data to the left given the precision given,
void CAN_FIX_SendFloatMeasurement(const struct CAN_FIX_Comms* comms, uint16_t canId, uint8_t index, uint8_t functionCode, float floatData)
{
	//Validate input data
	if((floatData < comms->LowLimit) ||
	   (floatData > comms->HighLimit))
		return;

	uint8_t data[sizeof(float)];
	int exp = 10^(comms->Precision);
	int bytes = 0;

	if ((strcmp(comms->DataType, "CHAR") == 0)||
			(strcmp(comms->DataType, "BYTE") == 0) ||
			(strcmp(comms->DataType, "USHORT") == 0))
	{
		data[0] = (uint8_t)(floatData * exp);
		bytes = sizeof(uint8_t);
	}
	else if (strcmp(comms->DataType, "SHORT") == 0)
	{
		data[0] = (int8_t)(floatData * exp);
		bytes = sizeof(uint8_t);
	}
	else if (strcmp(comms->DataType, "INT") == 0)
	{
		int16_t integer16 = (int16_t)(floatData * exp);
		ConvertInt16ToBytes(integer16, data);
		bytes = sizeof(int16_t);
	}
	else if (strcmp(comms->DataType, "UINT") == 0)
	{
		uint16_t uinteger16 = (uint16_t)(floatData * exp);
		ConvertUInt16ToBytes(uinteger16, data);
		bytes = sizeof(uint16_t);
	}
	//Note Precision is lost with this... the float
	//cannot handle this large of a number with good accuracy
	//Use a different function to handle this case
	else if (strcmp(comms->DataType, "DINT") == 0)
	{
		int32_t integer32 = (int32_t)(floatData * exp);
		ConvertInt32ToBytes(integer32, data);
		bytes = sizeof(uint32_t);
	}
	//Note Precision is lost with this... the float
	//cannot handle this large of a number with good accuracy
	//Use a different function to handle this case
	else if (strcmp(comms->DataType, "UDINT") == 0)
	{
		uint32_t uinteger32 = (uint32_t)(floatData * exp);
		ConvertUInt32ToBytes(uinteger32, data);
		bytes = sizeof(uint32_t);
	}
	else if (strcmp(comms->DataType, "FLOAT") == 0)
	{
		floatData = floatData * exp;
		ConvertFloatToBytes(floatData, data);
		bytes = sizeof(uint32_t);
	}
	else //Data Type unknown
		return;

	CAN_FIX_SendDataMessage(canId, index, functionCode, data, bytes);
}


void CAN_FIX_SendControlAngle(ControlSurfaceMeasurementsTypedef surface, float angle, uint8_t index, AttitudeAngleTypedef metaData )
{
	uint16_t canId;
	switch(surface)
	{
	case ControlSurfaceMeasurement_Elevator:
		canId = HighPriorityElevatorMeasurementCanId;
		break;
	case ControlSurfaceMeasurement_Aileron:
		canId = HighPriorityAileronMeasurementCanId;
		break;
	case ControlSurfaceMeasurement_Rudder:
		canId = HighPriorityRudderMeasurementCanId;
		break;
	case ControlSurfaceMeasurement_Collective:
		canId = HighPriorityCollectiveMeasurementCanId;
		break;
	case ControlSurfaceMeasurement_TailRotor:
		canId = HighPriorityTailRotorMeasurementCanId;
		break;
	case ControlSurfaceMeasurement_Flaps:
		canId = HighPriorityFlapMeasurementCanId;
		break;
	default:
		return;
	}
	const struct CAN_FIX_Comms* comms = FindCanFixComms(canId);
	//Verify comms did not return null: StdId = 0xFFFF
	if(comms->StdId == 0xFFFF)
		return;
	//Verify the element argument is not greater than the possible
	//elements

	CAN_FIX_SendFloatMeasurement(comms, canId, index, metaData, angle);
}


void CAN_FIX_SendHighPriorityRPM (RpmTypedef device, uint8_t engine, float rpm, uint8_t index, RpmMetadataTypedef metaData )
{
	uint16_t canId;
	switch(device)
	{
	case EngineRpm:
		canId = HighPriorityEngineRPMCanId_0;
		break;
	case PropRpm:
		canId = HighPriorityPropRPMCanId_0;
		break;
	default:
		return;
	}

	const struct CAN_FIX_Comms* comms = FindCanFixComms(canId);
	//Verify comms did not return null: StdId = 0xFFFF
	if(comms->StdId == 0xFFFF)
		return;
	//Verify the element argument is not greater than the possible
	//elements
	if(engine >= comms->Count)
		return;
	canId += engine;
	CAN_FIX_SendFloatMeasurement(comms, canId, index, metaData, rpm);
}

void CAN_FIX_SendNormalPilotControlInput (PilotControlInputTypedef sensor, float value, uint8_t index, RpmMetadataTypedef metaData )
{
	if(sensor < 0 || sensor >= PilotControlMaxValue)
		return;
	if(value < -100 || value > 100)
		return;
	uint16_t canId = sensor + NormalPrioritySpeedBrakeControlCanId;
	const struct CAN_FIX_Comms* comms = FindCanFixComms(canId);
	//Verify comms did not return null: StdId = 0xFFFF
	if(comms->StdId == 0xFFFF)
		return;
	//Verify the element argument is not greater than the possible
	//elements
	if(sensor >= comms->Count)
		return;
	canId += sensor;
	CAN_FIX_SendFloatMeasurement(comms, canId, index, metaData, value);
}


//
//Subset is a number between 0 and 3 corresponding to the number of systems on the aircraft
void CAN_FIX_SendNormalMeasuredPositions(NormalPositionMeasurementsTypedef sensor, float value, uint8_t index, RpmMetadataTypedef metaData )
{
	if(sensor < 0 || sensor >= MesuredPositionsMaxValue)
		return;
	if(value < -100 || value > 100)
		return;
	uint16_t canId = sensor + NormalPrioritySpeedBrakePositionCanId;
	const struct CAN_FIX_Comms* comms = FindCanFixComms(canId);
	//Verify comms did not return null: StdId = 0xFFFF
	if(comms->StdId == 0xFFFF)
		return;
	//Verify the element argument is not greater than the possible
	//elements
	if(sensor >= comms->Count)
		return;
	canId += sensor;
	CAN_FIX_SendFloatMeasurement(comms, canId, index, metaData, value);
}

void CAN_FIX_SendNormalStatus (NormalStatusTypedef sensor, uint8_t value, uint8_t index, uint8_t metaData )
{
	if(sensor < 0 || sensor >= NormalStatusMaxValue)
		return;

	uint16_t canId = sensor +  NormalPriorityLightStatusCanId;

	CAN_FIX_SendDataMessage(canId, index, metaData, &value, sizeof(uint8_t));
}

//Subset is a number between 0 and 3 corresponding to the number of systems on the aircraft
void CAN_FIX_SendHighPrioritySensorReading (SystemSensorTypedef sensor, uint8_t subset, float value, uint8_t index, RpmMetadataTypedef metaData )
{
	if(sensor < 0 || sensor >= SystemSensorMaxValue)
		return;
	if(subset < 0 || subset > 3)
		return;
	uint16_t canId = sensor * 4 + subset + HighPriorityFuelFlowCanId_0;
	const struct CAN_FIX_Comms* comms = FindCanFixComms(canId);
	//Verify comms did not return null: StdId = 0xFFFF
	if(comms->StdId == 0xFFFF)
		return;
	//Verify the element argument is not greater than the possible
	//elements
	if(subset >= comms->Count)
		return;
	canId += subset;

	CAN_FIX_SendFloatMeasurement(comms, canId, index, metaData, value);
}

void CAN_FIX_SendLandingGearControl(PilotLocationTypedef device, LandingGearTypedef button)
{
	uint16_t canId = HighPriorityLandingGearControlSwitchCanId_0;
	const struct CAN_FIX_Comms* comms = FindCanFixComms(canId);
	//Verify comms did not return null: StdId = 0xFFFF
	if(comms->StdId == 0xFFFF)
		return;
	//Verify the element argument is not greater than the possible
	//elements
	if(device >= comms->Count)
		return;
	canId += device;
	CAN_FIX_SendDataMessage(canId, 0, 0, &button, 1);
}

void CAN_FIX_SendControlSwitch(ControlSwitchTypedef control, PilotLocationTypedef location,  uint8_t index, uint8_t functionCode, uint8_t button)
{
	uint16_t canId;
	switch(control)
	{
	case FlapControlSwitches: //100
		canId = HighPriorityFlapControlSwitchCanId_0;
		break;
	case TrimControlSwitches: //102
		canId = HighPriorityTrimControlSwitchCanId_0;
		break;
	case ElectricalBusControlSwitches: //104
		canId = HighPriorityElectricalControlSwitchCanId_0;
	    break;
	case LightingControlSwitches:  //106
		canId = HighPriorityLightingControlSwitchCanId_0;
		break;
	case FuelPumpControlSwitches: //108
		canId = HighPriorityFuelPumpControlSwitchCanId_0;
		break;
	case FuelValveControlSwitches: //10A
		canId = HighPriorityFuelValveControlSwitchCanId_0;
		break;
	case AutoPilotControlSwitches:     //10C
		canId = HighPriorityAutoPilotControlSwitchCanId_0;
		break;
	case VhfControlSwitches:    //10E
		canId = HighPriorityVHFControlSwitchCanId_0;
		break;
	case TransponderControlSwitches:   //110
		canId = HighPriorityTransponderControlSwitchCanId_0;
		break;
	case StarterMagnetoControlSwitches:  //112
		canId = HighPriorityStarterMagsControlSwitchCanId_0;
		break;
	case LandingGearControlSwitches:    //114
		canId = HighPriorityLandingGearControlSwitchCanId_0;
		break;
	case GenericControlSwitches:       //118
		canId = HighPriorityGenericControlSwitchCanId_0;
		break;
	}


	CAN_FIX_SendDataMessage(canId, index, functionCode, &button, 1);
}

void CAN_FIX_SendControlLeverPosition(ControlLeverTypedef lever, uint8_t element, float position, uint8_t index )
{
	uint16_t canId;
	switch(lever)
	{
	case ControlLever_LeftBrake:
		canId = HighPriorityLeftBrakeControlCanId; //120
		break;
	case ControlLever_RightBrake:
		canId = HighPriorityRightBrakeControlCanId; //121
		break;
	case ControlLever_EngineThrottle:
		canId = HighPriorityEngineThrottleControlCanId_0; //122
		break;
	case ControlLever_EngineProp:
		canId = HighPriorityEnginePropControlCanId_0; //126
		break;
	case ControlLever_EngineMixture:
		canId = HighPriorityEngineMixtureControlCanId_0; //12A
		break;
	default:
		return;
	}
	const struct CAN_FIX_Comms* comms = FindCanFixComms(canId);
	//Verify comms did not return null: StdId = 0xFFFF
	if(comms->StdId == 0xFFFF)
		return;
	//Verify the element argument is not greater than the possible
	//elements
	if(element >= comms->Count)
		return;
	canId += element;
	CAN_FIX_SendFloatMeasurement(comms, canId, index, 0, position);
}

void CAN_FIX_SendIndicatorSwitch(IndicatorSwitchTypedef indicator, PilotLocationTypedef location,  uint8_t index, uint8_t functionCode, uint8_t button)
{
	uint16_t canId;
	switch(indicator)
	{
	case LandingGearPositionIndicatorSwitch:
		canId = HighPriorityLandingGearPositionSwCanId;
		break;
	case FuelPressureIndicatorSwitch: //218
		canId = HighPriorityFuelPressureSwitchCanId_0;
		break;
	case OilPressureIndicatorSwitch: //21C
		canId = HighPriorityOilPressureSwitchCanId_0;
		break;
	case OilTemperatureIndicatorSwitch: //220
		canId = HighPriorityOilTemperatureSwitchCanId_0;
		break;
	case CoolantTemperatureIndicatorSwitch: //224
		canId = HighPriorityCoolantTemperatureSwitchCanId_0;
		break;
	case FuelQuantityIndicatorSwitch: //228
		canId = HighPriorityFuelQuantitySwitchCanId_0;
		break;
	case OilQuantityIndicatorSwitch: //22C
		canId = HighPriorityOilQuantitySwitchCanId_0;
		break;
	case CoolantQuantityIndicatorSwitch: //230
		canId = HighPriorityCoolantQuantitySwitchCanId_0;
		break;
	}


	CAN_FIX_SendDataMessage(canId, index, functionCode, &button, 1);
}

void CAN_FIX_SendHighPriorityPressureSwitch (EngineFluidSwitchTypedef sensor,uint8_t subset, SwitchValueTypedef value, uint8_t index, uint8_t metaData )
{
	if(sensor < 0 || sensor >= SystemMaxValue)
		return;
	if(subset < 0 || subset > 3)
		return;
	uint16_t canId = sensor * 4 + subset +  HighPriorityFuelPressureSwitchCanId_0;

	uint8_t data;
	memcpy(&data,&value,sizeof(int8_t));
	CAN_FIX_SendDataMessage(canId, index, metaData, &data, sizeof(int8_t));
}

void CAN_FIX_SendHighPriorityTurbineTemp (TurbineTempTypedef device, uint8_t engine, float temp, uint8_t index, RpmMetadataTypedef metaData )
{
	uint16_t canId;
	switch(device)
	{
	case InletTemp:
		canId = HighPriorityTurbineInletTempCanId_0;
		break;
	case InterTemp:
		canId = HighPriorityTurbineInterTempCanId_0;
		break;
	case OutletTemp:
		canId = HighPriorityTurbineOutletTempCanId_0;
		break;
	default:
		return;
	}

	const struct CAN_FIX_Comms* comms = FindCanFixComms(canId);
	//Verify comms did not return null: StdId = 0xFFFF
	if(comms->StdId == 0xFFFF)
		return;
	//Verify the element argument is not greater than the possible
	//elements
	if(engine >= comms->Count)
		return;
	canId += engine;
	CAN_FIX_SendFloatMeasurement(comms, canId, index, metaData, temp);
}

void CAN_FIX_SendHighPriorityTorque (uint8_t engine, float torque, uint8_t index, RpmMetadataTypedef metaData )
{

	uint16_t canId = HighPriorityTorqueCanId_0;
	const struct CAN_FIX_Comms* comms = FindCanFixComms(canId);
	//Verify comms did not return null: StdId = 0xFFFF
	if(comms->StdId == 0xFFFF)
		return;
	//Verify the element argument is not greater than the possible
	//elements
	if(engine >= comms->Count)
		return;
	canId += engine;
	CAN_FIX_SendFloatMeasurement(comms, canId, index, metaData, torque);
}
void CAN_FIX_SendNodeSpecificMessage(void)
{

}

void CAN_FIX_SendTwoWayCommunication(uint8_t channel, int8_t sender, uint8_t* data)
{

}
