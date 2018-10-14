//Event System by mka0207@fwkzt.com

class CustomEventsSurvival
{
	void CustomEventsSurvival()
	{
	}
	
	void ~CustomEventsSurvival()
	{
	}
	
	float Mission_FloatTime = 0.0;
	float Mission_AdvertTime = 0.0;

	const float EVENT_START_INTERVAL = 120;
	const float EVENT_END_INTERVAL = 600;
	
	bool IsEventRunning = false;
	
	string selected_event;
	vector cleanup_vector;
	float cleanup_radius;
	int EVENT_NOTIFY_DELAY;
	int NUM_OF_EVENT_ZOMBIES;
	int LAST_EVENT_NUM = 0;
	int TimesAdverted = 0;
	
	//Make sure this stays correct.
	int MAX_NUM_OF_EVENTS = 5;

	bool FireOnlyOnce;
	bool NoCleanUp;
	bool FirstWarningFired = false;
	bool SecondWarningFired = false;
	bool ThirdWarningFired = false;
	bool FourthWarningFired = false;

	//ItemBase Item_0;
	ItemBase Item_1;
	ItemBase Item_2;
	ItemBase Item_3;
	ItemBase Item_4;

	//vector Item_0_Pos;
	vector Item_1_Pos;
	vector Item_2_Pos;
	vector Item_3_Pos;
	vector Item_4_Pos;

	//vector Item_0_Axis;
	vector Item_1_Axis;
	vector Item_2_Axis;
	vector Item_3_Axis;
	vector Item_4_Axis;
	
	void OnEventTick(float CurTime)
	{
		Mission_FloatTime += CurTime;
		Mission_AdvertTime += CurTime;
		
		if ( Mission_FloatTime > EVENT_START_INTERVAL && !IsEventRunning )
        {
			StartEvent();
			IsEventRunning = true;
			Mission_FloatTime = 0;
			Mission_AdvertTime = 0;
		}

		if ( Mission_AdvertTime > 120 && IsEventRunning && !FirstWarningFired )
		{
			GetGame().ChatPlayer( 1, "Gear Cache Active!" );
			GetGame().ChatPlayer( 1, selected_event );
			GetGame().ChatPlayer( 1, "8 minutes left!" );
			Mission_AdvertTime = 0;
			FirstWarningFired = true;
		}
		
		if ( Mission_AdvertTime > 120 && IsEventRunning && !SecondWarningFired )
		{
			GetGame().ChatPlayer( 1, "Gear Cache Active!" );
			GetGame().ChatPlayer( 1, selected_event );
			GetGame().ChatPlayer( 1, "6 minutes left!" );
			Mission_AdvertTime = 0;
			SecondWarningFired = true;
		}
		
		if ( Mission_AdvertTime > 120 && IsEventRunning && !ThirdWarningFired )
		{
			GetGame().ChatPlayer( 1, "Gear Cache Active!" );
			GetGame().ChatPlayer( 1, selected_event );
			GetGame().ChatPlayer( 1, "4 minutes left!" );
			Mission_AdvertTime = 0;
			ThirdWarningFired = true;
		}
		
		if ( Mission_AdvertTime > 120 && IsEventRunning && !FourthWarningFired )
		{
			GetGame().ChatPlayer( 1, "Gear Cache Active!" );
			GetGame().ChatPlayer( 1, selected_event );
			GetGame().ChatPlayer( 1, "2 minutes left!" );
			Mission_AdvertTime = 0;
			FourthWarningFired = true;
		}

		if ( Mission_FloatTime > EVENT_END_INTERVAL && IsEventRunning )
        {
            EndEvent();
			IsEventRunning = false;
			Mission_FloatTime = 0;
			Mission_AdvertTime = 0;
			
			FirstWarningFired = false;
			SecondWarningFired = false;
			ThirdWarningFired = false;
			FourthWarningFired = false;
	    }
	}

	void AnnounceEvent(string EventLocation)
	{
		GetGame().ChatPlayer( 1, "Gear Cache Sighted!" );
		GetGame().ChatPlayer( 1, EventLocation );
	}
	
