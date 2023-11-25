// Fill out your copyright notice in the Description page of Project Settings.

#include "PSKXFactory.h"
#include "PSKReader.h"
#include "RawMesh.h"
#include "AssetRegistry/AssetRegistryModule.h"

UObject* UPSKXFactory::Import(const FString Filename, UObject* Parent, const FName Name, const EObjectFlags Flags) const
{
	const auto Reader = new PSKReader(Filename);
	if (!Reader->Read())
	{
		return nullptr;
	}
	auto bHasNormals = Reader->Normals.Num() > 0;
	auto bHasVertexColors = Reader->VertexColors.Num() > 0;

	TArray<FColor> FaceVertexColors;
	FaceVertexColors.Init(FColor::White, Reader->VertexColors.Num());
	if (bHasVertexColors)
	{
		for (auto i = 0; i < Reader->Wedges.Num(); i++)
		{
			auto FixedColor = Reader->VertexColors[i];
			Swap(FixedColor.R, FixedColor.B);
			FaceVertexColors[Reader->Wedges[i].PointIndex] = FixedColor;
		}
	}
	auto RawMesh = FRawMesh();
	for (auto Vertex : Reader->Vertices)
	{
		auto FixedVertex = Vertex;
		FixedVertex.Y = -FixedVertex.Y; // mirror y axis cuz ue dumb dumb
		RawMesh.VertexPositions.Add(FixedVertex);
	}

	for (const auto Face : Reader->Faces)
	{
		for (auto VtxIdx = 2; VtxIdx >= 0; VtxIdx--) // reverse face winding to account for -y vertex pos
		{
			const auto Wedge = Reader->Wedges[Face.WedgeIndex[VtxIdx]];

			RawMesh.WedgeIndices.Add(Wedge.PointIndex);
			RawMesh.WedgeTexCoords[0].Add(FVector2D(Wedge.U, Wedge.V));

			for (auto UVIdx = 0; UVIdx < Reader->ExtraUVs.Num(); UVIdx++)
			{
				auto UV = Reader->ExtraUVs[UVIdx][Face.WedgeIndex[VtxIdx]];
				RawMesh.WedgeTexCoords[UVIdx + 1].Add(FVector2D(UV.X, UV.Y));
			}

			auto Normal = FVector::ZeroVector;

			if (bHasNormals)
			{
				Normal = Reader->Normals[Wedge.PointIndex];
				Normal.Y = -Normal.Y;
			}

			RawMesh.WedgeTangentZ.Add(Normal);
			RawMesh.WedgeTangentY.Add(FVector::ZeroVector);
			RawMesh.WedgeTangentX.Add(FVector::ZeroVector);

			if (bHasVertexColors) RawMesh.WedgeColors.Add(FaceVertexColors[Wedge.PointIndex]);
		}
		
		RawMesh.FaceMaterialIndices.Add(Face.MatIndex);
		RawMesh.FaceSmoothingMasks.Add(1);
	}

	const auto StaticMesh = CastChecked<UStaticMesh>(CreateOrOverwriteAsset(UStaticMesh::StaticClass(), Parent, Name, Flags));
	
	auto& SourceModel = StaticMesh->AddSourceModel();
	SourceModel.BuildSettings.bBuildReversedIndexBuffer = false;
	SourceModel.BuildSettings.bRecomputeTangents = false;
	SourceModel.BuildSettings.bGenerateLightmapUVs = false;
	SourceModel.BuildSettings.bComputeWeightedNormals = false;
	SourceModel.BuildSettings.bRecomputeNormals = !bHasNormals;
	SourceModel.SaveRawMesh(RawMesh);


	TArray<FStaticMaterial> StaticMaterials;

	for (const VMaterial Material : Reader->Materials)
	{
		FString MaterialName = FString(ANSI_TO_TCHAR(Material.MaterialName));

		FStaticMaterial StaticMaterial;
		StaticMaterial.ImportedMaterialSlotName = *MaterialName;
		StaticMaterial.MaterialSlotName = *MaterialName;

		StaticMaterials.Add(StaticMaterial);

		UE_LOG(LogTemp, Warning, TEXT("%s"), *MaterialName);
	}

	StaticMesh->SetStaticMaterials(StaticMaterials);


	StaticMesh->Build();
	StaticMesh->PostEditChange();
	FAssetRegistryModule::AssetCreated(StaticMesh);
	StaticMesh->MarkPackageDirty();
	return StaticMesh;
}
