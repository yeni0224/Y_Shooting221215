// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerFlight.h"
#include "EngineUtils.h" //�̰� ��� �̸� �˻��Ҷ� : 

// Sets default values ������
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f));

	/*�浹 ������ �����ϱ�*/
	//Collision Enabled ���� Query and Physics�� �����Ѵ�
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//�浹�� ������ ä���� Object Type�� Enemy�� �����Ѵ�
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel1);

	//����ä���� �ϰ������� Ignore���·� ó���Ѵ�
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	//���� ä���� Player�� bullet ä�ο� ���ؼ��� Overlap���� ó���Ѵ� >> ��ü�� ignore�� �а� overlap���� �ؾ� �ڵ带 ���� �� ����. ���� �߿�!
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	meshComp -> SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//��÷�� ���ؼ� �ϳ��� ���� ����, �� �ٸ� �ϳ��� �÷��̾� �������� �̵��ϰ�ʹ�
	//1. ��÷�� �Ѵ�. Ȯ���� ������ �̿��ؼ� 7:3 ������ �Ѵ�.
	int32 drawNumber = FMath::RandRange(1, 100);
	//fmath Ŭ������ �ִ� randrange�Լ�, ���� Ȯ���� ������ 0~1������ �Ǽ��� ������ ����Ѵ�
		
	//2. ����, ���� ���� 30���� ������...
	if (drawNumber <= traceRate)
	{
		
	    //2-1. �÷��̾� ���͸� ã�´� : ������ ������BP�� �÷��̾ ã�ƾ��ϹǷ�, �ܼ��� ���⸸ ���Ұ��̹Ƿ� h�� �������� �����ϱ�.
		
		//BP���� ��ġ�� �ٸ� �÷��̾� ã�� �� (���忡�� Ư���� ��ü�� ã�� ��� 1):
		//��ȯ���� Actor, ���� �Լ��� ���ڷ� �޴´�, ã������ ���(APlayerFlight.h�� �߰��������)	
		//AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerFlight::StaticClass());
	

		//2-2. �÷��̾��� ��ġ(���� �������ϴ� ����) - ���� ��ġ = �� ������ �����Ѵ�
		
		//���忡�� Ư���� ��ü�� ã�� ��� 1
		//���͸� �������� ��ġ ��ü�� �� �� �ֱ� ������
        //FVector targetdir = target->GetActorLocation() - GetActorLocation();
        //direction = targetdir;
		//�̷��� �ϸ� ������ �Ÿ��� õ������ ���̰� ���� �ȴ�. ������ ��� �Ǿ��� ������ ���̰� �������� 1¥���� �ʱ�ȭ��������Ѵ�		
		

		//���忡�� Ư���� ��ü�� ã�� ���2
	    //APlayerFlight* target; << �긦 ���������� ������ֱ� ���� h�� ������

		// AplayerFlight���� ����Ѵ�
		//�ؼ� : World�� ��ġ�� ��� �迭���� Iterator��� ���Ŀ� �־���, �ϳ��� ������ �� null���� �ƴ϶��, ��ȯ �Ҷ����� �ϳ��� ��������
		for (TActorIterator<APlayerFlight> it(GetWorld()); it; ++it)
		{
			target = *it;
		}
		//����ȭ�� ���ؼ�
		if (target != nullptr)
		{
			float temp = target->moveSpeed;
		}

		FVector targetdir = target->GetActorLocation() - GetActorLocation();
		targetdir.Normalize();
		direction = targetdir;
		

	}	

	//3. �׷���������
	else 
	{
		//3-1. �������� ������ ���Ѵ�
		direction = GetActorForwardVector();
	}
	
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� ���� �������� ��� �̵��ϰ� �ʹ�. ������ �����Ͽ����Ƿ� ������ �ȴ�
	//direction = GetActorForwardVector();

	//��ġ �̵�, ForwardVector�� normalize�� �ʿ����� �ʴ�
	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);

}


