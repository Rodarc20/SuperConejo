// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperConejo.h"
#include "Conejo.h"
#include "BolaChocolate.h"


// Sets default values
AConejo::AConejo()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Velocidad = 600.0f;
    VelocidadCaminar = 600.0f;
    VelocidadCorrer = 1000.0f;

    SaludMaxima = 100.0f;
    SaludActual = SaludMaxima;

    Cuerpo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cuerpo"));
    RootComponent = Cuerpo;
    //obtenemos los objetos para los mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CapsuleAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> ConejoMaterial(TEXT("Material'/Game/SuperConejo/Materials/Chocolate.Chocolate'"));
    if (CapsuleAsset.Succeeded()) {
        Cuerpo->SetStaticMesh(CapsuleAsset.Object);
        if (ConejoMaterial.Succeeded()) {
            Cuerpo->SetMaterial(0, ConejoMaterial.Object);
        }
    }

    OrejaDerecha = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrejaDerecha"));
    OrejaDerecha->SetupAttachment(RootComponent);
    if (CapsuleAsset.Succeeded()) {
        OrejaDerecha->SetStaticMesh(CapsuleAsset.Object);
        if (ConejoMaterial.Succeeded()) {
            OrejaDerecha->SetMaterial(0, ConejoMaterial.Object);
        }
        OrejaDerecha->SetWorldScale3D(FVector(0.3f, 0.3f, 0.6f));
        OrejaDerecha->SetRelativeLocationAndRotation(FVector(-5.0f, -10.0f, 80.0f), FRotator(0.0f, 0.0f, -10.0f));
    }

    OrejaIzquierda= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrejaIzquierda"));
    OrejaIzquierda->SetupAttachment(RootComponent);
    if (CapsuleAsset.Succeeded()) {
        OrejaIzquierda->SetStaticMesh(CapsuleAsset.Object);
        if (ConejoMaterial.Succeeded()) {
            OrejaIzquierda->SetMaterial(0, ConejoMaterial.Object);
        }
        OrejaIzquierda->SetWorldScale3D(FVector(0.3f, 0.3f, 0.6f));
        OrejaIzquierda->SetRelativeLocationAndRotation(FVector(-5.0f, 10.0f, 80.0f), FRotator(0.0f, 0.0f, 10.0f));
    }

    Colision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Colision"));
    Colision->SetupAttachment(RootComponent);
    Colision->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
    Colision->InitCapsuleSize(25.0f, 70.0f);


    DistanciaCamara = 400.0f;
    ObjetivoCamara = FVector(0.0f, 0.0f, 140.0f);
    //Camara
    Camara = CreateDefaultSubobject<UCameraComponent>(TEXT("Camara"));
    Camara->SetupAttachment(RootComponent);
    FVector NewLocationCamara = FVector::ZeroVector;
    //los rotators trabajan con grados pero las funciones con radianes, lo anterior pero asi enseño dos formas de obtener lo mismo
    NewLocationCamara.X = -DistanciaCamara * FMath::Cos(FMath::DegreesToRadians(-20.0f));
    NewLocationCamara.Z = -DistanciaCamara * FMath::Sin(FMath::DegreesToRadians(-20.0f)) + ObjetivoCamara.Z;
    //FVector LocationCamara = 
    Camara->SetRelativeLocation(NewLocationCamara);//FVector(-310.f, 0.0f, 255.0f) antes se usaba ese vector a hora se calcula igual que la rotacion de la camara
    Camara->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

    PuntoLanzamiento = FVector(40.0f, 0.0f, 70.0f);
    //Busacndo la bola de chocolate, por defector, usare la clase bola de c++, podria usar la de bluprint, poner ambas aqui
    static ConstructorHelpers::FClassFinder<ABolaChocolate> BolaChocolateClass(TEXT("Class'/Script/SuperConejo.BolaChocolate'"));
    //static ConstructorHelpers::FClassFinder<ABolaChocolate> BolaChocolateClass(TEXT("BlueprintGeneratedClass'/Game/SuperConejo/Blueprints/BolasChocolate/BolaChocolate_BP.BolaChocolate_BP_C'"));
    if (BolaChocolateClass.Succeeded()) {
        if(GEngine)//no hacer esta verificación provocaba error al iniciar el editor
            GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("TipoBolaChocolate encontrado."));
        TipoBolaChocolate = BolaChocolateClass.Class;
    }
}

