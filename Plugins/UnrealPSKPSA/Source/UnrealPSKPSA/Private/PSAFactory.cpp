// Fill out your copyright notice in the Description page of Project Settings.


#include "PSAFactory.h"
#include "PSAReader.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/ScopedSlowTask.h"

UObject* UPSAFactory::Import(const FString Filename, UObject* Parent, const FName Name, const EObjectFlags Flags) const
{
	auto Psa = PSAReader(Filename);
	if (!Psa.Read()) return nullptr;
	
	auto AnimSequence = NewObject<UAnimSequence>(Parent, UAnimSequence::StaticClass(), Name, Flags);
	
	AnimSequence->SetSkeleton(SettingsImporter->Skeleton.Get());
	AnimSequence->CreateAnimation(SettingsImporter->SkeletalMesh.Get());

	auto MeshBones = SettingsImporter->Skeleton->GetReferenceSkeleton().GetRawRefBoneInfo();

	auto Info = Psa.AnimInfo;
	AnimSequence->SetRawNumberOfFrame(Info.NumRawFrames);
	AnimSequence->SequenceLength = Info.NumRawFrames/Psa.AnimInfo.AnimRate;
	
	FScopedSlowTask ImportTask(Psa.Bones.Num(), FText::FromString("Importing Anim"));
	ImportTask.MakeDialog(false);
	for (auto BoneIndex = 0; BoneIndex < Psa.Bones.Num(); BoneIndex++)
	{
		auto Bone = Psa.Bones[BoneIndex];
		auto BoneName = FName(Bone.Name);
		ImportTask.DefaultMessage = FText::FromString(FString::Printf(TEXT("Bone %s: %d/%d"), *BoneName.ToString(), BoneIndex+1, Psa.Bones.Num()));
		ImportTask.EnterProgressFrame();
		
		TArray<FVector> PositionalKeys;
		TArray<FQuat> RotationalKeys;
		TArray<FVector> ScaleKeys;
		for (auto Frame = 0; Frame < Info.NumRawFrames; Frame++)
		{
			auto KeyIndex = BoneIndex + Frame * Psa.Bones.Num();
			auto AnimKey = Psa.AnimKeys[KeyIndex];

			PositionalKeys.Add(FVector(AnimKey.Position.X, -AnimKey.Position.Y, AnimKey.Position.Z));
			RotationalKeys.Add(FQuat(AnimKey.Orientation.X, -AnimKey.Orientation.Y, AnimKey.Orientation.Z,
				(BoneIndex == 0) ? -AnimKey.Orientation.W : AnimKey.Orientation.W).GetNormalized());
			ScaleKeys.Add(Psa.bHasScaleKeys ? Psa.ScaleKeys[KeyIndex].ScaleVector : FVector::OneVector);
		}
		
		//AnimController.AddBoneTrack(BoneName);
		//AnimController.SetBoneTrackKeys(BoneName, PositionalKeys, RotationalKeys, ScaleKeys);
	}
	//AnimController.RemoveBoneTracksMissingFromSkeleton(Skeleton);

	AnimSequence->Modify(true);
	AnimSequence->PostEditChange();
	FAssetRegistryModule::AssetCreated(AnimSequence);
	AnimSequence->MarkPackageDirty();

	for (TObjectIterator<USkeletalMeshComponent> Iter; Iter; ++Iter)
	{
		FComponentReregisterContext ReregisterContext(*Iter);
	}

	return AnimSequence;
}


