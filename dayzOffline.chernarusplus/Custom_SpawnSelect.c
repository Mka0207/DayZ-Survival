//Custom spawn point select
#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\Custom_SpawnPoints.c"

TVectorArray RandomCherno = ChernoSpawns();
TVectorArray RandomElectro = ElectroSpawns();
TVectorArray RandomEast = EastSpawns();
TVectorArray RandomRando = RandoSpawns();

class SpawnHub
{
	const float TELEPORT_COOLDOWN = 10;
	const float TELEPORT_COOLDOWN_DELAY = 12;
	
	protected float m_TeleportCheckTimer = 0.0;
	protected float m_TeleportCheckTimerDelay = 0.0;
	
	const float HUB_RADIUS = 4.7;
	
	string NAME_CHERNO = "Cherno";
	string NAME_ELECTRO = "Electro";
	string NAME_EAST = "East";
	string NAME_RANDOM = "Random";
	
	vector CHERNO_HUB = "4132.42 352.4 14657.9";
	vector ELECTRO_HUB = "4132.97 352.45 14644.2";
	vector EAST_HUB = "4138.68 352.4 14644.2";
	vector RANDOM_HUB = "4138 352 14657.9";
	
	PlayerBase Players_Cherno;
	PlayerBase Players_Electro;
	PlayerBase Players_East;
	PlayerBase Players_Random;

	void SpawnHub()
	{
		
	}
	
	void ~SpawnHub()
	{
		
	}
	
	void OnHubTick(float curTime)
	{
		m_TeleportCheckTimer += curTime; 
		m_TeleportCheckTimerDelay += curTime;  
  		
		if ( m_TeleportCheckTimer > TELEPORT_COOLDOWN )
		{
			Players_Cherno = GetPlayersToTeleport( NAME_CHERNO, CHERNO_HUB, HUB_RADIUS );
			GiveStuff( Players_Cherno );
			
			Players_Electro = GetPlayersToTeleport( NAME_ELECTRO, ELECTRO_HUB, HUB_RADIUS );
			GiveStuff( Players_Electro );
			
			Players_East = GetPlayersToTeleport( NAME_EAST, EAST_HUB, HUB_RADIUS );
			GiveStuff( Players_East );
			
			Players_Random = GetPlayersToTeleport( NAME_RANDOM, RANDOM_HUB, HUB_RADIUS );
			GiveStuff( Players_Random );
			
			m_TeleportCheckTimer = 0;
		}
		
		if ( m_TeleportCheckTimerDelay > TELEPORT_COOLDOWN_DELAY )
		{
			PlayerBase Players_Cherno = GetPlayersToTeleport( NAME_CHERNO, CHERNO_HUB, HUB_RADIUS );
			SendPlayer( Players_Cherno, NAME_CHERNO );
			
			PlayerBase Players_Electro = GetPlayersToTeleport( NAME_ELECTRO, ELECTRO_HUB, HUB_RADIUS );
			SendPlayer( Players_Electro, NAME_ELECTRO );
			
			PlayerBase Players_East = GetPlayersToTeleport( NAME_EAST, EAST_HUB, HUB_RADIUS );
			SendPlayer( Players_East, NAME_EAST );
			
			PlayerBase Players_Random = GetPlayersToTeleport( NAME_RANDOM, RANDOM_HUB, HUB_RADIUS );
			SendPlayer( Players_Random, NAME_RANDOM );
			
			m_TeleportCheckTimerDelay = 0;
		}
	}
	
	void SendPlayer( PlayerBase entity, string LocationStuff )
	{
		if ( LocationStuff == "Cherno" )
		{
			entity.SetPosition( RandomCherno.GetRandomElement() );
		}
		if ( LocationStuff == "Electro" )
		{
			entity.SetPosition( RandomElectro.GetRandomElement() );
		}
		if ( LocationStuff == "East" )
		{
			entity.SetPosition( RandomEast.GetRandomElement() );
		}
		if ( LocationStuff == "Random" )
		{
			entity.SetPosition( RandomRando.GetRandomElement() );
		}
	}
	
	void GiveStuff( PlayerBase ply )
	{
		EntityAI itemEnt;
		itemEnt = ply.GetInventory().CreateInInventory("Mag_IJ70_8Rnd");
		ply.GetInventory().CreateInInventory("MakarovIJ70");
		ply.GetInventory().CreateInInventory("Compass");
	}
	
