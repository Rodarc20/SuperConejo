// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objeto.generated.h"

UCLASS()
class SUPERCONEJO_API AObjeto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjeto();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SuperConejo")
    UStaticMeshComponent * Bola;

    double X;
    double Y;
    double Z;
    double Phi;
    double Theta;
	
	
};
