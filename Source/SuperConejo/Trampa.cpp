// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperConejo.h"
#include "Trampa.h"
#include "Objeto.h"


// Sets default values
ATrampa::ATrampa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FClassFinder<AObjeto> BolaClass(TEXT("BlueprintGeneratedClass'/Game/SuperConejo/Blueprints/Trampas/Objeto_BP.Objeto_BP_C'"));
    if (BolaClass.Succeeded()) {
        if(GEngine)//no hacer esta verificación provocaba error al iniciar el editor
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("TipoObjeto encontrado."));
        TipoObjeto= BolaClass.Class;
    }

    Distancia = 100.0f;
    PhiPredeterminado = PI / 4;
    
}

// Called when the game starts or when spawned
void ATrampa::BeginPlay() {
	Super::BeginPlay();

    CrearBolas();
    UbicarBolas();
}

// Called every frame
void ATrampa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrampa::CrearBolas() {
    UWorld * const World = GetWorld();
    if (World) {//este if deberia estar afuera
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = Instigator;

        FVector SpawnLocation(1.0f, 1.0f, 1.0f);//ejes invertidos a los recibidos, esto tal vez deba ser la posicion relaitva, no la general
        SpawnLocation = GetTransform().TransformPosition(SpawnLocation);
        FRotator SpawnRotation(0.0f, 0.0f, 0.0f);

        Bola0 = World->SpawnActor<AObjeto>(TipoObjeto, SpawnLocation, SpawnRotation, SpawnParams);//creo que es mejor si yo hago los calculos de los angulos, para generar el rotator
        if(Bola0)
            Bola0->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
        Bola1 = World->SpawnActor<AObjeto>(TipoObjeto, SpawnLocation + FVector(20.0f), SpawnRotation, SpawnParams);//creo que es mejor si yo hago los calculos de los angulos, para generar el rotator
        //Bola1 = World->SpawnActor<AObjeto>(TipoObjeto, FVector(5.0f), SpawnRotation, SpawnParams);//creo que es mejor si yo hago los calculos de los angulos, para generar el rotator
        if(Bola1)
            Bola1->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
        Bola2 = World->SpawnActor<AObjeto>(TipoObjeto, SpawnLocation + FVector(40.0f), SpawnRotation, SpawnParams);//creo que es mejor si yo hago los calculos de los angulos, para generar el rotator
        if(Bola2)
            Bola2->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
        Bola3 = World->SpawnActor<AObjeto>(TipoObjeto, SpawnLocation + FVector(60.0f), SpawnRotation, SpawnParams);//creo que es mejor si yo hago los calculos de los angulos, para generar el rotator
        if(Bola3)
            Bola3->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
        Bola4 = World->SpawnActor<AObjeto>(TipoObjeto, SpawnLocation + FVector(80.0f), SpawnRotation, SpawnParams);//creo que es mejor si yo hago los calculos de los angulos, para generar el rotator
        if(Bola4)
            Bola4->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
        Bola5 = World->SpawnActor<AObjeto>(TipoObjeto, SpawnLocation + FVector(100.0f), SpawnRotation, SpawnParams);//creo que es mejor si yo hago los calculos de los angulos, para generar el rotator
        if(Bola5)
            Bola5->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
        Bola6 = World->SpawnActor<AObjeto>(TipoObjeto, SpawnLocation + FVector(120.0f), SpawnRotation, SpawnParams);//creo que es mejor si yo hago los calculos de los angulos, para generar el rotator
        if(Bola6)
            Bola6->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
    }

}

