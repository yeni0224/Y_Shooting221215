// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeTest.generated.h"

UCLASS()
class Y_SHOOTING221215_API ACodeTest : public AActor
	//함수 이름 앞에 A가 붙으면 Actor라는 부모로부터 상속받았다는 뜻
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodeTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	//실수형 변수 fnumber을 선언한다
	float fnumber1 = 3.14f;
	float fnumber2 = 10.0f;
	
	//문자열 변수 name을 선언한다.
	FString name;
	// FString name = ""; 와 같다
	FString name2 = FString(TEXT("김예은"));
	
	//논리형 변수 isStudent를 선언한다
	bool isStudent;
	//bool isStudent = false; 와 같다
	bool isTeacher = false;
	*/

	/*
	int32 Add(int32 num1, int32 num2);
	int32 Sub(int32 num3, int32 num4);
	int32 Mul(int32 num5, int32 num6);
	float Div(int32 num7, int32 num8);
	float Div2(int32 num9, float num00);

	UPROPERTY(EditAnywhere, Category = CodeVariable)
	int32 age = 25;

	UPROPERTY(EditAnywhere, Category = CodeVariable)
	int32 height = 155;

	UPROPERTY(EditAnywhere, Category = CodeVariable)
	FString nation = FString(TEXT("한국"));
	*/

	/*
	//성과 이름을 받아서 둘을 합친 성명을 반환하는 함수
	//함수 이름 : StringAppender ( , )
	FString StringAppender1(FString firstname, FString lastname);
	FString name11 = FString(TEXT("Yeeun"));
	FString name22 = FString(TEXT("Kim"));

	//문자열 두개를 받아서 문자열 한개로 합쳐서 반환하는 함수를 만들고싶다
	UFUNCTION(BlueprintCallable) //내 코드를 언리얼에서 직접 접근할 수 있게 하는 것
	FString StringAppender(FString a, FString b); //블루프린트에서도 쓸 수 있는 함수이다

	//UFUNCTION(BlueprintPure)
	*/


};