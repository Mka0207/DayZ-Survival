class ActionDismantleOvenCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime( UATimeSpent.DEFAULT_DECONSTRUCT );
	}
}

class ActionDismantleOven: ActionContinuousBase
{	
	void ActionDismantleOven()
	{
		m_CallbackClass = ActionDismantleOvenCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		
		m_MessageStartFail = "I cannot dismantle an oven.";
		m_MessageSuccess = "I have dismantle an oven.";
		m_MessageFail = "I cannot dismantle an oven.";
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override void CreateConditionComponents()  
	{	
		
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
		m_ConditionItem = new CCINotPresent;
	}

	override int GetType()
	{
		return AT_DISMANTLE_OVEN;
	}
		
	override string GetText()
	{
		return "Dismantle oven";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		Object target_object = target.GetObject();
		
		if ( target_object && target_object.IsFireplace() )
		{
			FireplaceBase fireplace_target = FireplaceBase.Cast( target_object );
			
			if ( fireplace_target.IsBaseFireplace() && fireplace_target.CanDismantleOven() )
			{
				return true;
			}
		}

		return false;
	}
		
	override void OnCompleteServer( ActionData action_data )
	{	
		Object target_object = action_data.m_Target.GetObject();
		FireplaceBase fireplace_target = FireplaceBase.Cast( target_object );
		
		if ( fireplace_target.CanDismantleOven() )
		{
			ItemBase attached_item = ItemBase.Cast( fireplace_target.GetAttachmentByType( fireplace_target.ATTACHMENT_STONES ) );
			int slot_id = attached_item.GetInventory().GetSlotId(0);
			fireplace_target.GetInventory().SetSlotLock( slot_id, false );

			//set oven state
			fireplace_target.SetOvenState( false );
			
			//add specialty to soft skills
			action_data.m_Player.GetSoftSkillManager().AddSpecialty( m_SpecialtyWeight );
		}
		else
		{
			SendMessageToClient( action_data.m_Player, fireplace_target.MESSAGE_CANNOT_DISMANTLE_OVEN );
		}
	}
}