void ATrampa::UbicarBolas() {
    //la bola 0 al medio, la bola 1 y 2 hijas de 0, la bola 3 hija de 1
    Bola0->SetActorRelativeLocation(FVector(0.0f));
    float PhiInicial = PI/6;
    float ThetaInicial = 0;
    float DeltaTheta = PI;
    Bola1->X = 25.0f * FMath::Sin(PhiPredeterminado) * FMath::Sin(ThetaInicial);
    Bola1->Y = 25.0f * FMath::Sin(PhiPredeterminado) * FMath::Cos(ThetaInicial);
    Bola1->Z = 25.0f * FMath::Cos(PhiPredeterminado);
    Bola1->SetActorRelativeLocation(FVector(Bola1->X, Bola1->Y, Bola1->Z));

    Bola2->X = 25.0f * FMath::Sin(PhiPredeterminado) * FMath::Sin(ThetaInicial + PI);
    Bola2->Y = 25.0f * FMath::Sin(PhiPredeterminado) * FMath::Cos(ThetaInicial + PI);
    Bola2->Z = 25.0f * FMath::Cos(PhiPredeterminado);
    Bola2->SetActorRelativeLocation(FVector(Bola2->X, Bola2->Y, Bola2->Z));


    FVector DesplazamientoBola1 = GetTransform().InverseTransformPosition(Bola1->GetActorTransform().GetLocation()) - GetTransform().InverseTransformPosition(Bola0->GetActorTransform().GetLocation());
    //me da la direccion , deberia poder sacar los angulos con esto
    //esta perfecto pero debo trabajr con esta direccion, y obtener los angulos respectivos
    //esto es respecto al padre, pero deberia haber otro respecto al origen, para solo hacer el desplzadamiento, es decir, un vector mas que sea la posicion de Bolao (O), que hay que aplicar al calculo final
    FMatrix RotX = MatrizRotacionX(2*PI - PhiPredeterminado);

    FMatrix RotZ = FMatrix::Identity;//en este caso la matriz z es la identidad por que theta de V es 0 y eso al realziar calculos es la matriz identdad;

    FMatrix TraslacionV = MatrizTraslacion(Bola1->X, Bola1->Y, Bola1->Z);

    FMatrix oHv = MulMatrix(TraslacionV, RotX);//deberia multiplicar tambine por Rotz, pero como es la identidad no importa


    Bola4->X = 16.0f * FMath::Sin(PhiPredeterminado) * FMath::Sin(ThetaInicial + PI);
    Bola4->Y = 16.0f * FMath::Sin(PhiPredeterminado) * FMath::Cos(ThetaInicial + PI);
    Bola4->Z = 16.0f * FMath::Cos(PhiPredeterminado);
    Bola4->SetActorRelativeLocation(FVector(Bola4->X, Bola4->Y, Bola4->Z));
    //hasta auqi han sido ubicados como si su nodo padre estuviera en O en el 0,0,0

    FMatrix TraslacionB = MatrizTraslacion(Bola4->X, Bola4->Y, Bola4->Z);

    RotZ = MatrizRotacionZ(PI);
    RotX = MatrizRotacionX(PhiPredeterminado);

    FMatrix vHb = MulMatrix(MulMatrix(TraslacionB, RotX), RotZ);

    UE_LOG(LogClass, Log, TEXT("oHv"))
    ImprimirMatrix(oHv);

    UE_LOG(LogClass, Log, TEXT("vHb"));
    ImprimirMatrix(vHb);

    FMatrix oHb = MulMatrix(oHv, vHb);

    UE_LOG(LogClass, Log, TEXT("oHb"));
    ImprimirMatrix(oHb);

    Bola4->SetActorRelativeLocation(FVector(oHb.M[0][3],oHb.M[1][3],oHb.M[2][3]));

    float Twist = PI / 2;

    Bola3->X = 16.0f * FMath::Sin(PhiPredeterminado) * FMath::Sin(ThetaInicial);
    Bola3->Y = 16.0f * FMath::Sin(PhiPredeterminado) * FMath::Cos(ThetaInicial);
    Bola3->Z = 16.0f * FMath::Cos(PhiPredeterminado);
    Bola3->SetActorRelativeLocation(FVector(Bola3->X, Bola3->Y, Bola3->Z));

    FMatrix TraslacionC = MatrizTraslacion(Bola3->X, Bola3->Y, Bola3->Z);

    FMatrix vHc = MulMatrix(TraslacionC, RotX);

    UE_LOG(LogClass, Log, TEXT("oHv"));
    ImprimirMatrix(oHv);

    UE_LOG(LogClass, Log, TEXT("vHc"));
    ImprimirMatrix(vHc);

    FMatrix oHc = MulMatrix(oHv, vHc);

    UE_LOG(LogClass, Log, TEXT("oHc"));
    ImprimirMatrix(oHc);

    Bola3->SetActorRelativeLocation(FVector(oHc.M[0][3],oHc.M[1][3],oHc.M[2][3]));

    //el ejemplo de la bola 5 es importante
    //calculo en espacion respcto a bola4
    Bola5->X = 9.0f * FMath::Sin(PhiPredeterminado) * FMath::Sin(ThetaInicial);
    Bola5->Y = 9.0f * FMath::Sin(PhiPredeterminado) * FMath::Cos(ThetaInicial);
    Bola5->Z = 9.0f * FMath::Cos(PhiPredeterminado);
    Bola5->SetActorRelativeLocation(FVector(Bola5->X, Bola5->Y, Bola5->Z));
    FMatrix TraslacionE = MatrizTraslacion(Bola5->X, Bola5->Y, Bola5->Z);
    RotX = MatrizRotacionX(2*PI - PhiPredeterminado);

    RotZ = FMatrix::Identity;//en este caso la matriz z es la identidad por que theta de V es 0 y eso al realziar calculos es la matriz identdad;

    FMatrix bHe = MulMatrix(TraslacionE, RotX);//deberia multiplicar tambine por Rotz, pero como es la identidad no importa
    FMatrix oHe = MulMatrix(oHb, bHe);

    UE_LOG(LogClass, Log, TEXT("oHb"))
    ImprimirMatrix(oHb);

    UE_LOG(LogClass, Log, TEXT("bHe"));
    ImprimirMatrix(bHe);

    UE_LOG(LogClass, Log, TEXT("oHe"));
    ImprimirMatrix(oHe);
    Bola5->SetActorRelativeLocation(FVector(oHe.M[0][3],oHe.M[1][3],oHe.M[2][3]));


    Bola6->X = 9.0f * FMath::Sin(PhiPredeterminado) * FMath::Sin(ThetaInicial + PI);
    Bola6->Y = 9.0f * FMath::Sin(PhiPredeterminado) * FMath::Cos(ThetaInicial + PI);
    Bola6->Z = 9.0f * FMath::Cos(PhiPredeterminado);
    Bola6->SetActorRelativeLocation(FVector(Bola6->X, Bola6->Y, Bola6->Z));
    FMatrix TraslacionF = MatrizTraslacion(Bola6->X, Bola6->Y, Bola6->Z);
    RotX = MatrizRotacionX(PhiPredeterminado);

    RotZ = FMatrix::Identity;//en este caso la matriz z es la identidad por que theta de V es 0 y eso al realziar calculos es la matriz identdad;

    FMatrix bHf = MulMatrix(TraslacionF, RotX);//deberia multiplicar tambine por Rotz, pero como es la identidad no importa
    FMatrix oHf = MulMatrix(oHb, bHf);

    UE_LOG(LogClass, Log, TEXT("oHb"))
    ImprimirMatrix(oHb);

    UE_LOG(LogClass, Log, TEXT("bHf"));
    ImprimirMatrix(bHf);

    UE_LOG(LogClass, Log, TEXT("oHf"));
    ImprimirMatrix(oHf);
    Bola6->SetActorRelativeLocation(FVector(oHf.M[0][3],oHf.M[1][3],oHf.M[2][3]));
}

