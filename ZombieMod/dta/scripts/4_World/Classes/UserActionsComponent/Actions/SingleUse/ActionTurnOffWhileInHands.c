class ActionTurnOffWhileInHands: ActionSingleUseBase
{
	void ActionTurnOffWhileInHands()
	{
		m_MessageSuccess = "I've flipped the switch off.";
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override int GetType()
	{
		return AT_TURN_OFF_WHILE_IN_HANDS;
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "#switch_off";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( item.HasEnergyManager()  &&  item.GetCompEM().CanSwitchOff() )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	override void OnCompleteServer( ActionData action_data )
	{
		action_data.m_MainItem.GetCompEM().SwitchOff();
	}
};