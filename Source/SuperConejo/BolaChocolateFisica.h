// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BolaChocolate.h"
#include "BolaChocolateFisica.generated.h"

/**
 * 
 */
UCLASS()
class SUPERCONEJO_API ABolaChocolateFisica : public ABolaChocolate
{
	GENERATED_BODY()

public:
    ABolaChocolateFisica();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
	
    virtual void Lanzar() override;

    float Fuerza;
	
	
};
