// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame. 
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�浹 ���� ����
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f)); //������ �ڵ�� �����ϱ�

	//�Ѿ� �ݸ����� �浹 ó�� �������� "BulletPreset"���� �����Ѵ�
	boxComp->SetCollisionProfileName(TEXT("BulletPreset"));

	//�޽� ����
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocation(FVector(0, 0, -50)); 
	//relative : ������� <-> Set World Relative Location : ��������
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	//�浹(overlap)�� �߻��ϸ� ������ �Լ��� �����Ѵ�
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
	boxComp->SetGenerateOverlapEvents(true);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//direction = FVector(1, 0, 0); //���� ����

	// ���� ���� �������� ��� �̵��ϰ� �ʹ�
	direction = GetActorForwardVector(); 
	
	//��ġ �̵�, ForwardVector�� normalize�� �ʿ����� �ʴ�
	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);
}

//�浹ü ������Ʈ, ������, , , Hit�� ���õ� ����
void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AEnemy* enemy = Cast<AEnemy>(OtherActor); //include "Enemy.h" �߰��������

	//���� �ε��� ����� �Ѿ��̶�� (other actor�� enemy���� �ƴ� �� �ִ� > enemy�� ĳ���� �Ͽ� Ȯ�κ��� �Ѵ�)
	if (enemy != nullptr)
	{
		//���� �����Ѵ� (������� ���� �����Ѵ�) , ��� ������Ʈ�� Destroy �Լ��� �����ִ�
		enemy->Destroy();

		//�� �ڽ��� �����Ѵ�
		Destroy();
	}

}

