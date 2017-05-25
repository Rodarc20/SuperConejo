// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BolaChocolate.generated.h"

UCLASS()
class SUPERCONEJO_API ABolaChocolate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABolaChocolate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SuperConejo")
    bool bLanzado;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SuperConejo")
    float Velocidad;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SuperConejo")
    float Poder;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SuperConejo")
    FLinearColor Color;

    UFUNCTION(BlueprintCallable, Category = "SuperConejo")
    virtual void Lanzar();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SuperConejo")
    USphereComponent * Colision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SuperConejo")
    UStaticMeshComponent * Bola;
	
	
    //colisiones
    //OnBeginOverlap, necesario que este como UFUNCTION
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};

//esta bola cuando es creada debo rotarla de tal forma que su ForawardVector que de mirando en la direccion con la que fue lanzado, esto no tiene implicaciones cuando usae fisiicas.
//de esta forma la bola viajara siempre hacia adelante,
