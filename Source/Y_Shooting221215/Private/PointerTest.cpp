// Fill out your copyright notice in the Description page of Project Settings.


#include "PointerTest.h"

// Sets default values
APointerTest::APointerTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	myAge = &realAge; //미리 기본 값을 먼저 정해주어 크래시나지 않도록 해준다. 가장 먼저 발생하는 순서에 위치하기
}

// Called when the game starts or when spawned
void APointerTest::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APointerTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

