// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo.generated.h"

UCLASS()
class SUPERCONEJO_API AEnemigo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemigo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //para modificar o hacer consas con el crear funcionces que se llamen desde blueprint
    FTimerHandle AtacarTimer;//los timers no son propiedades por eso no hay un UPROPERTY aqui

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SuperConejo")
    float SaludMaxima;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SuperConejo")
    float SaludActual;

    UFUNCTION(BlueprintCallable, Category = "SuperConejo")
    virtual void RecibirAtaque(float Poder);
	
};
