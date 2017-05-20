// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperConejo.h"
#include "BolaChocolate.h"


// Sets default values
ABolaChocolate::ABolaChocolate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Velocidad = 2000.0f;
    Poder = 30.0f;
    Color = FLinearColor(0.082f, 0.039f, 0.012f, 1.0f);
    bLanzado = false;

    Colision = CreateDefaultSubobject<USphereComponent>(TEXT("Colision"));
    RootComponent = Colision;
    Colision->InitSphereRadius(12.5f);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BolaAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> BolaMaterial(TEXT("Material'/Game/SuperConejo/Materials/Chocolate.Chocolate'"));

    Bola = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bola"));
    Bola->SetupAttachment(RootComponent);
    Bola->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
    if (BolaAsset.Succeeded()) {
        Bola->SetStaticMesh(BolaAsset.Object);
        if (BolaMaterial.Succeeded()) {
            Bola->SetMaterial(0, BolaMaterial.Object);
        }
    }


    
}

// Called when the game starts or when spawned
void ABolaChocolate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABolaChocolate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (bLanzado) {
        SetActorLocation(GetActorLocation() + GetActorForwardVector() * Velocidad * DeltaTime);
    }

}

void ABolaChocolate::Lanzar() {// o podria recibir la direccion del lanzamiento y conservarla, y aplicarla a medida sin importar mi rotacion
    bLanzado = true;
}

