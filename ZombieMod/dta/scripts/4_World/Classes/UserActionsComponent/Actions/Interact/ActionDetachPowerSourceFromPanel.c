
class ActionDetachPowerSourceFromPanel: ActionInteractBase
{
	void ActionDetachPowerSourceFromPanel()
	{
		//m_MessageStartFail = "m_MessageStartFail";
		//m_MessageStart = "m_MessageStart";
		m_MessageSuccess = "I've detached the power source from the panel.";
		//m_MessageFail = "m_MessageFail";
		//m_MessageCancel = "m_MessageCancel";
	}
	
	override int GetType()
	{
		return AT_DETACH_POWER_SOURCE_FROM_PANEL;
	}
		
	override string GetText()
	{
		return "Detach power source";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_object = target.GetObject();
		
		if ( player && target_object )
		{
			EntityAI target_entity = EntityAI.Cast( target.GetObject() );
			string selection = target_object.GetActionComponentName( target.GetComponentIndex() );
			
			
			if ( target_entity && target_entity.GetInventory() && target_entity.GetInventory().AttachmentCount() > 0 && selection == "power_source" )	//has any power source attachment attached
			{
				return true;
			}
		}
		
		return false;
	}
	
	override void OnCompleteClient( ActionData action_data )
	{
		Process(action_data);
	}
	
	override void OnCompleteServer( ActionData action_data )
	{
		Process(action_data);
	}

	void Process( ActionData action_data )
	{
		EntityAI target_entity = EntityAI.Cast( action_data.m_Target.GetObject() );
		
		EntityAI attachment;
		int attachments_count = target_entity.GetInventory().AttachmentCount();
		for ( int j = 0; j < attachments_count; j++ )				//find any attached power source
		{
			// @TODO: vezme prvni att?
			attachment = target_entity.GetInventory().GetAttachmentFromIndex( j );
			if ( attachment )
				break;
		}
		
		if ( attachment )
		{
			action_data.m_Player.PredictiveTakeEntityToHands(attachment );
		}
	}
}