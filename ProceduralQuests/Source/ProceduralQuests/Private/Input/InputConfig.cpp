// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig.h"

UInputAction* UInputConfig::GetMoveForwardInput()
{
	return InputMoveForward;
}

UInputAction* UInputConfig::GetMoveRightInput()
{
	return InputMoveRight;
}

UInputAction* UInputConfig::GetLookInput()
{
	return InputLook;
}

UInputAction* UInputConfig::GetQuestRequestInput()
{
	return InputRequestQuest;
}
