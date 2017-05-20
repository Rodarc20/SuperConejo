// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Conejo.generated.h"

UCLASS()
class SUPERCONEJO_API AConejo : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AConejo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    //Cuerpo del SuperConejo
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SuperConejo")
    UStaticMeshComponent * Cuerpo;

    //Oreja derecha del SuperConejo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    UStaticMeshComponent * OrejaDerecha;

    //Oreja izquierda del SuperConejo
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SuperConejo")
    UStaticMeshComponent * OrejaIzquierda;

    //Colision del SuperConejo
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    UCapsuleComponent * Colision;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    UCameraComponent * Camara;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    float Velocidad;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    float VelocidadCaminar;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    float VelocidadCorrer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    float DistanciaCamara;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    FVector ObjetivoCamara;

    FVector Movimiento;

    FVector Rotacion;

    void MoveForward(float AxisValue);

    void MoveRight(float AxisValue);

    void RotateYaw(float AxisValue);

    void RotatePitch(float AxisValue);//este no sera necesari al comienzo

    UFUNCTION(BlueprintCallable, Category = "SuperConejo")
    void Correr();

    UFUNCTION(BlueprintCallable, Category = "SuperConejo")
    void Caminar();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    TSubclassOf<class ABolaChocolate> TipoBolaChocolate;//esto no es practio llenarlo en el cosntructor, cuando esta clase pase a bluprint sera mejor
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SuperConejo")
    FVector PuntoLanzamiento;

    UFUNCTION(BlueprintCallable, Category = "SuperConejo")
    void Lanzar();
};
