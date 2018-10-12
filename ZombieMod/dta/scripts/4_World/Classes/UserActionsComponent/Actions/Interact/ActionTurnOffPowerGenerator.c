class ActionTurnOffPowerGenerator: ActionInteractBase
{	
	void ActionTurnOffPowerGenerator()
	{
		m_MessageSuccess = "I've turned off the generator.";
		m_MessageStart = "";
	}
	
	override int GetType()
	{
		return AT_TURN_OFF_POWER_GENERATOR;
	}

	override string GetText()
	{
		return "Switch off";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		ItemBase target_IB = ItemBase.Cast( targetObject );
		string selection = targetObject.GetActionComponentName(target.GetComponentIndex());
		
		if ( target_IB.HasEnergyManager()  &&  target_IB.GetCompEM().CanSwitchOff()  &&  selection == "switch" )
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
		Object targetObject = action_data.m_Target.GetObject();
		if ( targetObject )
		{
			ItemBase target_IB = ItemBase.Cast( targetObject );
			target_IB.GetCompEM().SwitchOff();
		}
	}
};