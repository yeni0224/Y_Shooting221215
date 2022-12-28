// Fill out your copyright notice in the Description page of Project Settings.


#include "Killzone_.h"
#include "Components/BoxComponent.h"
#include "PlayerFlight.h"

// Sets default values
AKillzone_::AKillZone_()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);

	boxComp->SetBoxExtent(FVector(50.0f, 2000.0f, 50.0f));
	boxComp->SetCollisionProfileName(TEXT("KillzonePreset"));
}

// Called when the game starts or when spawned
void AKillzone_::BeginPlay()
{
	Super::BeginPlay();

	//오버랩 이벤트를 활성화한다
	boxComp->SetGenerateOverlapEvents(true);

	//오버랩 이벤트 델리게이트에 오버랩 함수를 연결한다.
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AKillZone_::OnOverlap);

}

// Called every frame
void AKillzone_::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillzone_::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//플레이어를 제외한 부딪힌 모든 대상을 제거한다.
	//부딪힌 대상이 플레이어인지는 : 플레이어 클래스로 캐스팅해보면 알 수 있다. (이 클래스의 인자에 OtherActor)
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	//플레이어 클래스가 아니라면 nullptr로 값을 변환한다
	if (player != nullptr)
	{
		//Player가 맞는 것
	}
	else
	{
		//플레이어 클래스가 아니라면 제거한다
		OtherActor->Destroy();
	}
}