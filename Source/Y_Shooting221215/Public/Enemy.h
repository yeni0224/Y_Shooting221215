// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class Y_SHOOTING221215_API AEnemy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EnemySettings)
		class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EnemySettings)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemySettings)
		float moveSpeed = 800.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemySettings)
		int32 traceRate = 30;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FVector direction;
	class APlayerFlight* target;
	//���������� �����ϸ� class�� ���漱��������Ѵ� APlayerFlight�� Ŭ�����̴�
};