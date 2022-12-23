// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlight.h"
#include "Components/BoxComponent.h" //box 추가
#include "Components/StaticMeshComponent.h" //mesh 추가 (bone이 없는 mesh, bone 있으면 skeletal mesh)
#include "UObject/ConstructorHelpers.h"
#include "Bullet.h"
#include "Gameframework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerFlight::APlayerFlight()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//생성자 함수에서 충돌 박스 컴포넌트를 생성한다
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	//생성된 충돌박스 컴포넌트를 루트 컴포넌트로 설정한다
	SetRootComponent(boxComp);

	//박스 콜리전의 크기를 가로x세로x높이 모두 50센티미터로 설정한다
	//숫자 한번만 적을 경우 가로, 세로 높이 모두에 같은 값이 들어갈 것
	boxComp->SetBoxExtent(FVector(50.0f));


	//박스 콜리전의 충돌 처리 프리셋을 "PlayerPreset"으로 설정한다
	boxComp->SetCollisionProfileName(TEXT("PlayerPreset"));




	//메시 컴포넌트를 생성한다
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	//메시 컴포넌트를 루릍 컴포넌트의 하위 개체로 등록한다
	//루트 컴포넌트가 바뀌어도 root component는 변하지 않기 때문에 수정이 용이하다
	meshComp->SetupAttachment(RootComponent);

	//메시 컴포넌트의 staticmesh 항목에 큐브파일을 할당한다
	ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	//만약 큐브 파일을 로드하는데 성공했다면
	if (cubeMesh.Succeeded()) //클래스 변수이기 때문에 .연산자를 적는다
	{
		//로드한 파일을 메시 컴포넌트의 static mesh 항목에 넣는다
		meshComp->SetStaticMesh(cubeMesh.Object); //포인터 연산자라서 -> 연산자를 적는다
	}
}

// Called when the game starts or when spawned
void APlayerFlight::BeginPlay()
{
	Super::BeginPlay();

	//플레이어 컨트롤러를 캐스팅한다
	APlayerController* playerCon = Cast<APlayerController>(GetController()); //변수로 써도 되긴 하는데 함수로 그냥 적어주자

	if (playerCon != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys 
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());
		//어떤 타입의 서브시스템을 가져올건지 알려줘야한다(>> 캐스팅 해야한다)

		if (subsys != nullptr)
		{
			subsys->AddMappingContext(imc_myMapping, 0);
		}
	}
	
}

// Called every frame
void APlayerFlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//사용자의 입력키 이용
	//1.상하 입력값과 좌우 입력값을 이용해서 방향백터를 만든다.

	//2.사용자가 입력한 방향대로 이동하고 싶다 : 벡터의 정규화
	direction.Normalize();

	//3.사용자가 입력한 방향대로 이동하고싶다
	//P = P0 + vt
	FVector dir = GetActorLocation() + direction * moveSpeed * DeltaTime;

	//4.현재 액터의 위치 좌표를 앞에서 구한 새 좌표로 갱신한다.
	SetActorLocation(dir);

}

// 키보드로 입력했을때 그 값을 이벤트와 연결해주는 것
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//기존의 UInputComponent* 변수를 UEnhancedInputComponent*로 변환한다
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent); //uinputcomponent를 상속받았다는 것

	//함수 연결하기
	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Triggered, this, &APlayerFlight::Horizontal);

	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Completed, this, &APlayerFlight::Horizontal);

	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Triggered, this, &APlayerFlight::Vertical);
	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Completed, this, &APlayerFlight::Vertical);

	enhancedInputComponent->BindAction(ia_fire, ETriggerEvent::Triggered, this, &APlayerFlight::FireBullet);

	//Horizontal Axis 함수를 바인딩 한다. "Horizontal"을 이 클래스 안에 있는 Horizontal 클래스와 연결한다
	//PlayerInputComponent->BindAxis("Horizontal", this, &APlayerFlight::Horizontal);
	//Vertical Axis 함수를 바인딩 한다
	//PlayerInputComponent->BindAxis("Vertical", this, &APlayerFlight::Vertical);

	//Fire Action 입력에 함수를 연결한다
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerFlight::FireBullet);
	//IE_Pressed : 버튼을 눌렀을 때 , IE_Released : 버튼을 떼었을 때
}

//좌우 입력이 있을 때 실행될 함수
// void APlayerFlight::Horizontal(float value)
// {
// 	h = value;
// 	//UE_LOG(LogTemp, Warning, TEXT("h = %.4f"), h);
// 	direction.Y = h;
// }

void APlayerFlight::Horizontal(const FInputActionValue& value)
{
	h = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("h = %.4f"), h);
	direction.Y = h;
}

void APlayerFlight::Vertical (const FInputActionValue& value)
{
	v = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("h = %.4f"), h);
	direction.Z = v;
}

// 상하 입력이 있을 때 실행될 함수
// void APlayerFlight::Vertical(float value)
// {
// 	v= value;
// 	//UE_LOG(LogTemp, Warning, TEXT("v = %.4f"), v);
// 	direction.Z = v;
// }

//마우스 왼쪽 버튼을 눌렀을 때 실행될 함수
void APlayerFlight::FireBullet()
{
	//눌렀을 때 총알을 생성한다
	//총알 블루프린트 변수가 필요하다. 그 변수의 값을 생성해라

	//플레이어의 위치보다 높은 곳에 위치시킨다
	FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 90.0f;

	//pitch 방향으로 -90 틀어준다(y 방향)
	FRotator spawnRotation = FRotator(90.0f, 0, 0);//pitch yaw roll 순으로 작성해줘야한다. 엔진에서는 yaw pitch roll순
	GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotation);
	FActorSpawnParameters param; //구조체라 데이터가 저장되어있는 단순한 형태이므로 *사용하지 않는다
	
	//오브젝트가 생성되었는데 이미 이자리에 다른 오브젝트가 위치해있을 경우. 생성되자마자 충돌이 발생한다.
	//그럴 때 어떻게 할건지 설정해주는 것이다
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotation, param);
	
}
