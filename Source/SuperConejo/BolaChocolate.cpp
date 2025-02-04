// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperConejo.h"
#include "BolaChocolate.h"
#include "Conejo.h"
#include "Enemigo.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ABolaChocolate::ABolaChocolate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Velocidad = 2000.0f;
    Poder = 30.0f;
    Color = FLinearColor(0.082f, 0.039f, 0.012f, 1.0f);
    bLanzado = false;

    /*Colision = CreateDefaultSubobject<USphereComponent>(TEXT("Colision"));
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
    }*/



    static ConstructorHelpers::FObjectFinder<UStaticMesh> BolaAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> BolaMaterial(TEXT("Material'/Game/SuperConejo/Materials/Chocolate.Chocolate'"));

    Bola = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bola"));
    RootComponent = Bola;
    Bola->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
    if (BolaAsset.Succeeded()) {
        Bola->SetStaticMesh(BolaAsset.Object);
        if (BolaMaterial.Succeeded()) {
            Bola->SetMaterial(0, BolaMaterial.Object);
        }
    }
    Bola->SetCollisionProfileName(TEXT("Custom"));
    Bola->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Bola->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    Bola->OnComponentBeginOverlap.AddDynamic(this, &ABolaChocolate::OnBeginOverlap);

    Colision = CreateDefaultSubobject<USphereComponent>(TEXT("Colision"));
    Colision->SetupAttachment(RootComponent);
    Colision->InitSphereRadius(12.5f);


    EfectoImpacto = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EfectoImpacto"));
    EfectoImpacto->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UParticleSystem> EfectoImpactoAsset(TEXT("ParticleSystem'/Game/SuperConejo/ParticleSystems/ImpactoChocolate.ImpactoChocolate'"));
    if (EfectoImpactoAsset.Succeeded()) {
        EfectoImpacto->SetTemplate(EfectoImpactoAsset.Object);
    }
    EfectoImpacto->SetRelativeLocation(FVector::ZeroVector);

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
    //de esta forma si funciones, lo que no funciones es le delegate
    /*TArray<AActor *> OverlappedActors;
    Bola->GetOverlappingActors(OverlappedActors);
    for (int i = 0; i < OverlappedActors.Num(); i++) {
        if (OverlappedActors[i] != nullptr && OverlappedActors[i] != this) {
            if(GEngine)//no hacer esta verificación provocaba error al iniciar el editor
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Overlap"));
            Destroy();
        }
    }*/

}

void ABolaChocolate::Lanzar() {// o podria recibir la direccion del lanzamiento y conservarla, y aplicarla a medida sin importar mi rotacion
    bLanzado = true;
}

//OnBeginOverlap
//no debe destruirse con el conejo
void ABolaChocolate::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
    //verificar que el actor que inicia el solapamiento no sea si mismo con otro componente, y que no sea nulo 
    if ( (OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner())) { //no es necesario el ultimo, solo para este caso particular en el que no quiero que el propio conejo active esta funconalidad
        if(GEngine)//no hacer esta verificación provocaba error al iniciar el editor
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Overlap"));
        AEnemigo * const Animal = Cast<AEnemigo>(OtherActor);
        if (Animal && !Animal->IsPendingKill()) {
            UStaticMeshComponent * const CuerpoAnimal = Cast<UStaticMeshComponent>(OtherComp);
            if(CuerpoAnimal){
                Animal->RecibirAtaque(Poder, GetActorLocation());
                Destroy();
            }
        }
        else {
            EfectoImpacto->Activate(false);
            EfectoImpacto->SetRelativeLocation(GetActorLocation());
            EfectoImpacto->Activate(true);
            UWorld * const World = GetWorld();
            if (World) {
                UGameplayStatics::SpawnEmitterAtLocation(World, EfectoImpacto->Template, FTransform(FRotator::ZeroRotator, GetActorLocation()));
            }
            Destroy();
        }
    }
}

