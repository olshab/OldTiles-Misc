#pragma once

#include "CoreMinimal.h"
#include "UIComponent.h"
#include "EContext.h"
#include "Components/SlateWrapperTypes.h"
#include "EPresenterPhase.h"
#include "Presenter.generated.h"

class UPresenterRequirementFunction;
class UUserWidget;
class UPresenterParentInfo;

UCLASS(BlueprintType, Abstract, EditInlineNew)
class DBDUIPRESENTERS_API UPresenter : public UUIComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _overrideWidgetInstantiationPhase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPresenterPhase _widgetInstantiationPhase;

	UPROPERTY(EditAnywhere)
	bool RequestPresentationAtBeginPlay;

	UPROPERTY(EditAnywhere)
	ESlateVisibility InitialVisibility;

	UPROPERTY(EditAnywhere)
	int32 _widgetZOrder;

	UPROPERTY(Transient, meta=(BindWidget))
	UUserWidget* _widget;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UPresenterParentInfo* _parentInfo;

	UPROPERTY(EditAnywhere)
	TSet<FString> _ignoredPresentationRequirementFunctions;

	UPROPERTY(Transient)
	TArray<UPresenterRequirementFunction*> _presentationRequirementFunctions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 _filter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 _currencyFilter;

private:
	UFUNCTION()
	bool ShouldPresent() const;

protected:
	UFUNCTION()
	void OnContextUnfocus(EContext context);

	UFUNCTION()
	void OnContextSectionChanged(EContext context);

	UFUNCTION()
	void OnContextFocus(EContext context);

	UFUNCTION()
	bool IsPlayerStateReady() const;

	UFUNCTION()
	bool IsGameStateReady() const;

	UFUNCTION()
	bool IsContextReady() const;

public:
	UPresenter();
};

FORCEINLINE uint32 GetTypeHash(const UPresenter) { return 0; }
