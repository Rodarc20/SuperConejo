// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trampa.generated.h"

UCLASS()
class SUPERCONEJO_API ATrampa : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrampa();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampa")
    class AObjeto* Bola0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampa")
    class AObjeto* Bola1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampa")
    class AObjeto* Bola2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampa")
    class AObjeto* Bola3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampa")
    class AObjeto* Bola4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampa")
    class AObjeto* Bola5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampa")
    class AObjeto* Bola6;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampa")
    float Distancia;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampa")
    float PhiPredeterminado;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampa")
    TSubclassOf<class AObjeto> TipoObjeto;//esto no es practio llenarlo en el cosntructor, cuando esta clase pase a bluprint sera mejor

    UFUNCTION(BlueprintCallable, Category = "Trampa")
    void CrearBolas();

    UFUNCTION(BlueprintCallable, Category = "Trampa")
    void UbicarBolas();

    FMatrix MatrizTraslacion(float x, float y, float z);

    FMatrix MatrizRotacionX(float angle);

    FMatrix MatrizRotacionY(float angle);

    FMatrix MatrizRotacionZ(float angle);

    FMatrix MulMatrix(FMatrix a, FMatrix b);

    void ImprimirMatrix(FMatrix m);

	
	
};
