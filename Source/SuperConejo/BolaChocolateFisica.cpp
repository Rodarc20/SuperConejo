// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperConejo.h"
#include "BolaChocolateFisica.h"


ABolaChocolateFisica::ABolaChocolateFisica() {
    Fuerza = 10000.0f;
}

void ABolaChocolateFisica::BeginPlay() {
    Super::BeginPlay();

}

void ABolaChocolateFisica::Tick(float DeltaTime) {

}

void ABolaChocolateFisica::Lanzar() {
    FVector Force = GetActorForwardVector() * Fuerza;
    Bola->AddImpulse(Force, NAME_None, false);
}