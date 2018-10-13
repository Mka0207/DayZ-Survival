#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\Custom_SpawnSelect.c"
//#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\Custom_SpawnPoints.c"
#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\Custom_Buildings.c"
#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\Custom_Adverts.c"
#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\Custom_CacheBase.c"
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
	AddBuildings()
	AddSpawnStuff()
	
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
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);
		
		GetGame().SelectPlayer(identity, m_player);
		
		return m_player;
	}
	
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
/*
		player.RemoveAllItems();

		EntityAI item = player.GetInventory().CreateInInventory(topsArray.GetRandomElement());
		EntityAI item2 = player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		EntityAI item3 = player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
*/
		EntityAI itemEnt;
		ItemBase itemBs;
		Magazine mag = player.GetHumanInventory().CreateInInventory("Mag_IJ70_8Rnd");
		Weapon wpn = player.GetHumanInventory().CreateInHands("MakarovIJ70");
		player.GetWeaponManager().AttachMagazine(mag);
		player.GetInventory().CreateInInventory("StoneKnife");


	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate( timeslice );
	
		//Custom
		curr_event.OnEventTick(timeslice);
		spwn_hub.OnHubTick(timeslice);
		OnTickAdverts( timeslice );
	}	
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
}