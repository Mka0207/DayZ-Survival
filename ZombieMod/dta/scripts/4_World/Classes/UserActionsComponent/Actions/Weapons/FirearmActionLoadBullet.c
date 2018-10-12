class FirearmActionLoadBullet : FirearmActionBase
{	
	//-----------------------------------------------------
	// 	Action events and methods
	//-----------------------------------------------------
	void FirearmActionLoadBullet() 
	{
	}	
	
	override int GetActionCategory()
	{
		return AC_SINGLE_USE;
	}
	
	override int GetType()  //returns action uid
	{
		return AT_LOAD_BULLET_TO_WEAPON;
	}

	override string GetText() //text game displays in HUD hint 
	{
		return "Load bullet";
	} 
	
	/*string GetTargetDescription()
	{
		return "default target description";
	}*/
	
	/*protected bool ActionConditionContinue( ActionData action_data ) //condition for action
	{
		return true;
	}*/
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item ) //condition for action
	{
		Weapon_Base wpn = Weapon_Base.Cast(item);
		Magazine mag = Magazine.Cast(target.GetObject());
		
		if (wpn && mag )
			if ( player.GetWeaponManager().CanLoadBullet(wpn,mag) )
				return true;

		return false;
	}
	
	override void Start( ActionData action_data )
	{
		super.Start( action_data );
		Magazine mag = Magazine.Cast(action_data.m_Target.GetObject());	

		action_data.m_Player.GetWeaponManager().LoadBullet(mag, this);
	}
	
	override bool CanBePerformedFromInventory()
	{
		return true;
	}
	
	override bool CanBePerformedFromQuickbar()
	{
		return true;
	}
	
	// action need first have permission from server before can start
	/*bool UseAcknowledgment()
	{
		return true;
	}*/

	
	/*override int GetState( ActionData action_data )
	{
		return UA_PROCESSING;
	}*/
	
	/*override float GetProgress( ActionData action_data )
	{
		return -1;
	}*/
};