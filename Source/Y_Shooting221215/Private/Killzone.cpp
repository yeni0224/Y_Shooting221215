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

	//������ �̺�Ʈ�� Ȱ��ȭ�Ѵ�
	boxComp->SetGenerateOverlapEvents(true);

	//������ �̺�Ʈ ��������Ʈ�� ������ �Լ��� �����Ѵ�.
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AKillZone_::OnOverlap);

}

// Called every frame
void AKillzone_::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillzone_::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//�÷��̾ ������ �ε��� ��� ����� �����Ѵ�.
	//�ε��� ����� �÷��̾������� : �÷��̾� Ŭ������ ĳ�����غ��� �� �� �ִ�. (�� Ŭ������ ���ڿ� OtherActor)
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	//�÷��̾� Ŭ������ �ƴ϶�� nullptr�� ���� ��ȯ�Ѵ�
	if (player != nullptr)
	{
		//Player�� �´� ��
	}
	else
	{
		//�÷��̾� Ŭ������ �ƴ϶�� �����Ѵ�
		OtherActor->Destroy();
	}
}