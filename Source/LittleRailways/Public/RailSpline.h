
#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameFramework/Actor.h"
#include "RailSpline.generated.h"

UCLASS()
class LITTLERAILWAYS_API ARailSpline : public AActor
{
	GENERATED_BODY()

public:
	ARailSpline();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void AddSplineMeshComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rail Spline Properties")
	float m_SectionLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rail Spline Properties")
	bool m_AllowScaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rail Spline Properties")
	bool m_MustBeFullLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rail Spline Properties")
	UStaticMesh* m_SplineMesh;

	USplineComponent* m_Spline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rail Spline Properties")
	USplineMeshComponent* m_SplineMeshComponent;

protected:
	virtual void BeginPlay() override;

private:
	void AddMeshToSpline();

	//Getters
	FVector GetStartPos(int index);
	FVector GetEndPos(int index);
	FVector GetStartTangent(int index);
	FVector GetEndTangent(int index);

	int loopIndex;
};