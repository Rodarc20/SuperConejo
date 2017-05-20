// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperConejo.h"
#include "ConejoVR.h"


// Sets default values
AConejoVR::AConejoVR()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
    VRCamera->SetupAttachment(RootComponent);//hay alugnas cosas que se le tiene que hacer a este componente, por ahora hacerlas en el blueprint

    LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
    LeftController->Hand = EControllerHand::Left;
    LeftController->SetupAttachment(RootComponent);
    LeftController->SetRelativeLocation(FVector(50.0f, -40.0f, 20.0f));

    RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
    RightController->Hand = EControllerHand::Right;
    RightController->SetupAttachment(RootComponent);
    RightController->SetRelativeLocation(FVector(50.0f, 40.0f, 20.0f));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ViveControllerAsset(TEXT("StaticMesh'/Game/ControllerSetup/vr_controller_vive_1_5.vr_controller_vive_1_5'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> ViveControllerMaterial(TEXT("Material'/Game/ControllerSetup/ControlMaterial.ControlMaterial'"));

    ViveLeftController = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ViveLeftController"));
    ViveLeftController->SetupAttachment(LeftController);
    if (ViveControllerAsset.Succeeded()) {
        ViveLeftController->SetStaticMesh(ViveControllerAsset.Object);
        if (ViveControllerMaterial.Succeeded()) {
            ViveLeftController->SetMaterial(0, ViveControllerMaterial.Object);
        }
    }
    ViveLeftController->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));

    ViveRightController = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ViveRightController"));
    ViveRightController->SetupAttachment(RightController);
    if (ViveControllerAsset.Succeeded()) {
        ViveRightController->SetStaticMesh(ViveControllerAsset.Object);
        if (ViveControllerMaterial.Succeeded()) {
            ViveRightController->SetMaterial(0, ViveControllerMaterial.Object);
        }
    }
    ViveRightController->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));

    Colision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Colision"));
    Colision->SetupAttachment(VRCamera);
    Colision->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
    Colision->InitCapsuleSize(40.0f, 80.0f);
}

// Called when the game starts or when spawned
void AConejoVR::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConejoVR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AConejoVR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

