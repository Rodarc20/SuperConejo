// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperConejo.h"
#include "SuperConejoGameModeBase.h"
#include "Kismet/GameplayStatics.h"//para poder aceder a las estadisticas del juego y acceder al Chracter y trabajar con el
#include "Blueprint/UserWidget.h" 


ASuperConejoGameModeBase::ASuperConejoGameModeBase() {

    PrimaryActorTick.bCanEverTick = true;//esto hacia falta en el tutprial, sin esto unreal no llama a la funcion tick en cada cuadro

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Class'/Script/SuperConejo.Conejo'"));
	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
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