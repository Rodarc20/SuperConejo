// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperConejo.h"
#include "SuperConejoGameModeBase.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"//para poder aceder a las estadisticas del juego y acceder al Chracter y trabajar con el
#include "Blueprint/UserWidget.h" 
#include "ConejoMultiplayerController.h"


ASuperConejoGameModeBase::ASuperConejoGameModeBase() {

    PrimaryActorTick.bCanEverTick = true;//esto hacia falta en el tutprial, sin esto unreal no llama a la funcion tick en cada cuadro

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Class'/Script/SuperConejo.Conejo'"));
	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
        Pawn1 = PlayerPawnBPClass.Class;
	}

    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass2(TEXT("BlueprintGeneratedClass'/Game/SuperConejo/Blueprints/Conejo/Conejo_BP.Conejo_BP_C'"));
    if (PlayerPawnBPClass2.Class != NULL) {
        Pawn2 = PlayerPawnBPClass2.Class;
    }

    PlayerControllerClass = AConejoMultiplayerController::StaticClass();
}

void ASuperConejoGameModeBase::BeginPlay() {
    Super::BeginPlay();

    if (HUDWidgetClass) {
        WidgetActual = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);//le doy el mundo sobre el que se instancia, y lo que instanciare
        if (WidgetActual) {
            WidgetActual->AddToViewport();
        }
    }

}

void ASuperConejoGameModeBase::Tick(float DeltaTime) {}

UClass* ASuperConejoGameModeBase::GetDefaultPawnClassForController(AController* InController)
{
	/* Override Functionality to get Pawn from PlayerController */
	AConejoMultiplayerController* MyController = Cast<AConejoMultiplayerController>(InController);
	if (MyController)
	{
        return MyController->GetPlayerPawnClass();
	}
 
	/* If we don't get the right Controller, use the Default Pawn */
	return DefaultPawnClass;
}