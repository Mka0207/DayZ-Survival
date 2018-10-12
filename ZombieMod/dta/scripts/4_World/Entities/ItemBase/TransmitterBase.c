//TRANSMITTER BASE
class TransmitterBase extends ItemTransmitter
{
	//Sounds
	const string SOUND_RADIO_START_NOISE 	= "radioStartNoise";
	
	override bool IsTransmitter()
	{
		return true;
	}
	
	//--- COMMON
	bool CanOperate()
	{
		return GetCompEM().IsSwitchedOn();	
	}

	//--- ACTIONS
	void SetNextFrequency( PlayerBase player = NULL )
	{
		SetNextChannel();
		
		if ( player )
		{
			DisplayRadioInfo( GetTunedFrequency().ToString(), player );
		}
	}
	
	//--- HUD
	protected Hud GetHud( PlayerBase player )
	{
		if ( !player ) 
		{
			return NULL;
		}
		
		return player.m_HUD;
	}
	
	void DisplayRadioInfo( string message, PlayerBase player )
	{
		Hud hud;
		if ( player )
		{
			hud = GetHud( player );
		}
		
		if ( hud ) 
		{	
			hud.SetWalkieTalkieText( message );
			hud.ShowWalkieTalkie( 3 );
		}
	}
	
	//--- POWER EVENTS
	override void OnSwitchOn()
	{
		//turn on broadcasting/receiving
		EnableBroadcast ( true );
		EnableReceive ( true );
		SwitchOn ( true );
		
		//play sound
		SoundRadioStartNoise();
	}

	override void OnSwitchOff()
	{
		//turn off broadcasting/receiving
		EnableBroadcast ( false );
		EnableReceive ( false );	
		SwitchOn ( false );	
	}

	override void OnWorkStop()
	{
		//turn off device
		GetCompEM().SwitchOff();
	}
	
	//--- SOUNDS
	//Radio start noise
	protected void SoundRadioStartNoise()
	{
		if ( GetGame() && ( !GetGame().IsMultiplayer() || GetGame().IsClient() ) )
		{
			PlaySound( SOUND_RADIO_START_NOISE, 50 );
		}
	}
}
