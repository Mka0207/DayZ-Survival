#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\Custom_SpawnSelect.c"
void main()
{

	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	Weather weather = g_Game.GetWeather();

	weather.GetOvercast().SetLimits( 0.0 , 1.0 );
	weather.GetRain().SetLimits( 0.0 , 1.0 );
	weather.GetFog().SetLimits( 0.0 , 0.25 );

	weather.GetOvercast().SetForecastChangeLimits( 0.0, 0.2 );
	weather.GetRain().SetForecastChangeLimits( 0.0, 0.1 );
	weather.GetFog().SetForecastChangeLimits( 0.15, 0.45 );

	weather.GetOvercast().SetForecastTimeLimits( 1800 , 1800 );
	weather.GetRain().SetForecastTimeLimits( 600 , 600 );
	weather.GetFog().SetForecastTimeLimits( 1800 , 1800 );

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.0, 0.3), 0, 0);
	weather.GetRain().Set( Math.RandomFloatInclusive(0.0, 0.2), 0, 0);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.0, 0.1), 0, 0);
	
	weather.SetWindMaximumSpeed(15);
	weather.SetWindFunctionParams(0.1, 0.3, 50);
	
	//Establish our tables.
	ref array<Object> objects = new array<Object>;
	ref array<CargoBase> proxyCargos = new array<CargoBase>;
	
	//Delete any chemlights that persisted past restart
	GetGame().GetObjectsAtPosition( "4121 0 14650", 50.0, objects, proxyCargos );
	
	if ( GetGame() && objects )
	{
		for ( int i = 0; i < objects.Count(); i++ )
		{
			//Handle Cleanup
			Object item = objects.Get( i );
			if ( item )
			{
				if ( item.IsWeapon() || item.IsClothing() || item.IsMeleeWeapon() || item.IsMagazine() )  //item.IsMan() && !item.IsAlive()
				{    
					if ( objects.Count() >= 1 )
					{
						GetGame().ObjectDelete(item);
					}
				}
			}
		}
	}
}

class CustomMission: MissionServer
{	
	ref CustomEventsSurvival curr_event;
	ref SpawnHub spwn_hub;
	
	void CustomMission()
	{
		curr_event = new CustomEventsSurvival();
		spwn_hub = new SpawnHub();
	
	} 
	
	void SetRandomHealth(EntityAI itemEnt)
	{
		int rndHlt = Math.RandomInt(40,100);
		itemEnt.SetHealth("","",rndHlt);
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, "4121 0 14650", 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);
		
		GetGame().SelectPlayer(identity, m_player);
		
		return m_player;
	}
	
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{

		
		EntityAI itemEnt;
		ItemBase itemBs;
		
		itemEnt = player.GetInventory().CreateInInventory("Rag");
		itemBs = ItemBase.Cast(itemEnt);
		itemBs.SetQuantity(4);
		player.GetStatWater().Set(700);

	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate( timeslice );
	
		//Custom
		//curr_event.OnEventTick(timeslice);
		spwn_hub.OnHubTick(timeslice);
		OnTickAdverts( timeslice );
	}	
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
}