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

	//충돌 영역 생성
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f)); //스케일 코드로 조정하기

	//총알 콜리전의 충돌 처리 프리셋을 "BulletPreset"으로 설정한다
	boxComp->SetCollisionProfileName(TEXT("BulletPreset"));

	//메쉬 생성
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocation(FVector(0, 0, -50)); 
	//relative : 상대적인 <-> Set World Relative Location : 절대적인
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	//충돌(overlap)이 발생하면 실행할 함수를 연결한다
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
	boxComp->SetGenerateOverlapEvents(true);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//direction = FVector(1, 0, 0); //정면 벡터

	// 나의 정면 방향으로 계속 이동하고 싶다
	direction = GetActorForwardVector(); 
	
	//위치 이동, ForwardVector은 normalize가 필요하지 않다
	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);
}

//충돌체 컴포넌트, 대상액터, , , Hit과 관련된 정보
void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AEnemy* enemy = Cast<AEnemy>(OtherActor); //include "Enemy.h" 추가해줘야함

	//만일 부딪힌 대상이 총알이라면 (other actor이 enemy만이 아닐 수 있다 > enemy로 캐스팅 하여 확인부터 한다)
	if (enemy != nullptr)
	{
		//적을 제거한다 (상대방부터 먼저 제거한다) , 모든 오브젝트는 Destroy 함수를 갖고있다
		enemy->Destroy();

		//나 자신을 제거한다
		Destroy();
	}

}

