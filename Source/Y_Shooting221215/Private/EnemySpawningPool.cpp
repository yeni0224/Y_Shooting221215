// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawningPool.h"
#include "Enemy.h"
#include "Components/ArrowComponent.h"

// Sets default values
AEnemySpawningPool::AEnemySpawningPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	SetRootComponent(rootScene);

	spawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Arrow"));
	spawnArrow->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemySpawningPool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawningPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//1. Ÿ�̸Ӹ� ���� �ʰ� �ڵ������ �����ϴ� ��
	//����� �ð��� ������Ų��(��ž��ġ) >> ������ �ð��� ������ ��Ÿ�ӱ��� á�°� >> ���� �Ǿ��ٸ� �ٽ� 0���� �ǵ�����
	//���������� �ؾ� ������� �ʴ´�
	currentTime += DeltaTime;

	//���� ������ �ð��� spawnCool�� ������ �ð����� ũ�ų� ���ٸ�
	if (currentTime >= spawnCool) {
		
		//Enemy �������Ʈ�� �����Ѵ�
		//Arrow ������Ʈ�� ��ġ�� ȸ���� ������ ���� �����δ�
		GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());

		
		//������ �ð��� 0�ʷ� �ʱ�ȭ �Ѵ�
		currentTime = 0;
	}
	
}