FMatrix ATrampa::MulMatrix(FMatrix a, FMatrix b) {
    FMatrix c;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            c.M[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                c.M[i][j] += a.M[i][k] * b.M[k][j];
            }
        }
    }
    return c;
}

void ATrampa::ImprimirMatrix(FMatrix m) {
    for (int i = 0; i < 4; i++) {
        UE_LOG(LogClass, Log, TEXT("[%.4f,%.4f,%.4f,%.4f]"), m.M[i][0], m.M[i][1], m.M[i][2], m.M[i][3]);
    }
}

FMatrix ATrampa::MatrizTraslacion(float x, float y, float z) {
    FMatrix Traslacion;
    Traslacion.M[0][0] = 1;
    Traslacion.M[0][1] = 0;
    Traslacion.M[0][2] = 0;
    Traslacion.M[0][3] = x;
    Traslacion.M[1][0] = 0;
    Traslacion.M[1][1] = 1;
    Traslacion.M[1][2] = 0;
    Traslacion.M[1][3] = y;
    Traslacion.M[2][0] = 0;
    Traslacion.M[2][1] = 0;
    Traslacion.M[2][2] = 1;
    Traslacion.M[2][3] = z;
    Traslacion.M[3][0] = 0;
    Traslacion.M[3][1] = 0;
    Traslacion.M[3][2] = 0;
    Traslacion.M[3][3] = 1;
    return Traslacion;
}

FMatrix ATrampa::MatrizRotacionX(float angle) {
    FMatrix RotX;
    RotX.M[0][0] = 1;
    RotX.M[0][1] = 0;
    RotX.M[0][2] = 0;
    RotX.M[0][3] = 0;
    RotX.M[1][0] = 0;
    RotX.M[1][1] = cos(angle);
    RotX.M[1][2] = -sin(angle);
    RotX.M[1][3] = 0;
    RotX.M[2][0] = 0;
    RotX.M[2][1] = sin(angle);
    RotX.M[2][2] = cos(angle);
    RotX.M[2][3] = 0;
    RotX.M[3][0] = 0;
    RotX.M[3][1] = 0;
    RotX.M[3][2] = 0;
    RotX.M[3][3] = 1;
    return RotX;
}

FMatrix ATrampa::MatrizRotacionY(float angle) {
    return FMatrix::Identity;
}

FMatrix ATrampa::MatrizRotacionZ(float angle) {
    FMatrix RotZ;//en este caso la matriz z es la identidad por que theta de V es 0 y eso al realziar calculos es la matriz identdad;
    RotZ.M[0][0] = cos(angle);
    RotZ.M[0][1] = -sin(angle);
    RotZ.M[0][2] = 0;
    RotZ.M[0][3] = 0;
    RotZ.M[1][0] = sin(angle);
    RotZ.M[1][1] = cos(angle);
    RotZ.M[1][2] = 0;
    RotZ.M[1][3] = 0;
    RotZ.M[2][0] = 0;
    RotZ.M[2][1] = 0;
    RotZ.M[2][2] = 1;
    RotZ.M[2][3] = 0;
    RotZ.M[3][0] = 0;
    RotZ.M[3][1] = 0;
    RotZ.M[3][2] = 0;
    RotZ.M[3][3] = 1;
    return RotZ;
}
