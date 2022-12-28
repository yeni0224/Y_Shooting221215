// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameModeBase.h"

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

	//������ �̺�Ʈ�� �߻��ϵ��� �����Ѵ�
	boxComp->SetGenerateOverlapEvents(true);

	//�¾ �� 2�� �ڿ� �����Ѵ�.
	//SetLifeSpan(2.0f);
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &ABullet::DestroyMySelf, 2.0f, false);
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
		//���� �ִ� ��ġ�� ���� ����Ʈ�� �����Ѵ� (�����ϱ� ���� �����ؾ� ���� ��ġ�� �� �� �ִ�)
		FVector enemyLoc = enemy->GetActorLocation();
		FRotator enemyRot = enemy->GetActorRotation();
		//� ����Ʈ�� ������ ������ �������� �޾ƿ��� ���ڴ� >>header
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_effect, enemyLoc, enemyRot, true);

		//���� �����Ѵ� (������� ���� �����Ѵ�) , ��� ������Ʈ�� Destroy �Լ��� �����ִ�
		enemy->Destroy();

		//�� �ڽ��� ������� ���� GameMode�� ���� 1���� �߰��Ѵ�.(GameMode > current ����)
		//���������� ������ ������ ���� ����
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AMyGameModeBase* myGM = Cast<AMyGameModeBase>(gm);
		myGM->AddScore(1);
		UE_LOG(LogTemp, Warning, TEXT("Point : %d"), myGM->GetCurrentScore());

		//�� �ڽ��� �����Ѵ� 
		Destroy();

	}

}

void ABullet::DestroyMySelf()
{
	Destroy();
}