	void CreateContainrItems(ItemBase item)
	{
		int RandomItemsChance = Math.RandomIntInclusive( 1, 4 );

		if ( RandomItemsChance == 1 )
		{
			EntityAI wep_attach_1;
			EntityAI wep_attach_2;
			EntityAI wep_M4A1 = item.GetInventory().CreateInInventory( "M4A1_Green" );

			wep_M4A1.GetInventory().CreateAttachment( "M4_CQBBttstck_Green" );
			wep_M4A1.GetInventory().CreateAttachment( "M4_MPHndgrd_Green" );
			wep_M4A1.GetInventory().CreateAttachment( "M4_Suppressor" );
			wep_M4A1.GetInventory().CreateAttachment( "GhillieAtt_Mossy" );
			wep_attach_1 = wep_M4A1.GetInventory().CreateAttachment( "AcogOptic" );
			wep_attach_1.GetInventory().CreateAttachment( "Battery9V" );

			item.GetInventory().CreateInInventory( "Mag_StanagCoupled_30Rnd" ); 
			item.GetInventory().CreateInInventory( "Mag_StanagCoupled_30Rnd" ); 
			item.GetInventory().CreateInInventory( "Mag_StanagCoupled_30Rnd" );

			item.GetInventory().CreateInInventory( "BallisticHelmet_Green" ); 

			wep_attach_2 = item.GetInventory().CreateInInventory( "M68Optic" );
			wep_attach_2.GetInventory().CreateAttachment( "Battery9V" );
		}

		if ( RandomItemsChance == 2 )
		{
			item.GetInventory().CreateInInventory( "GhillieHood_Mossy" ); 
			item.GetInventory().CreateInInventory( "GhillieSuit_Mossy" );

			item.GetInventory().CreateInInventory( "Rangefinder" );
			item.GetInventory().CreateInInventory( "Binoculars" );
			item.GetInventory().CreateInInventory( "ImprovisedSuppressor" );
		}

		if ( RandomItemsChance == 3 )
		{
			EntityAI wep2_attack_1;
			EntityAI wep2_attack_2;
			EntityAI wep_AKM = item.GetInventory().CreateInInventory( "AKM" );
			wep_AKM.GetInventory().CreateAttachment( "AK_WoodBttstck_Camo" );
			wep_AKM.GetInventory().CreateAttachment( "AK_Bayonet" );
			wep_AKM.GetInventory().CreateAttachment( "AK_WoodHndgrd_Camo" );
			wep_AKM.GetInventory().CreateAttachment( "AK_Suppressor" );
			wep_AKM.GetInventory().CreateAttachment( "GhillieAtt_Mossy" );
			wep2_attack_1 = wep_AKM.GetInventory().CreateAttachment( "PSO1Optic" );
			wep2_attack_1.GetInventory().CreateAttachment( "Battery9V" );

			item.GetInventory().CreateInInventory( "Mag_AKM_Drum75Rnd" ); 
			item.GetInventory().CreateInInventory( "Mag_AKM_Drum75Rnd" ); 
			item.GetInventory().CreateInInventory( "Mag_AKM_Drum75Rnd" ); 

			item.GetInventory().CreateInInventory( "BallisticHelmet_Green" ); 
			wep2_attack_2 = item.GetInventory().CreateInInventory( "KobraOptic" );
			wep2_attack_2.GetInventory().CreateAttachment( "Battery9V" );
		}

		if ( RandomItemsChance == 4 )
		{
			item.GetInventory().CreateInInventory( "GreatHelm" );
			item.GetInventory().CreateInInventory( "PressVest_Blue" );
		}
	}
	
	void CreateFlareEnt(float x, float y, float z, float yaw, float pitch, float roll)
	{
		ItemGrenade m_Flare;
		m_Flare = g_Game.CreateObject("RDG2SmokeGrenade_Black", Vector(x, y, z), false);
		m_Flare.SetOrientation(Vector(yaw, pitch, roll));
		
		//Turn the smoke on.
		m_Flare.GetCompEM().SwitchOn();
		m_Flare.SetTakeable(false);
	}

