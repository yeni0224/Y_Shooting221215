// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h" //include �� ���� �׻� generated �����ٰ� �ۼ��ؾ��Ѵ�
#include "PlayerFlight.generated.h"

UCLASS()
class Y_SHOOTING221215_API APlayerFlight : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerFlight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
		class UBoxComponent* boxComp; //���� ������ ���ָ� ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
		float moveSpeed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
		TSubclassOf<class ABullet> bulletFactory;
	//�𸮾� ���� ������ �Լ��� �ƴ� �ܺο��� �ҷ����� �Լ��� ��� TSuclassOf�� ������ش�

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class UInputAction* ia_horizontal;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class UInputAction* ia_vertical;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class UInputAction* ia_fire;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class UInputMappingContext* imc_myMapping;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class USoundBase* fireSound;

	void ReservationHitColor(float time);
	void ChangeOriginColor();

private:

	//�Է����� �� �������� �����ϱ� ���� �Լ��� �� ĳ���͸� ��Ʈ���� �� �ֵ��� private���� �Ѵ�.
// 	UFUNCTION(BlueprintCallable)
// 	void Horizontal(float value);

	UFUNCTION(BlueprintCallable)
		void Horizontal(const FInputActionValue& value);
	//�����ε��Ͽ���. �ٸ� Ÿ���� ������ �־� ����� �� �ְ��Ѵ�, FInputActionValue�� ����ü�̴�.

	UFUNCTION(BlueprintCallable)
		void Vertical(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
		void FireBullet(); //bool type���� ������� ������ ������ ��� �ȴ�.

	// 	UFUNCTION(BlueprintCallable)
	// 	void Vertical(float value);
	// 
	// 	//�׼��� ��� �Ű������� ����־� �Ѵ�
	// 	UFUNCTION(BlueprintCallable)
	// 	void FireBullet(); 

		//������ ���� �����Ͽ���. �������� �ʴ� ���������� ���� ��� �� ������ ���ڴ�
	float h;
	float v;
	FVector direction;
	FLinearColor initColor; //������ B�÷� ���ϱ����� ����
	//FColor : RGB�� �ڷ����� float���̴�.(�� 4byte) ���� 0 ~ 1 ���̿� �ִ�
	//FRGB : byte������ �ڷ����̴�.(�� 4byte) ���� 0 ~ 255 ���̿� �ִ� 1byte = 8 bit = 2^8
	FTimerHandle colorTimer;
	UMaterialInstanceDynamic* dynamicMat;
};