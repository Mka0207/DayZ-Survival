class CAContinuousFertilizeGardenSlot : CAContinuousQuantity
{
	protected float m_SlotFertilizerNeed;
	protected float	m_TimeToComplete;

	void CAContinuousFertilizeGardenSlot( float quantity_used_per_second )
	{
		m_QuantityUsedPerSecond = quantity_used_per_second;
		m_TimeToComplete = 0;
	}
	
	override void Setup( ActionData action_data )
	{
		GardenBase target_GB;		
		if ( Class.CastTo(target_GB,  action_data.m_Target.GetObject() ) )
		{
			m_SpentQuantity = 0;
			
			if ( !m_SpentUnits )
			{
				m_SpentUnits = new Param1<float>(0);
			}
			else
			{	
				m_SpentUnits.param1 = 0;
			}
			
			if ( action_data.m_MainItem ) 
				m_ItemQuantity = action_data.m_MainItem.GetQuantity();
			
			if ( target_GB ) 
			{
				string selection = target_GB.GetActionComponentName(action_data.m_Target.GetComponentIndex());
				Slot slot = target_GB.GetSlotBySelection( selection );
				
				
				string item_type = action_data.m_MainItem.GetType();
				float consumed_quantity = GetGame().ConfigGetFloat( "cfgVehicles " + item_type + " Horticulture ConsumedQuantity" ) / 2;
				
				float max = slot.GetFertilizerQuantityMax();
				
				m_SlotFertilizerNeed = max - consumed_quantity;
				Print(m_SlotFertilizerNeed);
			}
			
			m_TimeToComplete = (Math.Min(m_SlotFertilizerNeed,m_ItemQuantity))/m_QuantityUsedPerSecond;
		}
	}
	
	
	override int Execute( ActionData action_data  )
	{		
		if ( !action_data.m_Player )
		{
			return UA_ERROR;
		}
		
		if ( m_ItemQuantity <= 0 )
		{
			return UA_FINISHED;
		}
		else
		{
			if ( m_SpentQuantity < m_ItemQuantity  &&  m_SpentQuantity < m_SlotFertilizerNeed )
			{
				m_SpentQuantity += m_QuantityUsedPerSecond * action_data.m_Player.GetDeltaT();
				float val = action_data.m_Player.GetSoftSkillManager().AddSpecialtyBonus( m_SpentQuantity, m_Action.GetSpecialtyWeight(), true );
				GardenBase garden_base;
				Class.CastTo(garden_base,  action_data.m_Target.GetObject() );
				string selection = garden_base.GetActionComponentName(action_data.m_Target.GetComponentIndex());
				
				if (GetGame().IsServer())
				{
					action_data.m_MainItem.AddQuantity( -m_SpentQuantity );
					m_Action.SendMessageToClient(action_data.m_Player, garden_base.Fertilize( action_data.m_Player, action_data.m_MainItem, val, selection ));
				}

				return UA_PROCESSING;
			}
			else
			{
				CalcAndSetQuantity( action_data );
				return UA_FINISHED;
			}
		}
	}
	
	override float GetProgress()
	{	
		//float progress = (m_SpentQuantity*m_QuantityUsedPerSecond)/m_TimeToComplete;
		return (m_SpentQuantity*m_QuantityUsedPerSecond)/m_TimeToComplete;
	}
};