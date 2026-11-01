/*
 * CanFix_Receive.c
 *
 *  Created on: Nov 1, 2026
 *      Author: oceyg
 */
#include <CanFix.h>
#include <CanFixHw.h>
#include <string.h>

void CAN_FIX_HandleCanRxMessage(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
	CAN_FIX_HandleHighPriorityNodeAlarm(rxHeader, rxData);
}


/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleHighPriorityNodeAlarm(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleHighPriorityPilotControlInput(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleHighPriorityMeasuredPosition(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleHighPriorityFlightData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleHighPriorityNavigationData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleHighPriorityEngineAircraftData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleHighPriorityAuxiliaryData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleNormalPriorityPilotControlInput(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleNormalPriorityMeasuredPosition(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleNormalPriorityFlightData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleNormalPriorityNavigationData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleNormalPriorityEngineAircraftData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleNormalPriorityAuxiliaryData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleTwoWayConnectionChannelData(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}

/* Define the default function with __weak attribute */
__weak void CAN_FIX_HandleNodeSpecificMessage(CAN_FIX_RxHeaderTypeDef* rxHeader, uint8_t* rxData)
{
    // Default empty implementation or basic logic
}
