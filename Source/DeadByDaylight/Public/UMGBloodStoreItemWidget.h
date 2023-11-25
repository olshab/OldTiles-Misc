#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UObject/NoExportTypes.h"
#include "EBloodwebNodeContentType.h"
#include "UMGBloodStoreItemWidget.generated.h"

class UImage;
class UCanvasPanel;

UCLASS(Abstract, EditInlineNew)
class UUMGBloodStoreItemWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* NodeImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* RarityBackground;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* ItemPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* MysteryBoxPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* MysteryBoxRarityBackground;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* CollectedPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* ConsumedPanel;

	UPROPERTY(BlueprintReadOnly)
	EBloodwebNodeContentType _contentType;

	UPROPERTY(BlueprintReadOnly)
	bool _isMysteryBox;

	UPROPERTY(EditDefaultsOnly)
	FVector2D _bigItemScale;

	UPROPERTY(EditDefaultsOnly)
	FVector2D _normalItemScale;

	UPROPERTY(EditDefaultsOnly)
	float _consumedOpacity;

public:
	UFUNCTION(BlueprintNativeEvent)
	void UnFocusNode();

	UFUNCTION(BlueprintImplementableEvent)
	void SetSelectedVisibilities(bool isSelected);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SetBackgroundImages();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayConsumedAnimation(const bool skipIntro);

	UFUNCTION(BlueprintNativeEvent)
	void FocusNode();

	UFUNCTION(BlueprintNativeEvent)
	void ConsumeNode();

	UFUNCTION(BlueprintNativeEvent)
	void CollectNode();

private:
	UFUNCTION(BlueprintCallable)
	void BroadcastBloodNodeSelected();

public:
	UUMGBloodStoreItemWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGBloodStoreItemWidget) { return 0; }
