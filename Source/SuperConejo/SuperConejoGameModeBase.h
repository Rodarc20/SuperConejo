// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "SuperConejoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SUPERCONEJO_API ASuperConejoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    ASuperConejoGameModeBase();
	
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))//significa que solo se puede cambiar en el constructor
    TSubclassOf<class UUserWidget> HUDWidgetClass;  
	
    UUserWidget * WidgetActual;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    TSubclassOf<class APawn> Pawn1;  

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    TSubclassOf<class APawn> Pawn2;  
    /* Override To Read In Pawn From Custom Controller */
	UClass* GetDefaultPawnClassForController(AController* InController);
};
