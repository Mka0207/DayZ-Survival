class ActionConstructor
{
	void ConstructActions(out array<ref ActionBase> actions, out TIntArray suactions, out TIntArray cactions, out TIntArray iactions)
	{
		// SingleUse Actions	
		actions.Insert(new ActionOpen);
		actions.Insert(new ActionClose);
		actions.Insert(new ActionConsumeSingle);
		actions.Insert(new ActionForceConsumeSingle);
		actions.Insert(new ActionTakeABite);
		actions.Insert(new ActionTakeASip);
		actions.Insert(new ActionForceABite);
		actions.Insert(new ActionForceASip);
		actions.Insert(new ActionMeasureBattery);
		actions.Insert(new ActionTurnOnChemlight);
		actions.Insert(new ActionBiteCharcoalTablets);
		actions.Insert(new ActionBitePurificationTablets);
		actions.Insert(new ActionBitePainkillerTablets);
		actions.Insert(new ActionBiteTetracyclineAntibiotics);
		actions.Insert(new ActionBiteVitaminBottle);
		actions.Insert(new ActionForceBitePurificationTablets);
		actions.Insert(new ActionForceBiteCharcoalTablets);
		actions.Insert(new ActionForceBitePainkillerTablets);
		actions.Insert(new ActionForceBiteTetracyclineAntibiotics);
		actions.Insert(new ActionForceBiteVitaminBottle);
		actions.Insert(new ActionMeasureTemperatureSelf);
		actions.Insert(new ActionMeasureTemperatureTarget);
		actions.Insert(new ActionDisinfectSelf);
		actions.Insert(new ActionDisinfectTarget);
		actions.Insert(new ActionPlugIn);
		actions.Insert(new ActionPlugIntoFence);
		actions.Insert(new ActionTogglePlaceObject);
		actions.Insert(new ActionTurnOnWhileInHands);
		actions.Insert(new ActionTurnOffWhileInHands);
		actions.Insert(new ActionPlantSeed);
		actions.Insert(new ActionDisinfectPlantBit);
		actions.Insert(new ActionReadPaper);
		actions.Insert(new ActionTurnOnTorch);
		actions.Insert(new ActionTurnOnHeatpack);
		actions.Insert(new ActionToggleFishing);
		actions.Insert(new ActionAttachToCharger);
		actions.Insert(new ActionTurnOnTransmitter);	
		actions.Insert(new ActionTurnOffTransmitter);
		actions.Insert(new ActionWashHandsItem);
		actions.Insert(new ActionTakeABiteCan);
		actions.Insert(new ActionForceABiteCan);
		actions.Insert(new ActionPlaceFireplaceIndoor);
		actions.Insert(new ActionAttach);
		actions.Insert(new ActionAttachWheels);
		actions.Insert(new ActionPlugTargetIntoThis);
		actions.Insert(new ActionInsertSparkplug);
		actions.Insert(new ActionEmptySeedsPack);
		actions.Insert(new ActionWorldCraftSwitch);
		actions.Insert(new ActionWorldLiquidActionSwitch);
		//actions.Insert(new ActionWorldCraftCancel);
		actions.Insert(new ActionAttachPowerSourceToPanel);
		actions.Insert(new ActionAttachMetalWire);
		actions.Insert(new ActionInjectSelf);
		actions.Insert(new ActionInjectTarget);
		actions.Insert(new ActionInjectEpinephrineSelf);
		actions.Insert(new ActionInjectEpinephrineTarget);
		actions.Insert(new ActionInjectMorphineSelf);
		actions.Insert(new ActionInjectMorphineTarget);
		actions.Insert(new ActionHandcuffTarget);

		//actions.Insert(new ActionLoadMagazineToWeapon);
		//actions.Insert(new ActionLoadBulletToWeapon);
		actions.Insert(new ActionClapBearTrapWithThisItem);
		actions.Insert(new ActionZoomIn);
		actions.Insert(new ActionZoomOut);
		actions.Insert(new ActionPlaceFireplaceIntoBarrel);
		actions.Insert(new ActionStopEngine);
		actions.Insert(new ActionUnfoldMap);

		// Continuous use actions
		//actions.Insert(new ActionCraft);
		actions.Insert(new ActionWorldCraft);
		actions.Insert(new ActionDigStash);
		actions.Insert(new ActionSkinning);
		actions.Insert(new ActionPlaceObject);
		actions.Insert(new ActionDeployObject);
		actions.Insert(new ActionMineTree);
		actions.Insert(new ActionMineBush);
		actions.Insert(new ActionMineRock);
		actions.Insert(new ActionDrinkDisinfectant);
		actions.Insert(new ActionForceDrinkDisinfectant);	
		actions.Insert(new ActionDrinkDisinfectant2);
		actions.Insert(new ActionDigGardenPlot);
		actions.Insert(new ActionWaterPlant);
		actions.Insert(new ActionFertilizeSlot);
		actions.Insert(new ActionDisinfectPlant);
		actions.Insert(new ActionFillObject);
		actions.Insert(new ActionDefibrilateSelf);
		actions.Insert(new ActionDefibrilateTarget);
		actions.Insert(new ActionTestBloodSelf);
		actions.Insert(new ActionTestBloodTarget);
		actions.Insert(new ActionGiveBloodSelf);
		actions.Insert(new ActionGiveBloodTarget);
		actions.Insert(new ActionGiveSalineSelf);
		actions.Insert(new ActionGiveSalineTarget);
		actions.Insert(new ActionCollectBloodSelf);
		actions.Insert(new ActionCollectBloodTarget);
		actions.Insert(new ActionCollectSampleSelf);
		actions.Insert(new ActionCollectSampleTarget);
		actions.Insert(new ActionCoverHeadSelf);
		actions.Insert(new ActionUncoverHeadSelf);
		actions.Insert(new ActionCoverHeadTarget);
		actions.Insert(new ActionShave);
		actions.Insert(new ActionSplintSelf);
		actions.Insert(new ActionSplintTarget);
		actions.Insert(new ActionConsume);
		actions.Insert(new ActionForceConsume);
		actions.Insert(new ActionForceDrink);
		actions.Insert(new ActionForceFeed);
		actions.Insert(new ActionEat);
		actions.Insert(new ActionEatMeat);
		actions.Insert(new ActionEatFruit);
		actions.Insert(new ActionDrink);
		actions.Insert(new ActionDrinkCookingPot);
		actions.Insert(new ActionBandageSelf);
		actions.Insert(new ActionBandageTarget);
		actions.Insert(new ActionRestrainTarget);
		actions.Insert(new ActionPlaceOnGround);
		actions.Insert(new ActionEatCharcoalTablets);
		actions.Insert(new ActionEatPurificationTablets);	
		actions.Insert(new ActionEatPainkillerTablets);
		actions.Insert(new ActionEatTetracyclineAntibiotics);	
		actions.Insert(new ActionEatVitaminBottle);
		actions.Insert(new ActionFeedCharcoalTablets);
		actions.Insert(new ActionFeedPurificationTablets);	
		actions.Insert(new ActionFeedPainkillerTablets);
		actions.Insert(new ActionFeedTetracyclineAntibiotics);
		actions.Insert(new ActionFeedVitaminBottle);
		actions.Insert(new ActionForceDrinkAlcohol);
		actions.Insert(new ActionDrinkAlcohol);
		actions.Insert(new ActionFishing);
		actions.Insert(new ActionFillBottleBase);
		actions.Insert(new ActionTuneFrequency);
		actions.Insert(new ActionTuneRadioStation);
		actions.Insert(new ActionIgniteFireplaceByMatch);
		actions.Insert(new ActionIgniteFireplaceByLighter);
		actions.Insert(new ActionIgniteFireplaceByHandDrill);
		actions.Insert(new ActionIgniteFireplaceByRoadFlare);
		actions.Insert(new ActionExtinguishFireplaceByLiquid);
		actions.Insert(new ActionExtinguishFireplaceByExtinguisher);
		actions.Insert(new ActionBurnSewSelf);
		actions.Insert(new ActionBurnSewTarget);
		actions.Insert(new ActionSewSelf);
		actions.Insert(new ActionSewTarget);
		actions.Insert(new ActionBuryAshes);
		actions.Insert(new ActionCookOnStick);
		actions.Insert(new ActionFillGeneratorTank);
		actions.Insert(new ActionSawPlanks);
		actions.Insert(new ActionBuryBody);
		actions.Insert(new ActionEatCan);
		actions.Insert(new ActionForceFeedCan);
		actions.Insert(new ActionForceFeedMeat);
		actions.Insert(new ActionUseRangefinder);
		actions.Insert(new ActionWaterGardenSlot);
		actions.Insert(new ActionWringClothes);
		actions.Insert(new ActionLoadMagazine);
		actions.Insert(new ActionEmptyMagazine);
		actions.Insert(new ActionConstruct);
		actions.Insert(new ActionDeconstruct);
		actions.Insert(new ActionCPR);
		actions.Insert(new ActionDrinkPondContinuous);
		actions.Insert(new ActionEatSmall);
		actions.Insert(new ActionMineTreeBark);
		actions.Insert(new ActionDigWorms);
		actions.Insert(new ActionShaveTarget);
		actions.Insert(new ActionDrinkWellContinuous);
		actions.Insert(new ActionUncoverHeadTarget);
		actions.Insert(new ActionIgniteFireplaceByAir);
		actions.Insert(new ActionIgniteFireplaceByTorch);
		actions.Insert(new ActionLockDoors);
		actions.Insert(new ActionUnlockDoors);
		actions.Insert(new ActionUnpackBox);
		actions.Insert(new ActionWashHandsWater);
		actions.Insert(new ActionWashHandsWell);
		actions.Insert(new ActionDrinkCan);
		actions.Insert(new ActionStripCarrierVest);
		actions.Insert(new ActionBuildOven);
		actions.Insert(new ActionDismantleOven);
		actions.Insert(new ActionWritePaper);
		actions.Insert(new ActionFillFuel);
		actions.Insert(new ActionPourLiquid);
		actions.Insert(new ActionDrainLiquid);
		actions.Insert(new ActionStartEngine);
		actions.Insert(new ActionViewCompass);
		actions.Insert(new ActionRaiseMegaphone);
		actions.Insert(new ActionActivateTrap);
		actions.Insert(new ActionEmptyBottleBase);
		actions.Insert(new ActionEmptyCookingPot);
		actions.Insert(new ActionViewOptics);
		actions.Insert(new ActionViewBinoculars);
		
		//actions.Insert(new ActionAttached);
		
		// Interact actions
		actions.Insert(new ActionPullOutPlug);
		actions.Insert(new ActionUnplugThisByCord);
		actions.Insert(new ActionTurnOnWhileOnGround);
		actions.Insert(new ActionTurnOffWhileOnGround);
		actions.Insert(new ActionTurnOnPowerGenerator);
		actions.Insert(new ActionTurnOffPowerGenerator);
		actions.Insert(new ActionTurnOnSpotlight);
		actions.Insert(new ActionTurnOffSpotlight);
		actions.Insert(new ActionITest);
		actions.Insert(new ActionRemovePlant);
		actions.Insert(new ActionHarvestCrops);
		actions.Insert(new ActionFoldObject);
		actions.Insert(new ActionDrinkPond);
		actions.Insert(new ActionDrinkWell);
		actions.Insert(new ActionRepositionPluggedItem);
		//actions.Insert(new ActionPickBerry);
		actions.Insert(new ActionTurnOnTransmitterOnGround);
		actions.Insert(new ActionTurnOffTransmitterOnGround);
		actions.Insert(new ActionTuneFrequencyOnGround);
		actions.Insert(new ActionToggleTentOpen);
		actions.Insert(new ActionPackTent);
		actions.Insert(new ActionOpenBarrel);
		actions.Insert(new ActionCloseBarrel);
		actions.Insert(new ActionCoverPlantedSeed);
		actions.Insert(new ActionOpenBarrelHoles);
		actions.Insert(new ActionCloseBarrelHoles);
		actions.Insert(new ActionTakeFireplaceIndoor);
		actions.Insert(new ActionOpenDoors);
		actions.Insert(new ActionCloseDoors);
		actions.Insert(new ActionEnterLadder);
		actions.Insert(new ActionExitLadder);
		actions.Insert(new ActionGetInTransport);
		actions.Insert(new ActionTakeItem);
		actions.Insert(new ActionDetachPowerSourceFromPanel);
		actions.Insert(new ActionSortAmmoPile);
		actions.Insert(new ActionSwapItemToHands);
		actions.Insert(new ActionTakeItemToHands);
		actions.Insert(new ActionLockedDoors);
		actions.Insert(new ActionTakeFireplaceFromBarrel);
		actions.Insert(new ActionOpenCarDoors);
		actions.Insert(new ActionCloseCarDoors);
		actions.Insert(new ActionWashHandsWellOne);
		actions.Insert(new ActionWashHandsWaterOne);
		actions.Insert(new ActionGetOutTransport);
		//actions.Insert(new ActionOpenV3SPlate); <- action doesn't work well, add it later
		//actions.Insert(new ActionCloseV3SPlate); <- action doesn't work well, add it later
		
		//vehicle actions
		actions.Insert(new ActionSwitchLights);
		
		//Instant action - debug
		actions.Insert(new ActionDebug);
		
		//=============================================================
		//uids of SINGLE USE actions for entities without config
		//suactions.Insert();
		
		//uids of CONTINUOUS actions for entities without config
		cactions.Insert(AT_CPR_T); //adds deafult CPR interaction check
		cactions.Insert(AT_DRINK_POND);
		cactions.Insert(AT_DRINK_WELL);
		cactions.Insert(AT_WORLD_CRAFT);		
		cactions.Insert(AT_WASH_HANDS_WATER);
		cactions.Insert(AT_WASH_HANDS_WELL);
		
		//uids of INTERACT actions for entities without config
		iactions.Insert(AT_TAKE_ITEM);
		iactions.Insert(AT_TAKE_ITEM_TO_HANDS);
		//iactions.Insert(AT_SWAP_ITEM_TO_HANDS);
		iactions.Insert(AT_LOCKED_DOORS);
		iactions.Insert(AT_PICK_BERRY);
		//iactions.Insert(AT_DRINK_POND_ONE);
		iactions.Insert(AT_OPEN_DOORS);
		iactions.Insert(AT_CLOSE_DOORS);
		iactions.Insert(AT_ENTER_LADDER);
		iactions.Insert(AT_EXIT_LADDER);
		
		
		//Weapon
		actions.Insert(new FirearmActionAttachMagazine);
		actions.Insert(new FirearmActionLoadMultiBullet);
		actions.Insert(new FirearmActionLoadBullet);
	}
};