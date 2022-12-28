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

	//오버랩 이벤트가 발생하도록 설정한다
	boxComp->SetGenerateOverlapEvents(true);

	//태어난 후 2초 뒤에 제거한다.
	//SetLifeSpan(2.0f);
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &ABullet::DestroyMySelf, 2.0f, false);
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
		//적이 있던 위치에 폭발 이펙트를 생성한다 (제거하기 전에 폭발해야 적의 위치를 알 수 있다)
		FVector enemyLoc = enemy->GetActorLocation();
		FRotator enemyRot = enemy->GetActorRotation();
		//어떤 이펙트를 받으면 좋을지 변수부터 받아오면 좋겠다 >>header
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_effect, enemyLoc, enemyRot, true);

		//적을 제거한다 (상대방부터 먼저 제거한다) , 모든 오브젝트는 Destroy 함수를 갖고있다
		enemy->Destroy();

		//나 자신이 사라지기 전에 GameMode에 점수 1점을 추가한다.(GameMode > current 변수)
		//전역변수로 저장해 빼놓는 것이 좋다
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AMyGameModeBase* myGM = Cast<AMyGameModeBase>(gm);
		myGM->AddScore(1);
		UE_LOG(LogTemp, Warning, TEXT("Point : %d"), myGM->GetCurrentScore());

		//나 자신을 제거한다 
		Destroy();

	}

}

void ABullet::DestroyMySelf()
{
	Destroy();
}