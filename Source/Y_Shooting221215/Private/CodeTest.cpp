// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeTest.h"

// Sets default values
ACodeTest::ACodeTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodeTest::BeginPlay()
{
	Super::BeginPlay();
	/*
	//Add 함수에 입력값 8, 4를 넣어서 결과를 result 변수에 받는다
	int32 result = Add(8, 4);
	int32 result2 = Sub(8, 4);
	int32 result3 = Mul(8, 4);
	float result4 = Div(4, 8);
	float result5 = Div2(4, 8.f);

	//result 변수에 있는 값을 화면에 출력한다
	UE_LOG(LogTemp, Warning, TEXT("Result is %d"), result);	
	UE_LOG(LogTemp, Warning, TEXT("Result is %d"), result2);
	UE_LOG(LogTemp, Warning, TEXT("Result is %d"), result3);
	UE_LOG(LogTemp, Warning, TEXT("Result is %.2f"), result4);
	UE_LOG(LogTemp, Warning, TEXT("Result is %.1f"), result5);
	
	//만약, 나이가 30살 이상이면 "꼰대"라고 출력하고 싶다
	if (age >= 30) {
		UE_LOG(LogTemp, Warning, TEXT("할배 되십니까"));
	}
	//만약, 나이가 20살 이상이면 "꼰대"라고 출력하고 싶다
	else if (age >= 20) {
		UE_LOG(LogTemp, Warning, TEXT("꼰대시네요ㅋ"));
	}
	//그렇지 않다면
	else {
		UE_LOG(LogTemp, Warning, TEXT("잼민이네ㅋ"));
	}

	//만약 나이가 20살 이상이면서 키가 160 이상인 경우에는 "환영" 이라고 출력한다.
	if (age >= 20 && height >= 160) {
		UE_LOG(LogTemp, Warning, TEXT("환영"));
	}
	//그렇지 않으면 "외면" 이라고 출력한다.
	else {
		UE_LOG(LogTemp, Warning, TEXT("외면"));
	}

	//만약, 국적이 "한국"이면서, 나이가 20살 이상 40세 미만인 경우 "청년" 이라고 출력
	if (nation == FString(TEXT("한국"))) {
		UE_LOG(LogTemp, Warning, TEXT("한국인"));

		if (age < 40 && age >= 20) {
			UE_LOG(LogTemp, Warning, TEXT("청년"));
		}
		
	}
	//만약, 그 외에는 청년 아님 이라고 출력
	else {
		UE_LOG(LogTemp, Warning, TEXT("청년 아님"));
	}


	//성과 이름을 받아서 둘을 합친 성명을 반환하는 함수
	//함수 이름 : StringAppender ( , )
	FString FullName = StringAppender1(name11, name22);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FullName);

	//문자열 두개를 결합하여 문자열 하나를 반환하는 함수
	//문자열을 반환하려면 포인터를 붙여줘야한다
	FString result1 = StringAppender(TEXT("김예은"), TEXT("ㅋㅋㅋ"));
	UE_LOG(LogTemp, Warning, TEXT("함수 실행 결과 : %s"), *result1);
	*/


	int32 checker = 123;
	//만약 checker에 들어있는 값이 짝수라면 "even"이라고 출력한다
	//그렇지 않고, 변수의 값이 홀수라면 "odd"라고 출력한다

	if (checker % 2 == 0) {
		UE_LOG(LogTemp, Warning, TEXT("even"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("odd"));
	}

	for (int32 i = 2; i < 10; i++) {
		for (int32 j = 1; j < 10; j++) {
			UE_LOG(LogTemp, Warning, TEXT("%d * %d = %d"), i, j, i * j);
		}
	}

}
/*
int32 ACodeTest::Add(int32 num1, int32 num2) {

	return num1 + num2;
}

int32 ACodeTest::Sub(int32 num3, int32 num4) {

	return num3 - num4;
}

int32 ACodeTest::Mul(int32 num5, int32 num6) {

	return num5 * num6;
}

float ACodeTest::Div(int32 num7, int32 num8) {

	return float (num7) / float (num8);
}

float ACodeTest::Div2(int32 num9, float num00) {

	return num9 / num00;
}
*/

/*
//값을 반환하는 함수 구현
FString ACodeTest::StringAppender(FString a, FString b) {
	return a + b;
}

FString ACodeTest::StringAppender1(FString firstname, FString lastname)
{
	return  firstname + lastname;
}
*/



// Called every frame
void ACodeTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
