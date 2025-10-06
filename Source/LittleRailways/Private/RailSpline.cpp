#include "RailSpline.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARailSpline::ARailSpline()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	m_Spline->SetupAttachment(RootComponent);

	if (m_AllowScaling)
	{
		m_SectionLength = (GetActorScale3D().X * 100.f);
	}

	if (m_MustBeFullLength)
	{
		for (int i = 0; i < FMath::TruncToInt((m_Spline->GetSplineLength() / m_SectionLength)); i++)
		{
			loopIndex = i;
			AddMeshToSpline();
		}
	}
	else
	{
		for (int i = 0; i < FMath::TruncToInt((m_Spline->GetSplineLength() / m_SectionLength)) - 1; i++)
		{
			loopIndex = i;
			AddMeshToSpline();
		}
	}
}

// Called when the game starts or when spawned
void ARailSpline::BeginPlay()
{
	Super::BeginPlay();
}

void ARailSpline::AddMeshToSpline()
{
	if (m_SplineMeshComponent != NULL)
	{
		m_SplineMeshComponent->SetStaticMesh(m_SplineMesh);
		m_SplineMeshComponent->SetForwardAxis(ESplineMeshAxis::X, true);
		m_SplineMeshComponent->SetStartAndEnd(GetStartPos(loopIndex), GetStartTangent(loopIndex), GetEndPos(loopIndex), GetEndTangent(loopIndex), true);
		m_SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

FVector ARailSpline::GetStartPos(int index)
{
	return m_Spline->GetLocationAtDistanceAlongSpline((index * m_SectionLength), ESplineCoordinateSpace::Local);
}

FVector ARailSpline::GetEndPos(int index)
{
	return m_Spline->GetLocationAtDistanceAlongSpline(((index + 1) * m_SectionLength), ESplineCoordinateSpace::Local);
}

FVector ARailSpline::GetStartTangent(int index)
{
	return UKismetMathLibrary::ClampVectorSize(m_Spline->GetTangentAtDistanceAlongSpline((index * m_SectionLength), ESplineCoordinateSpace::Local), 0, m_SectionLength);
}

FVector ARailSpline::GetEndTangent(int index)
{
	return UKismetMathLibrary::ClampVectorSize(m_Spline->GetTangentAtDistanceAlongSpline(((index + 1) * m_SectionLength), ESplineCoordinateSpace::Local), 0, m_SectionLength);
}

// Called every frame
void ARailSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}