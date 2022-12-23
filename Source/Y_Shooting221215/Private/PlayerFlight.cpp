// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlight.h"
#include "Components/BoxComponent.h" //box �߰�
#include "Components/StaticMeshComponent.h" //mesh �߰� (bone�� ���� mesh, bone ������ skeletal mesh)
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
	
	//������ �Լ����� �浹 �ڽ� ������Ʈ�� �����Ѵ�
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	//������ �浹�ڽ� ������Ʈ�� ��Ʈ ������Ʈ�� �����Ѵ�
	SetRootComponent(boxComp);

	//�ڽ� �ݸ����� ũ�⸦ ����x����x���� ��� 50��Ƽ���ͷ� �����Ѵ�
	//���� �ѹ��� ���� ��� ����, ���� ���� ��ο� ���� ���� �� ��
	boxComp->SetBoxExtent(FVector(50.0f));


	//�ڽ� �ݸ����� �浹 ó�� �������� "PlayerPreset"���� �����Ѵ�
	boxComp->SetCollisionProfileName(TEXT("PlayerPreset"));




	//�޽� ������Ʈ�� �����Ѵ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	//�޽� ������Ʈ�� �縬 ������Ʈ�� ���� ��ü�� ����Ѵ�
	//��Ʈ ������Ʈ�� �ٲ� root component�� ������ �ʱ� ������ ������ �����ϴ�
	meshComp->SetupAttachment(RootComponent);

	//�޽� ������Ʈ�� staticmesh �׸� ť�������� �Ҵ��Ѵ�
	ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	//���� ť�� ������ �ε��ϴµ� �����ߴٸ�
	if (cubeMesh.Succeeded()) //Ŭ���� �����̱� ������ .�����ڸ� ���´�
	{
		//�ε��� ������ �޽� ������Ʈ�� static mesh �׸� �ִ´�
		meshComp->SetStaticMesh(cubeMesh.Object); //������ �����ڶ� -> �����ڸ� ���´�
	}
}

// Called when the game starts or when spawned
void APlayerFlight::BeginPlay()
{
	Super::BeginPlay();

	//�÷��̾� ��Ʈ�ѷ��� ĳ�����Ѵ�
	APlayerController* playerCon = Cast<APlayerController>(GetController()); //������ �ᵵ �Ǳ� �ϴµ� �Լ��� �׳� ��������

	if (playerCon != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys 
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());
		//� Ÿ���� ����ý����� �����ð��� �˷�����Ѵ�(>> ĳ���� �ؾ��Ѵ�)

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

	//������� �Է�Ű �̿�
	//1.���� �Է°��� �¿� �Է°��� �̿��ؼ� ������͸� �����.

	//2.����ڰ� �Է��� ������ �̵��ϰ� �ʹ� : ������ ����ȭ
	direction.Normalize();

	//3.����ڰ� �Է��� ������ �̵��ϰ�ʹ�
	//P = P0 + vt
	FVector dir = GetActorLocation() + direction * moveSpeed * DeltaTime;

	//4.���� ������ ��ġ ��ǥ�� �տ��� ���� �� ��ǥ�� �����Ѵ�.
	SetActorLocation(dir);

}

// Ű����� �Է������� �� ���� �̺�Ʈ�� �������ִ� ��
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//������ UInputComponent* ������ UEnhancedInputComponent*�� ��ȯ�Ѵ�
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent); //uinputcomponent�� ��ӹ޾Ҵٴ� ��

	//�Լ� �����ϱ�
	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Triggered, this, &APlayerFlight::Horizontal);

	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Completed, this, &APlayerFlight::Horizontal);

	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Triggered, this, &APlayerFlight::Vertical);
	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Completed, this, &APlayerFlight::Vertical);

	enhancedInputComponent->BindAction(ia_fire, ETriggerEvent::Triggered, this, &APlayerFlight::FireBullet);

	//Horizontal Axis �Լ��� ���ε� �Ѵ�. "Horizontal"�� �� Ŭ���� �ȿ� �ִ� Horizontal Ŭ������ �����Ѵ�
	//PlayerInputComponent->BindAxis("Horizontal", this, &APlayerFlight::Horizontal);
	//Vertical Axis �Լ��� ���ε� �Ѵ�
	//PlayerInputComponent->BindAxis("Vertical", this, &APlayerFlight::Vertical);

	//Fire Action �Է¿� �Լ��� �����Ѵ�
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerFlight::FireBullet);
	//IE_Pressed : ��ư�� ������ �� , IE_Released : ��ư�� ������ ��
}

//�¿� �Է��� ���� �� ����� �Լ�
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

// ���� �Է��� ���� �� ����� �Լ�
// void APlayerFlight::Vertical(float value)
// {
// 	v= value;
// 	//UE_LOG(LogTemp, Warning, TEXT("v = %.4f"), v);
// 	direction.Z = v;
// }

//���콺 ���� ��ư�� ������ �� ����� �Լ�
void APlayerFlight::FireBullet()
{
	//������ �� �Ѿ��� �����Ѵ�
	//�Ѿ� �������Ʈ ������ �ʿ��ϴ�. �� ������ ���� �����ض�

	//�÷��̾��� ��ġ���� ���� ���� ��ġ��Ų��
	FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 90.0f;

	//pitch �������� -90 Ʋ���ش�(y ����)
	FRotator spawnRotation = FRotator(90.0f, 0, 0);//pitch yaw roll ������ �ۼ�������Ѵ�. ���������� yaw pitch roll��
	GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotation);
	FActorSpawnParameters param; //����ü�� �����Ͱ� ����Ǿ��ִ� �ܼ��� �����̹Ƿ� *������� �ʴ´�
	
	//������Ʈ�� �����Ǿ��µ� �̹� ���ڸ��� �ٸ� ������Ʈ�� ��ġ������ ���. �������ڸ��� �浹�� �߻��Ѵ�.
	//�׷� �� ��� �Ұ��� �������ִ� ���̴�
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotation, param);
	
}
