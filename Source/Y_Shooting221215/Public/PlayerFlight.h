// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h" //include 할 때는 항상 generated 위에다가 작성해야한다
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
		class UBoxComponent* boxComp; //전반 선언을 해주면 됨

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
		float moveSpeed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
		TSubclassOf<class ABullet> bulletFactory;
	//언리얼 엔진 고유의 함수가 아닌 외부에서 불러오는 함수의 경우 TSuclassOf를 사용해준다

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

	//입력했을 때 움직임을 제어하기 위한 함수는 그 캐릭터만 컨트롤할 수 있도록 private으로 한다.
// 	UFUNCTION(BlueprintCallable)
// 	void Horizontal(float value);

	UFUNCTION(BlueprintCallable)
		void Horizontal(const FInputActionValue& value);
	//오버로드하였다. 다른 타입의 변수를 넣어 사용할 수 있게한다, FInputActionValue는 구조체이다.

	UFUNCTION(BlueprintCallable)
		void Vertical(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
		void FireBullet(); //bool type으로 만들었기 때문에 변수는 없어도 된다.

	// 	UFUNCTION(BlueprintCallable)
	// 	void Vertical(float value);
	// 
	// 	//액션의 경우 매개변수는 비워둬야 한다
	// 	UFUNCTION(BlueprintCallable)
	// 	void FireBullet(); 

		//변수를 따로 생성하였다. 지워지지 않는 전역변수를 만들어서 계속 이 변수를 쓰겠다
	float h;
	float v;
	FVector direction;
	FLinearColor initColor; //최초의 B컬러 정하기위한 변수
	//FColor : RGB값 자료형이 float형이다.(총 4byte) 값이 0 ~ 1 사이에 있다
	//FRGB : byte형태의 자료형이다.(총 4byte) 값이 0 ~ 255 사이에 있다 1byte = 8 bit = 2^8
	FTimerHandle colorTimer;
	UMaterialInstanceDynamic* dynamicMat;
};