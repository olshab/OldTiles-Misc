#include "MapSelectionAnalytics.h"

FMapSelectionAnalytics::FMapSelectionAnalytics()
{
	this->KrakenMatchId = TEXT("");
	this->SelectedMapId = TEXT("");
	this->MapSeed = 0;
	this->MapWeights = TArray<FMapSelectionWeight>();
}