	PlayerBase GetPlayersToTeleport( string LocationName, vector HubLocation, float HubRadius )
	{
		ref array<Object> players = new array<Object>;
		GetGame().GetObjectsAtPosition( HubLocation, HubRadius, players, NULL );
		PlayerBase player;
		
		for ( int i = 0; i < players.Count(); i++ )
		{
			Object obj_ent = players.Get( i );
			if ( obj_ent ) 
			{
				if ( obj_ent.IsMan() )
				{    
					player = PlayerBase.Cast( obj_ent );
				}
			}
		}	
		
		return player;
	}
}

void AddSpawnStuff()
{
	
	//Green shed
	Building m_spwn1;
    vector spwn1_pos;
    vector spwn1_dir;
   
    spwn1_pos[0] = 4132.42;
    spwn1_pos[1] = 352.4;
    spwn1_pos[2] = 14657.9;
 
    spwn1_dir[0] = 0;
    spwn1_dir[1] = 0;
    spwn1_dir[2] = 0;

	m_spwn1 = g_Game.CreateObject("Land_Shed_W6", spwn1_pos, false);
	m_spwn1.SetOrientation(spwn1_dir);
	m_spwn1.OpenDoor(1);
	m_spwn1.OpenDoor(0);
	
	//4129.94, 4134.77
	//14654.5, 14662
	
	//proto HLIGHT AddLight(IEntity owner, LightType spot, LightFlags dynamic, float 1, 4118 350 14650 green);
	
	//Green chemlight on map	
	ItemBase m_spwn2;
	ItemBase m_spwn22;
    vector spwn2_pos;
    vector spwn2_dir;
   
    spwn2_pos[0] = 4118.32;
    spwn2_pos[1] = 350.604;
    spwn2_pos[2] = 14650.1;
 
    spwn2_dir[0] = 96.7628;
    spwn2_dir[1] = 89.9234;
    spwn2_dir[2] = -176.692;

	m_spwn2 = g_Game.CreateObject("Chemlight_Green", spwn2_pos, false);
	m_spwn22 = g_Game.CreateObject("Armband_Green", spwn2_pos, false);	
	m_spwn2.SetOrientation(spwn2_dir);
	m_spwn2.GetCompEM().SwitchOn();
	m_spwn2.GetCompEM().SetEnergy(15400);
	m_spwn2.SetPosition(spwn2_pos); 
	m_spwn22.SetPosition(spwn2_pos); 
	m_spwn2.SetTakeable(false);
	m_spwn22.SetTakeable(false);
	


	
	
	 //Green chemlight in shed	
	ItemBase m_spwn3;
    vector spwn3_pos;
    vector spwn3_dir;
   
    spwn3_pos[0] = 4132.42;
    spwn3_pos[1] = 354.5;
    spwn3_pos[2] = 14657.9;
 
    spwn3_dir[0] = 0;
    spwn3_dir[1] = 0;
    spwn3_dir[2] = 0;

	m_spwn3 = g_Game.CreateObject("Chemlight_Green", spwn3_pos, false);
	m_spwn3.SetOrientation(spwn3_dir);
	m_spwn3.GetCompEM().SwitchOn();	 
	m_spwn3.GetCompEM().SetEnergy(15400);
	m_spwn3.SetTakeable(false);
	m_spwn3.SetPosition(spwn3_pos);
	
	
	//Blue shed	
	Building m_spwn4;
    vector spwn4_pos;
    vector spwn4_dir;
   
    spwn4_pos[0] = 4132.97;
    spwn4_pos[1] = 352.45;
    spwn4_pos[2] = 14644.2;
 
    spwn4_dir[0] = 180;
    spwn4_dir[1] = 0;
    spwn4_dir[2] = 0;

	m_spwn4 = g_Game.CreateObject("Land_Shed_W6", spwn4_pos, false);
	m_spwn4.SetOrientation(spwn4_dir);
	m_spwn4.OpenDoor(1);
	m_spwn4.OpenDoor(0);
	
	//4130.62, 4135.35
	//14640.1, 14648.2
	
	 //Blue chemlight on map
	ItemBase m_spwn5;
	ItemBase m_spwn55;
    vector spwn5_pos;
    vector spwn5_dir;

    spwn5_pos[0] = 4118.45;
    spwn5_pos[1] = 350.498;
    spwn5_pos[2] = 14650.5;
 
    spwn5_dir[0] = 162.114;
    spwn5_dir[1] = -86.9347;
    spwn5_dir[2] = -63.5597;

	m_spwn5 = g_Game.CreateObject("Chemlight_Blue", spwn5_pos, false);
	m_spwn55 = g_Game.CreateObject("Armband_Blue", spwn5_pos, false);
	m_spwn5.SetOrientation(spwn2_dir);
	m_spwn5.GetCompEM().SwitchOn();
	m_spwn5.GetCompEM().SetEnergy(15400);
	m_spwn5.SetPosition(spwn5_pos);
	m_spwn55.SetPosition(spwn5_pos);
	m_spwn5.SetTakeable(false);
	m_spwn55.SetTakeable(false);
	
	
	 //Blue chemlight in shed
	ItemBase m_spwn6;
    vector spwn6_pos;
    vector spwn6_dir;
   
    spwn6_pos[0] = 4132.31;
    spwn6_pos[1] = 354.315;
    spwn6_pos[2] = 14644.8;
 
    spwn6_dir[0] = 0;
    spwn6_dir[1] = 0;
    spwn6_dir[2] = 0;

	m_spwn6 = g_Game.CreateObject("Chemlight_Blue", spwn6_pos, false);
	m_spwn6.SetOrientation(spwn6_dir);
	m_spwn6.GetCompEM().SwitchOn();
	m_spwn6.GetCompEM().SetEnergy(15400);
	m_spwn6.SetTakeable(false);
	m_spwn6.SetPosition(spwn6_pos);
	
	 
	
	//Red shed
	Building m_spwn7;
    vector spwn7_pos;
    vector spwn7_dir;
	
    spwn7_pos[0] = 4138.68;
    spwn7_pos[1] = 352.45;
    spwn7_pos[2] = 14644.2;
 
    spwn7_dir[0] = 180;
    spwn7_dir[1] = 0;
    spwn7_dir[2] = 0;

	m_spwn7 = g_Game.CreateObject("Land_Shed_W6", spwn7_pos, false);
	m_spwn7.SetOrientation(spwn7_dir);
	m_spwn7.OpenDoor(1);
	m_spwn7.OpenDoor(0);
	
	//4136.47, 14640.1
	//4141.16, 14648.2
	
	//Red chemlight on map
	ItemBase m_spwn8;
	ItemBase m_spwn88;
    vector spwn8_pos;
    vector spwn8_dir;
   
    spwn8_pos[0] = 4118.46;
    spwn8_pos[1] = 351.278;
    spwn8_pos[2] = 14650.8;
 
    spwn8_dir[0] = -21.7279;
    spwn8_dir[1] = 86.9806;
    spwn8_dir[2] = 59.0782

	m_spwn8 = g_Game.CreateObject("Chemlight_Red", spwn8_pos, false);
	m_spwn88 = g_Game.CreateObject("Armband_Red", spwn8_pos, false);	
	m_spwn8.SetOrientation(spwn2_dir);
	m_spwn8.GetCompEM().SwitchOn();
	m_spwn8.GetCompEM().SetEnergy(15400);
	m_spwn8.SetPosition(spwn8_pos); 
	m_spwn88.SetPosition(spwn8_pos); 
	m_spwn8.SetTakeable(false);
	m_spwn88.SetTakeable(false);
	
	
	 //Red chemlight in shed
	ItemBase m_spwn9;
    vector spwn9_pos;
    vector spwn9_dir;
   
    spwn9_pos[0] = 4140.33;
    spwn9_pos[1] = 354.529;
    spwn9_pos[2] = 14645;
 
    spwn9_dir[0] = 0;
    spwn9_dir[1] = 0;
    spwn9_dir[2] = 0;

	m_spwn9 = g_Game.CreateObject("Chemlight_Red", spwn9_pos, false);
	m_spwn9.SetOrientation(spwn9_dir);
	m_spwn9.GetCompEM().SwitchOn(); 
	m_spwn9.GetCompEM().SetEnergy(15400);
	m_spwn9.SetTakeable(false);
	m_spwn9.SetPosition(spwn9_pos);
	
	
	//Yellow (random) shed
	Building m_spwn10;
    vector spwn10_pos;
    vector spwn10_dir;
   
    spwn10_pos[0] = 4138.6;
    spwn10_pos[1] = 352.4;
    spwn10_pos[2] = 14657.9;
 
    spwn10_dir[0] = 0;
    spwn10_dir[1] = 0;
    spwn10_dir[2] = 0;

	m_spwn10 = g_Game.CreateObject("Land_Shed_W6", spwn10_pos, false);
	m_spwn10.SetOrientation(spwn10_dir);
	m_spwn10.OpenDoor(1);
	m_spwn10.OpenDoor(0);
	
	//4140.95, 4136.12
	//14662, 14653.9
	
	
	//Yellow (random) chemlight in shed
	ItemBase m_spwn11;
    vector spwn11_pos;
    vector spwn11_dir;
   
    spwn11_pos[0] = 4139.38;
    spwn11_pos[1] = 354.467;
    spwn11_pos[2] = 14656.7;
 
    spwn11_dir[0] = 0;
    spwn11_dir[1] = 0;
    spwn11_dir[2] = 0;

	m_spwn11 = g_Game.CreateObject("Chemlight_Yellow", spwn11_pos, false);
	m_spwn11.SetOrientation(spwn11_dir);
	m_spwn11.GetCompEM().SwitchOn();
	m_spwn11.GetCompEM().SetEnergy(15400);
	m_spwn11.SetTakeable(false);
	m_spwn11.SetPosition(spwn11_pos);
	
	

	
	//Castle shit
	
	////////////
	Building m_wall1;
    vector wall1_pos;
    vector wall1_dir;
   
    wall1_pos[0] = 4136.9;
    wall1_pos[1] = 353.29;
    wall1_pos[2] = 14634.4;
 
    wall1_dir[0] = 0;
    wall1_dir[1] = 0;
    wall1_dir[2] = 0;

	m_wall1 = g_Game.CreateObject("Land_Castle_Wall1_20", wall1_pos, false);
	m_wall1.SetOrientation(wall1_dir);
	

	
	Building m_wall2;
    vector wall2_pos;
    vector wall2_dir;
  
    wall2_pos[0] = 4148.17;
    wall2_pos[1] = 353.29;
    wall2_pos[2] = 14645.8;
 
    wall2_dir[0] = -90;
    wall2_dir[1] = 0;
    wall2_dir[2] = 0;

	m_wall2 = g_Game.CreateObject("Land_Castle_wall1_20", wall2_pos, false);
	m_wall2.SetOrientation(wall2_dir);
	

	
	Building m_wall3;
    vector wall3_pos;
    vector wall3_dir;
   
    wall3_pos[0] = 4148.31;
    wall3_pos[1] = 353.29;
    wall3_pos[2] = 14665.9;
 
    wall3_dir[0] = -90;
    wall3_dir[1] = 0;
    wall3_dir[2] = 0;

	m_wall3 = g_Game.CreateObject("Land_Castle_wall1_20", wall3_pos, false);
	m_wall3.SetOrientation(wall3_dir);
	
	
	Building m_wall4;
    vector wall4_pos;
    vector wall4_dir;
  
    wall4_pos[0] = 4137.08;
    wall4_pos[1] = 353.29;
    wall4_pos[2] = 14676.7;
 
    wall4_dir[0] = -180;
    wall4_dir[1] = 0;
    wall4_dir[2] = 0;

	m_wall4 = g_Game.CreateObject("Land_Castle_wall1_20", wall4_pos, false);
	m_wall4.SetOrientation(wall4_dir);
	
	Building m_wall5;
    vector wall5_pos;
    vector wall5_dir;
   
    wall5_pos[0] = 4118.6;
    wall5_pos[1] = 353.29;
    wall5_pos[2] = 14676.3;
 
    wall5_dir[0] = 180;
    wall5_dir[1] = 0;
    wall5_dir[2] = 0;

	m_wall5 = g_Game.CreateObject("Land_Castle_wall1_20", wall5_pos, false);
	m_wall5.SetOrientation(wall5_dir);
	
	
	
	Building m_wall6;
    vector wall6_pos;
    vector wall6_dir;
   //4110.91,354.432,14665.7
    wall6_pos[0] = 4110.91;
    wall6_pos[1] = 353.29;
    wall6_pos[2] = 14665.7;
 
    wall6_dir[0] = 90;
    wall6_dir[1] = 0;
    wall6_dir[2] = 0;

	m_wall6 = g_Game.CreateObject("Land_Castle_wall1_20", wall6_pos, false);
	m_wall6.SetOrientation(wall6_dir);
	
	
	
	Building m_wall7;
    vector wall7_pos;
    vector wall7_dir;
   //4111.16,354.746,14645.9
    wall7_pos[0] = 4111.16;
    wall7_pos[1] = 353.29;
    wall7_pos[2] = 14645.9;
 
    wall7_dir[0] = 90;
    wall7_dir[1] = 0;
    wall7_dir[2] = 0;

	m_wall7 = g_Game.CreateObject("Land_Castle_wall1_20", wall7_pos, false);
	m_wall7.SetOrientation(wall7_dir);
	
	
	
	
	Building m_wall8;
    vector wall8_pos;
    vector wall8_dir;
   //4117.46,354.674,14634.3
    wall8_pos[0] = 4117.46;
    wall8_pos[1] = 353.29;
    wall8_pos[2] = 14634.3;
 
    wall8_dir[0] = 0;
    wall8_dir[1] = 0;
    wall8_dir[2] = 0;

	m_wall8 = g_Game.CreateObject("Land_Castle_wall1_20", wall8_pos, false);
	m_wall8.SetOrientation(wall8_dir);
	

}

