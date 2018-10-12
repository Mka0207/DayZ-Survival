class OptionsMenuSounds extends ScriptedWidgetEventHandler
{
	protected Widget					m_Root;
	
	protected Widget					m_SettingsRoot;
	protected Widget					m_DetailsRoot;
	protected TextWidget				m_DetailsLabel;
	protected RichTextWidget			m_DetailsText;
	
	protected ref NumericOptionsAccess	m_MasterOption;
	protected ref NumericOptionsAccess	m_EffectsOption;
	protected ref NumericOptionsAccess	m_VOIPOption;
	protected ref NumericOptionsAccess	m_MusicOption;
	
	protected ref OptionSelectorSlider	m_MasterSelector;
	protected ref OptionSelectorSlider	m_EffectsSelector;
	protected ref OptionSelectorSlider	m_VOIPSelector;
	protected ref OptionSelectorSlider	m_MusicSelector;
	
	protected GameOptions				m_Options;
	protected OptionsMenuNew			m_Menu;
	
	protected ref map<int, ref Param2<string, string>> m_TextMap;
	
	void OptionsMenuSounds( Widget parent, Widget details_root, GameOptions options, OptionsMenuNew menu )
	{
		#ifdef PLATFORM_CONSOLE
			m_Root				= GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/options/xbox/sound_tab.layout", parent );
		#else
		#ifdef PLATFORM_WINDOWS
			m_Root				= GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/options/pc/sound_tab.layout", parent );
		#endif
		#endif
		
		m_DetailsRoot			= details_root;
		m_DetailsLabel			= TextWidget.Cast( m_DetailsRoot.FindAnyWidget( "details_label" ) );
		m_DetailsText			= RichTextWidget.Cast( m_DetailsRoot.FindAnyWidget( "details_content" ) );
		
		m_Options				= options;
		m_Menu					= menu;
		
		m_MasterOption			= NumericOptionsAccess.Cast( m_Options.GetOptionByType( AT_OPTIONS_MASTER_VOLUME ) );
		m_EffectsOption			= NumericOptionsAccess.Cast( m_Options.GetOptionByType( AT_OPTIONS_EFFECTS_SLIDER ) );
		m_VOIPOption			= NumericOptionsAccess.Cast( m_Options.GetOptionByType( AT_OPTIONS_VON_SLIDER ) );
		m_MusicOption			= NumericOptionsAccess.Cast( m_Options.GetOptionByType( AT_OPTIONS_MUSIC_SLIDER ) );
		
		m_Root.FindAnyWidget( "master_setting_option" ).SetUserID( AT_OPTIONS_MASTER_VOLUME );
		m_Root.FindAnyWidget( "effects_setting_option" ).SetUserID( AT_OPTIONS_EFFECTS_SLIDER );
		m_Root.FindAnyWidget( "voip_setting_option" ).SetUserID( AT_OPTIONS_VON_SLIDER );
		m_Root.FindAnyWidget( "music_setting_option" ).SetUserID( AT_OPTIONS_MUSIC_SLIDER );
		
		FillTextMap();
		
		m_MasterSelector		= new OptionSelectorSlider( m_Root.FindAnyWidget( "master_setting_option" ), m_MasterOption.ReadValue(), this, false, m_MasterOption.GetMin(), m_MasterOption.GetMax() );
		m_EffectsSelector		= new OptionSelectorSlider( m_Root.FindAnyWidget( "effects_setting_option" ), m_EffectsOption.ReadValue(), this, false, m_EffectsOption.GetMin(), m_EffectsOption.GetMax() );
		m_VOIPSelector			= new OptionSelectorSlider( m_Root.FindAnyWidget( "voip_setting_option" ), m_VOIPOption.ReadValue(), this, false, m_VOIPOption.GetMin(), m_VOIPOption.GetMax() );
		m_MusicSelector			= new OptionSelectorSlider( m_Root.FindAnyWidget( "music_setting_option" ), m_MusicOption.ReadValue(), this, false, m_MusicOption.GetMin(), m_MusicOption.GetMax() );
		
		m_MasterSelector.m_OptionChanged.Insert( UpdateMaster );
		m_EffectsSelector.m_OptionChanged.Insert( UpdateEffects );
		m_VOIPSelector.m_OptionChanged.Insert( UpdateVOIP );
		m_MusicSelector.m_OptionChanged.Insert( UpdateMusic );
	}
	
	void Focus()
	{
		#ifdef PLATFORM_CONSOLE
			SetFocus( m_MasterSelector.GetParent() );
		#endif
	}
	
	override bool OnFocus( Widget w, int x, int y )
	{
		OptionsMenuNew menu = OptionsMenuNew.Cast( GetGame().GetUIManager().GetMenu() );
		if( menu )
			menu.OnFocus( w, x, y );
		if( w )
		{
			Param2<string, string> p = m_TextMap.Get( w.GetUserID() );
			if( p )
			{
				m_DetailsRoot.Show( true );
				m_DetailsLabel.SetText( p.param1 );
				m_DetailsText.SetText( p.param2 );
				int sx, sy;
				float lines = m_DetailsText.GetContentHeight();
				m_DetailsText.SetSize( 1, lines );
				
				m_DetailsText.Update();
				m_DetailsLabel.Update();
				m_DetailsRoot.Update();
				return true;
			}
		}
		m_DetailsRoot.Show( false );
		return ( w != null );
	}
	
	bool IsChanged()
	{
		return false;
	}
	
	void Apply()
	{
		
	}
	
	void Revert()
	{
		m_MasterSelector.SetValue( m_MasterOption.ReadValue() );
		m_EffectsSelector.SetValue( m_EffectsOption.ReadValue() );
		m_VOIPSelector.SetValue( m_VOIPOption.ReadValue() );
		m_MusicSelector.SetValue( m_MusicOption.ReadValue() );
	}
	
	void ReloadOptions()
	{
		m_Menu.ReloadOptions();
	}
	
	void SetOptions( GameOptions options )
	{
		m_Options = options;
	}
	
	void UpdateMaster( float value )
	{
		m_MasterOption.WriteValue( value );
		m_Menu.OnChanged();
	}
	
	void UpdateEffects( float value )
	{
		m_EffectsOption.WriteValue( value );
		m_Menu.OnChanged();
	}
	
	void UpdateVOIP( float value )
	{
		m_VOIPOption.WriteValue( value );
		m_Menu.OnChanged();
	}
	
	void UpdateMusic( float value )
	{
		m_MusicOption.WriteValue( value );
		m_Menu.OnChanged();
	}
	
	void FillTextMap()
	{
		m_TextMap = new map<int, ref Param2<string, string>>;
		m_TextMap.Insert( AT_OPTIONS_MASTER_VOLUME, new Param2<string, string>( "Master Volume", "#options_sound_master_volume_desc" ) );
		m_TextMap.Insert( AT_OPTIONS_EFFECTS_SLIDER, new Param2<string, string>( "Effects Volume", "#options_sound_effects_volume_desc" ) );
		m_TextMap.Insert( AT_OPTIONS_VON_SLIDER, new Param2<string, string>( "VoIP Volume", "#options_sound_VOIP_volume_desc" ) );
		m_TextMap.Insert( AT_OPTIONS_MUSIC_SLIDER, new Param2<string, string>( "Music Volume", "Sets the volume level for any music in the game." ) );
	}
}