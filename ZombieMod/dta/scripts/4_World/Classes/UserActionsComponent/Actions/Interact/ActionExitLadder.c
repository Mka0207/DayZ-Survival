class ActionExitLadder: ActionInteractBase
{
	void ActionExitLadder()
	{
		m_MessageSuccess = "";
		//m_CommandUID = DayZPlayerConstants.;
		m_HUDCursorIcon = CursorIcons.LadderDown;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override int GetType()
	{
		return AT_EXIT_LADDER;
	}

	override string GetText()
	{
		return "Exit ladder";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
	    HumanCommandLadder cl = player.GetCommand_Ladder();
		if (cl && cl.CanExit())
		{
			return true;
		}
		
		//if ( action_data.m_Player.IsOnLadder() ) return true;
		return false;
	}

	//! 
	override void Start( ActionData action_data )
	{
	    HumanCommandLadder cl = action_data.m_Player.GetCommand_Ladder();
		if (cl)
		{
			cl.Exit();
		}
	}


	/*override void OnCompleteServer( ActionData action_data )
	{
	}*/
	override bool IsInstant()
	{
		return true;
	}
	
	override bool UseAcknowledgment()
	{
		return false;
	}
};