// Called when the game starts or when spawned
void AConejo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConejo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //tercera forma, solo para la froma de obtener los valores de los ejes
    /*Movimiento.X = GetInputAxisValue("MoveForward");
    Movimiento.Y = GetInputAxisValue("MoveRight");*/

    float MX = GetInputAxisValue("MoveForward");
    float MY = GetInputAxisValue("MoveRight");
    float CameraPitch = GetInputAxisValue("RotatePitch");

    //cuarta forma, obteniendo pero usando el input controller
    /*Movimiento.X = InputComponent->GetAxisValue("MoveForward");
    Movimiento.Y = InputComponent->GetAxisValue("MoveRight");*/

    //if (!Movimiento.IsZero()) {//facilita la comparacion, pero se deberia manejar tal cual esta ahora, masomesno, la ventaja de unreal es que te permite delegar 
    if (MX != 0.0f || MY != 0.0f) {
        //Primera forma
        /*Movimiento = Movimiento.SafeNormal() * Velocidad * DeltaTime;
        FVector NewLocation = GetActorLocation();
        NewLocation += GetActorForwardVector() * Movimiento.X;
        NewLocation += GetActorRightVector() * Movimiento.Y;
        SetActorLocation(NewLocation);*/

        //segunda forma
        /*FVector Desplazamiento = GetActorForwardVector() * Movimiento.X + GetActorRightVector() * Movimiento.Y;//reemplazar esos x , y
        SetActorLocation(GetActorLocation() + Desplazamiento.SafeNormal() * Velocidad * DeltaTime);*/

        //segunda forma
        FVector Desplazamiento = GetActorForwardVector() * MX + GetActorRightVector() * MY;//reemplazar esos x , y
        SetActorLocation(GetActorLocation() + Desplazamiento.GetSafeNormal() * Velocidad * DeltaTime);
    }
    //otra forma usando la tercerda froma de oobtener entrada, sin usar la delegacion de funciones
    //la desventaja de este forma, es que no puedo evitar calculos para como en la forma anterior
    /*FVector Desplazamiento = FVector::ZeroVector;//creo que no es necesario todo esto
    Desplazamiento += GetActorForwardVector() * GetInputAxisValue("MoveForward");
    Desplazamiento += GetActorRightVector() * GetInputAxisValue("MoveRight");
    SetActorLocation(GetActorLocation() + Desplazamiento.SafeNormal() * Velocidad * DeltaTime);*/

    if (!Rotacion.IsZero()) {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += Rotacion.X;
        SetActorRotation(NewRotation);
    }

    if (CameraPitch != 0.0f) {
        FRotator NewRotationCamara = Camara->GetRelativeTransform().GetRotation().Rotator();
        //NewRotationCamara.Pitch += CameraPitch;
        NewRotationCamara.Pitch = FMath::Clamp(NewRotationCamara.Pitch + CameraPitch, -85.0f, 5.0f);//limitando, error cuadno unso -90
        Camara->SetRelativeRotation(NewRotationCamara);
        FVector NewLocationCamara = FVector::ZeroVector;
        //los rotators trabajan con grados pero las funciones con radianes, lo anterior pero asi enseño dos formas de obtener lo mismo
        NewLocationCamara.X = -DistanciaCamara * FMath::Cos(FMath::DegreesToRadians(NewRotationCamara.Pitch));
        NewLocationCamara.Z = -DistanciaCamara * FMath::Sin(FMath::DegreesToRadians(NewRotationCamara.Pitch)) + ObjetivoCamara.Z;
        //NewLocationCamara.X = -DistanciaCamara * FMath::Cos(FMath::DegreesToRadians(Camara->GetComponentRotation().Pitch));
        //NewLocationCamara.Z = -DistanciaCamara * FMath::Sin(FMath::DegreesToRadians(Camara->GetComponentRotation().Pitch)) + 140.0f;
        Camara->SetRelativeLocation(NewLocationCamara);
    }
}

// Called to bind functionality to input
void AConejo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    //estas acciones son necesarias para decir que nos interesa acceder a los valores de estas entradas
    //Axis
    /*InputComponent->BindAxis("MoveForward", this, &AConejo::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AConejo::MoveRight);*/
    InputComponent->BindAxis("RotateYaw", this, &AConejo::RotateYaw);//delega el trato a esta funcion

    //para la tercera forma sin delegacion
    InputComponent->BindAxis("MoveForward");
    InputComponent->BindAxis("MoveRight");
    InputComponent->BindAxis("RotatePitch");

    //Actions
    InputComponent->BindAction("Correr", IE_Pressed, this, &AConejo::Correr);
    InputComponent->BindAction("Correr", IE_Released, this, &AConejo::Caminar);
    InputComponent->BindAction("Lanzar", IE_Pressed, this, &AConejo::Lanzar);

}

void AConejo::MoveForward(float AxisValue) {
    Movimiento.X = AxisValue;
}

void AConejo::MoveRight(float AxisValue) {
    Movimiento.Y = AxisValue;
}

void AConejo::RotateYaw(float AxisValue) {
    Rotacion.X = AxisValue;
}

void AConejo::Correr() {
    UE_LOG(LogClass, Log, TEXT("Corriendo"));
    if(GEngine)//no hacer esta verificación provocaba error al iniciar el editor
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Corriendo"));
    Velocidad = VelocidadCorrer;
}

void AConejo::Caminar() {
    UE_LOG(LogClass, Log, TEXT("Caminando"));
    Velocidad = VelocidadCaminar;
}

void AConejo::Lanzar() {
    UWorld * const World = GetWorld();
    if (World) {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = Instigator;
        FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * PuntoLanzamiento.X + GetActorUpVector() * PuntoLanzamiento.Z;
        ABolaChocolate * BolaChocolate = World->SpawnActor<ABolaChocolate>(TipoBolaChocolate, SpawnLocation, GetActorRotation(), SpawnParams);//recibe el punto pero del mundo, no el local, lo podemos ver como vector
        //ABolaChocolate * BolaChocolate = World->SpawnActor<ABolaChocolate>(TipoBolaChocolate, GetActorLocation() + PuntoLanzamiento, GetActorRotation(), SpawnParams);//recibe el punto pero del mundo, no el local, lo podemos ver como vector
        //ABolaChocolate * BolaChocolate = World->SpawnActor<ABolaChocolate>(TipoBolaChocolate, GetActorLocation() + GetTransform().InverseTransformPostion(PuntoLanzamiento), GetActorRotation(), SpawnParams);//recibe el punto pero del mundo, no el local, lo podemos ver como vector
        if(BolaChocolate)
            BolaChocolate->Lanzar();
    }

}

void AConejo::RecibirAtaque(float Poder) {
    SaludActual = FMath::Clamp(SaludActual - Poder, 0.0f, SaludMaxima);
}