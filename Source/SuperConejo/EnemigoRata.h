// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoRata.generated.h"

/**
 * 
 */
UCLASS()
class SUPERCONEJO_API AEnemigoRata : public AEnemigo
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemigoRata();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //Cuerpo del SuperConejo
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimalesRaros")
    UStaticMeshComponent * Cuerpo;

    //Oreja derecha del SuperConejo
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimalesRaros")
    UStaticMeshComponent * OrejaDerecha;

    //Oreja izquierda del SuperConejo
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimalesRaros")
    UStaticMeshComponent * OrejaIzquierda;

    //Colision del SuperConejo
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimalesRaros")
    UCapsuleComponent * Colision;
	
	
	
};
