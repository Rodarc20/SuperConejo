// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperConejo.h"
#include "Objeto.h"


// Sets default values
AObjeto::AObjeto()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BolaAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> BolaMaterial(TEXT("Material'/Game/SuperConejo/Materials/Chocolate.Chocolate'"));

    Bola = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bola"));
    RootComponent = Bola;
    Bola->SetWorldScale3D(FVector(0.10f, 0.10f, 0.10f));
    if (BolaAsset.Succeeded()) {
        Bola->SetStaticMesh(BolaAsset.Object);
        if (BolaMaterial.Succeeded()) {
            Bola->SetMaterial(0, BolaMaterial.Object);
        }
    }
}

// Called when the game starts or when spawned
void AObjeto::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjeto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

