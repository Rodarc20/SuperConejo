// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperConejo.h"
#include "EnemigoRata.h"

AEnemigoRata::AEnemigoRata() {

    Cuerpo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cuerpo"));
    RootComponent = Cuerpo;
    //obtenemos los objetos para los mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CapsuleAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> ConejoMaterial(TEXT("Material'/Game/SuperConejo/Materials/PeloRata.PeloRata'"));
    if (CapsuleAsset.Succeeded()) {
        Cuerpo->SetStaticMesh(CapsuleAsset.Object);
        if (ConejoMaterial.Succeeded()) {
            Cuerpo->SetMaterial(0, ConejoMaterial.Object);
        }
    }

    OrejaDerecha = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrejaDerecha"));
    OrejaDerecha->SetupAttachment(RootComponent);
    if (SphereAsset.Succeeded()) {
        OrejaDerecha->SetStaticMesh(SphereAsset.Object);
        if (ConejoMaterial.Succeeded()) {
            OrejaDerecha->SetMaterial(0, ConejoMaterial.Object);
        }
        OrejaDerecha->SetWorldScale3D(FVector(0.15f, 0.35f, 0.35f));
        OrejaDerecha->SetRelativeLocationAndRotation(FVector(-5.0f, -20.0f, 102.0f), FRotator(0.0f, 0.0f, 0.0f));
    }

    OrejaIzquierda = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrejaIzquierda"));
    OrejaIzquierda->SetupAttachment(RootComponent);
    if (SphereAsset.Succeeded()) {
        OrejaIzquierda->SetStaticMesh(SphereAsset.Object);
        if (ConejoMaterial.Succeeded()) {
            OrejaIzquierda->SetMaterial(0, ConejoMaterial.Object);
        }
        OrejaIzquierda->SetWorldScale3D(FVector(0.15f, 0.35f, 0.35f));
        OrejaIzquierda->SetRelativeLocationAndRotation(FVector(-5.0f, 20.0f, 102.0f), FRotator(0.0f, 0.0f, 0.0f));
    }


}


void AEnemigoRata::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemigoRata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
