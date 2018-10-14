modded class PlayerBase extends ManBase
{
	bool IsInHub = true;
}

modded class BleedingSourcesManager
{
	override void ProcessHit(float damage, string component, string ammo, vector modelPos)
	{
		string ammo_type; 
		GetGame().ConfigGetText( "CfgAmmo " + ammo + " DamageApplied " + "type", ammo_type );
	
		if(ammo_type == "Melee")
		{
			if ( m_Player.IsInHub )
			{
				m_Player.SetHealth("","Health", 100);
				m_Player.SetHealth("","Shock", 100);
			}
		}
	}
}


