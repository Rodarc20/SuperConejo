// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "ConejoVR.generated.h"

UCLASS()
class SUPERCONEJO_API AConejoVR : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AConejoVR();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    UCameraComponent * VRCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    UMotionControllerComponent * LeftController;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    UMotionControllerComponent * RightController;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    UStaticMeshComponent * ViveLeftController;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    UStaticMeshComponent * ViveRightController;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    UCapsuleComponent * Colision;//hijo de vrcamera
};
