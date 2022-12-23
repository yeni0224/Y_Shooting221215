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

	//1. 타이머를 쓰지 않고 코드식으로 구현하는 법
	//경과된 시간을 누적시킨다(스탑워치) >> 누적된 시간이 지정된 쿨타임까지 찼는가 >> 누적 되었다면 다시 0으로 되돌리기
	//전역변수로 해야 사라지지 않는다
	currentTime += DeltaTime;

	//만약 누적된 시간이 spawnCool에 지정된 시간보다 크거나 같다면
	if (currentTime >= spawnCool) {
		
		//Enemy 블루프린트를 생성한다
		//Arrow 컴포넌트의 위치와 회전된 각도에 따라서 움직인다
		GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());

		
		//누적된 시간을 0초로 초기화 한다
		currentTime = 0;
	}
	
}