	void DestroyFlareEnt()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(CreateFlareEnt);
	}

	TStringArray GrabRandomZombieClass()
	{
		return {
		"ZmbM_Soldier", 
		"ZmbM_SoldierAlice", 
		"ZmbM_SoldierHelmet", 
		"ZmbM_SoldierVest", 
		"ZmbM_SoldierAliceHelmet", 
		"ZmbM_SoldierVestHelmet", 
		"ZmbM_HunterOld_Autumn", 
		"ZmbM_HunterOld_Spring", 
		"ZmbM_HunterOld_Summer", 
		"ZmbM_HunterOld_Winter"};
	}
	
	//Clean up those spooky zombies!
	void DoEventCleanUp(float x, float y, float z, float radius)
	{
		ref array<Object> Event_Items = new array<Object>;
		GetGame().GetObjectsAtPosition( Vector(x,y,z), radius, Event_Items, NULL );

		if ( GetGame() && Event_Items )
		{
			if ( Event_Items.Count() >= 1 ) 
			{
				for ( int i = 0; i < Event_Items.Count(); i++ )
				{
					Object z_ent = Event_Items.Get( i );

					//Zombies
					if ( z_ent.IsInherited(ZombieBase) )
					{
						GetGame().ObjectDelete(z_ent);
					}
					
				    //Barrels
					if ( z_ent.IsInherited(Barrel_ColorBase) )
					{
						GetGame().ObjectDelete(z_ent);
					}
					
					//SeaChests
					if ( z_ent.GetType() == "SeaChest" )
					{
						GetGame().ObjectDelete(z_ent);
					}
					
					//Smoke Grenades
					if ( z_ent.GetType() == "Wreck_UH1Y" )
					{
						z_ent.SetPosition( Vector( 0, 0, 0 ) );
						//GetGame().ObjectDelete(z_ent);
					}
					
					//Remove Melee, Firearms, Clothing and all other items dropped.
					/* if ( z_ent.IsWeapon() || z_ent.IsClothing() || z_ent.IsMeleeWeapon() || z_ent.IsMagazine() )  //item.IsMan() && !item.IsAlive()
					{	
						//Print("[DEBUG] - Removed Item "+item.GetType() + " idx = " + i.ToString());
						GetGame().ObjectDelete(z_ent);
					} */
				}
			}
		}
	}

	int random_event_chance = 0;
	void StartEvent()
	{	
		if ( random_event_chance == MAX_NUM_OF_EVENTS + 1 )
		{
			random_event_chance = 0;
		}
		random_event_chance++;
		int i;

		//Balota Coast Near ATC.
		if ( random_event_chance == 1 )
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CreateFlareEnt, 8500, true, 5019.09, 3.95992, 2008.58, 2, -1.09999, -4.44645);
			
			
			//Zombies
			NUM_OF_EVENT_ZOMBIES = 25;
			for ( i = 0; i < NUM_OF_EVENT_ZOMBIES; i++ )
			{
				g_Game.CreateObject(GrabRandomZombieClass().GetRandomElement(), Vector(Math.RandomFloatInclusive(4998, 5052), 0, Math.RandomFloatInclusive(1992, 2014)), false, true );
			}

			selected_event = "Balota airfield!";
			cleanup_vector = Vector( 5021.9, 3.93442, 2010.06 );
			cleanup_radius = 250.0;
			NoCleanUp = false;

			AnnounceEvent(selected_event);
		}

		//Balota AirField NE Hill Across from ATC.
		if ( random_event_chance == 2 )
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CreateFlareEnt, 8500, true, 5494.71, 47.5657, 2205.06, 0, 13, 1);
			
			//SeaChests
			Item_1_Pos = "5495.72 44.9966 2201.6";
			Item_1_Axis = "147.388 -10.768 5.57808";
			Item_1 = g_Game.CreateObject("SeaChest", Item_1_Pos, false);
			Item_1.SetOrientation(Item_1_Axis);
			CreateContainrItems(Item_1);
	
			Item_2_Pos = "5496.89 45.62 2204.02";
			Item_2_Axis = "84.1955 2.90348 21.2722";
			Item_2 = g_Game.CreateObject("SeaChest", Item_2_Pos, false);
			Item_2.SetOrientation(Item_2_Axis);
			CreateContainrItems(Item_2);
	
			Item_3_Pos = "5491.84 44.5761 2201.03";
			Item_3_Axis = "16.4995 17.5878 -7.2719";
			Item_3 = g_Game.CreateObject("SeaChest", Item_3_Pos, false);
			Item_3.SetOrientation(Item_3_Axis);
			CreateContainrItems(Item_3);

			//Zombies
			NUM_OF_EVENT_ZOMBIES = 25;
			for ( i = 0; i < NUM_OF_EVENT_ZOMBIES; i++ )
			{
				g_Game.CreateObject(GrabRandomZombieClass().GetRandomElement(), Vector(Math.RandomFloatInclusive(5483, 5535), 0, Math.RandomFloatInclusive(2215, 2256)), false, true );
			}

			selected_event = "Hill Across from ATC";
			cleanup_vector = Vector( 5495.72, 44.9966, 2201.6 );
			cleanup_radius = 250.0;
			NoCleanUp = false;

			AnnounceEvent(selected_event);
		}

		//Balota Town NW Hill
		if ( random_event_chance == 3 )
		{
	
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CreateFlareEnt, 8500, true, 4717.84, 65.29, 2932.43, 26.8815, 2.5061, 5.20263);
			
			//Barrels
			Item_1_Pos = "4721.31 65.67 2932.7";
			Item_1_Axis = "-50.52 4.11 -14.84";
			Item_1 = g_Game.CreateObject("Barrel_green", Item_1_Pos, false);
			Item_1.SetOrientation(Item_1_Axis);
			Item_1.Open();
			CreateContainrItems(Item_1);
	
			Item_2_Pos = "4720.49 66.05 2934.52";
			Item_2_Axis = "60.41 13.49 8.32";
			Item_2 = g_Game.CreateObject("Barrel_red", Item_2_Pos, false);
			Item_2.SetOrientation(Item_2_Axis);
			Item_2.Open();
			CreateContainrItems(Item_2);

			Item_3_Pos = "4718.26 66.0143 2935.42";
			Item_3_Axis = "-57.3 2.15 -15.21";
			Item_3 = g_Game.CreateObject("Barrel_blue", Item_3_Pos, false);
			Item_3.SetOrientation(Item_3_Axis);
			Item_3.Open();
			CreateContainrItems(Item_3);

			//Zombies
			NUM_OF_EVENT_ZOMBIES = 25;
			for ( i = 0; i < NUM_OF_EVENT_ZOMBIES; i++ )
			{
				g_Game.CreateObject(GrabRandomZombieClass().GetRandomElement(), Vector(Math.RandomFloatInclusive(4720, 4822), 0, Math.RandomFloatInclusive(2812, 2915)), false, true );
			}

			selected_event = "Balota Town NW Hill";
			cleanup_vector = Vector( 4721.31, 65.67, 2932.7 );
			cleanup_radius = 250.0;
			NoCleanUp = false;
	
			AnnounceEvent(selected_event);
		}

		//Balota_Barn_Fields West
		if ( random_event_chance == 4 )
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CreateFlareEnt, 8500, true, 4259.18, 8.31229, 2773.94, 26.8815, 2.5061, 5.20263);
			
			//SeaChests
			Item_1_Pos = "4258.03 8.07743 2771.52";
			Item_1_Axis = "0.3979 2.22964 -1.19725";
			Item_1 = g_Game.CreateObject("SeaChest", Item_1_Pos, false);
			Item_1.SetOrientation(Item_1_Axis);
			CreateContainrItems(Item_1);

			Item_2_Pos = "4261.77 8.37863 2775.05";
			Item_2_Axis = "-135.114 -3.29099 1.27619";
			Item_2 = g_Game.CreateObject("SeaChest", Item_2_Pos, false);
			Item_2.SetOrientation(Item_2_Axis);
			CreateContainrItems(Item_2);

			Item_3_Pos = "4256.82 8.21078 2776.04";
			Item_3_Axis = "125.984 3.03312 -0.153311";
			Item_3 = g_Game.CreateObject("SeaChest", Item_3_Pos, false);
			Item_3.SetOrientation(Item_3_Axis);
			CreateContainrItems(Item_3);

			//Zombies
			NUM_OF_EVENT_ZOMBIES = 30;
			for ( i = 0; i < NUM_OF_EVENT_ZOMBIES; i++ )
			{
				g_Game.CreateObject(GrabRandomZombieClass().GetRandomElement(), Vector(Math.RandomFloatInclusive(4229, 4287), 0, Math.RandomFloatInclusive(2710, 2845)), false, true );
			}

			selected_event = "Balota Town West Field!";
			cleanup_vector = Vector( 4258.03, 8.07743, 2771.52 );
			cleanup_radius = 250.0;
			NoCleanUp = false;

			AnnounceEvent(selected_event);
		}

		//Zombie Overrun Balota Airfield.
		if ( random_event_chance == 5 )
		{
			if ( !FireOnlyOnce )
			{
				//Zombies
				for ( i = 0; i < NUM_OF_EVENT_ZOMBIES; i++ )
				{
					g_Game.CreateObject(GrabRandomZombieClass().GetRandomElement(), Vector(Math.RandomFloatInclusive(5000, 5270), 0, Math.RandomFloatInclusive(2333, 2474)), false, true );
				}

				for ( int i_2 = 0; i_2 < NUM_OF_EVENT_ZOMBIES; i_2++ )
				{
					g_Game.CreateObject(GrabRandomZombieClass().GetRandomElement(), Vector(Math.RandomFloatInclusive(5112, 5340), 0, Math.RandomFloatInclusive(2191, 2224)), false, true );
				}

				for ( int i_3 = 0; i_3 < NUM_OF_EVENT_ZOMBIES; i_3++ )
				{
					g_Game.CreateObject(GrabRandomZombieClass().GetRandomElement(), Vector(Math.RandomFloatInclusive(4900, 5090), 0, Math.RandomFloatInclusive(2560, 2920)), false, true );
				}

				NoCleanUp = true;
				FireOnlyOnce = true;
				
				//Tell everyone the event is active.
				GetGame().ChatPlayer( 1, "Zombie Horde Spotted!" );
				GetGame().ChatPlayer( 1, "Balota Airfield is overrun!" );
			}
			else
			{
				//Airfield Chest Alternate.
				Item_1_Pos = "5097.79 9.50848 2360.05";
				Item_1_Axis = "-178.671 -0.47595 0.783043";
				Item_1 = g_Game.CreateObject("Barrel_Red", Item_1_Pos, false);
				Item_1.SetOrientation(Item_1_Axis);
				CreateContainrItems(Item_1);

				Item_2_Pos = "5105.22 9.50898 2351";
				Item_2_Axis = "-169.157 -0.593875 0.664015";
				Item_2 = g_Game.CreateObject("Barrel_Green", Item_2_Pos, false);
				Item_2.SetOrientation(Item_2_Axis);
				CreateContainrItems(Item_2);

				Item_3_Pos = "5114.63 9.49881 2360.64";
				Item_3_Axis = "173.049 -0.186891 2.2534";
				Item_3 = g_Game.CreateObject("Barrel_Yellow", Item_3_Pos, false);
				Item_3.SetOrientation(Item_3_Axis);
				CreateContainrItems(Item_3);
				
				//Zombies
				NUM_OF_EVENT_ZOMBIES = 30;
				for ( i = 0; i < NUM_OF_EVENT_ZOMBIES; i++ )
				{
					g_Game.CreateObject(GrabRandomZombieClass().GetRandomElement(), Vector(Math.RandomFloatInclusive(4229, 4287), 0, Math.RandomFloatInclusive(2710, 2845)), false, true );
				}

				selected_event = "Balota Airfield!";
				cleanup_vector = Vector( 5097.79, 9.50848, 2360.05 );
				cleanup_radius = 250.0;
				NoCleanUp = false;
				
				AnnounceEvent(selected_event);
			}
		}
	}

	void CleanUp()
	{
		if ( NoCleanUp == true ) return;
		
		//DestroyFlareEnt();
		DoEventCleanUp( cleanup_vector[0], cleanup_vector[1], cleanup_vector[2], cleanup_radius );
	}

	void EndEvent()
	{
		CleanUp();
		GetGame().ChatPlayer( 1, "Gear Cache Expired!" );
		GetGame().ChatPlayer( 1, "Next Gear Cache in 2 mins!" );
	}
}