typedef Param3<int, int, string> TSelectableActionInfo;

class TSelectableActionInfoArray extends array<ref TSelectableActionInfo>
{
	bool IsSameAs(TSelectableActionInfoArray other)
	{
		if( this.Count() != other.Count() )
		{
			return false;
		}
		
		for( int i = 0; i < Count(); ++i )
		{
			TSelectableActionInfo ai1 = this.Get(i);
			TSelectableActionInfo ai2 = other.Get(i);
			
			if( ai1.param2 != ai2.param2 )
			{
				return false;
			}
			
			if( ai1.param3 != ai2.param3 )
			{
				return false;
			}
		}
		return true;
	}
};

class ActionManagerBase
{
	ref array<ref ActionBase>		m_Actions;
	ref map<int, ActionBase>		m_ActionsMap;		
	ref TIntArray					m_DefaultSingleUseActions;
	ref TIntArray					m_DefaultContinuousActions;
	ref TIntArray					m_DefaultInteractActions;
	ref ActionConstructor			m_ActionConstructor;
	PlayerBase						m_Player;
	ref HumanCommandActionCallback	m_Command;
	protected ActionBase			m_PrimaryAction;
	protected ActionTarget			m_PrimaryActionTarget;
	protected ItemBase				m_PrimaryActionItem;
	protected ActionBase			m_SecondaryAction;
	protected ActionTarget			m_SecondaryActionTarget;
	protected ItemBase				m_SecondaryActionItem;
	bool							m_PrimaryActionEnabled;
	bool							m_SecondaryActionEnabled;
	bool							m_TertiaryActionEnabled;
	ref TSelectableActionInfoArray	m_SelectableActions;
	int                             m_SelectedActionIndex;
	bool                            m_SelectableActionsHasChanged;
		
//Pending actions waiting for acknowledgment
	protected int 					m_PendingActionAcknowledgmentID;
	
	protected ref ActionData		m_CurrentActionData;
	
	void ActionManagerBase(PlayerBase player)
	{
		m_Player = player;
		if ( m_Player )
		{
			m_Actions = new array<ref ActionBase>;
			m_DefaultSingleUseActions = new TIntArray;
			m_DefaultContinuousActions = new TIntArray;
			m_DefaultInteractActions = new TIntArray;
			m_ActionsMap = new map<int, ActionBase>;
			m_ActionConstructor = new ActionConstructor;	

			m_ActionConstructor.ConstructActions(m_Actions,m_DefaultSingleUseActions,m_DefaultContinuousActions,m_DefaultInteractActions);
			for (int i = 0; i < m_Actions.Count(); i++)
			{	
				m_Actions.Get(i).CreateConditionComponents();
				m_ActionsMap.Set(m_Actions.Get(i).GetType(), m_Actions.Get(i));
			}
			
			m_SelectableActions = new TSelectableActionInfoArray;			
			m_SelectedActionIndex = 0;
			m_SelectableActionsHasChanged = false;
			
			m_PendingActionAcknowledgmentID = -1;
			
			m_CurrentActionData = NULL;
		}
	}
	
	ActionBase GetRunningAction()
	{
		if( m_CurrentActionData )
			return m_CurrentActionData.m_Action;
		return NULL;
	}
	
	void Update(int pCurrentCommandID)
	{
		if(m_CurrentActionData)
		{
			if(m_CurrentActionData.m_State != UA_AM_PENDING && m_CurrentActionData.m_State != UA_AM_REJECTED && m_CurrentActionData.m_State != UA_AM_ACCEPTED)
			{
				m_CurrentActionData.m_Action.OnUpdate(m_CurrentActionData);
			}
		}
	}
	
	void OnSyncJuncture(int pJunctureID, ParamsReadContext pCtx)
	{
	}
		
	ActionTarget FindActionTarget()
	{
	}
	
	void StartDeliveredAction()
	{
	}
		
	TIntArray GetDefaultSingleUseActions()
	{
		return m_DefaultSingleUseActions;
	}
	
	TIntArray GetDefaultContinuousActions()
	{
		return m_DefaultContinuousActions;
	}
	
	TIntArray GetDefaultInteractActions()
	{
		return m_DefaultInteractActions;
	}
	
	ActionBase GetAction(int type)
	{		
		return m_ActionsMap.Get(type);
	}
	
	ActionBase GetContinuousAction()
	{
		if ( m_PrimaryAction )
		{
			return m_PrimaryAction;
		}
		return NULL;
	}
	
	ActionBase GetSingleUseAction()
	{
		if ( m_SecondaryAction )
		{ 
			return m_SecondaryAction;
		}
		return NULL;
	}
			
	TSelectableActionInfoArray GetSelectableActions()
	{
		return m_SelectableActions;
	}

	int GetSelectedActionIndex()
	{
		return m_SelectedActionIndex;
	}
	
	void SelectNextAction()
	{
		if( m_SelectableActions.Count() == 0 )
		{
			return;
		}
		
		m_SelectedActionIndex++;
		if( m_SelectedActionIndex >= m_SelectableActions.Count() )
		{
			m_SelectedActionIndex = 0;
		}
	}
	
	void SelectPrevAction()
	{
		if( m_SelectableActions.Count() == 0 )
		{
			return;
		}
		
		m_SelectedActionIndex--;
		if( m_SelectedActionIndex < 0 ) 
		{
			m_SelectedActionIndex = m_SelectableActions.Count() - 1;
		}
	}
	
	bool IsSelectableActionsChanged()
	{
		return m_SelectableActionsHasChanged;
	}
	//------------------------------------------------------
	bool ActionPossibilityCheck(int pCurrentCommandID)
	{
		if ( m_Player.IsSprinting() || m_Player.IsUnconscious() || m_Player.GetCommandModifier_Action() || m_Player.GetCommand_Action() )
			return false;
		
		if (pCurrentCommandID == DayZPlayerConstants.COMMANDID_ACTION || pCurrentCommandID == DayZPlayerConstants.COMMANDID_MOVE || pCurrentCommandID == DayZPlayerConstants.COMMANDID_SWIM || pCurrentCommandID == DayZPlayerConstants.COMMANDID_LADDER || pCurrentCommandID == DayZPlayerConstants.COMMANDID_VEHICLE)
			return true;
		
		return false;
	}	
	
	//------------------------------------------------------	
	protected void SetContinuousAction( ActionBase action, ActionTarget target, ItemBase item )
	{
		m_PrimaryAction = action;
		m_PrimaryActionTarget = target;
		m_PrimaryActionItem = item;
	}
	
	protected void SetSingleUseAction( ActionBase action, ActionTarget target, ItemBase item )
	{
		m_SecondaryAction = action;
		m_SecondaryActionTarget = target;
		m_SecondaryActionItem = item;
	}
	
	protected void RemoveContinuousAction()
	{
		m_PrimaryAction = NULL;
		m_PrimaryActionTarget = NULL;
		m_PrimaryActionItem = NULL;
	}
	
	protected void RemoveSingleUseAction()
	{
		m_SecondaryAction = NULL;
		m_SecondaryActionTarget = NULL;
		m_SecondaryActionItem = NULL;
	}
		
	protected void RemoveActions()
	{
		RemoveContinuousAction();
		RemoveSingleUseAction();
	}
	
	void DisableContinuousAction()
	{
		m_PrimaryActionEnabled = false;
	}
	
	void EnableContinuousAction()
	{
		m_PrimaryActionEnabled = true;		
	}
	
	void DisableSingleUseAction()
	{
		m_SecondaryActionEnabled = false;
	}
	
	void EnableSingleUseAction()
	{
		m_SecondaryActionEnabled = true;		
	}
	
	void DisableInteractAction()
	{
		m_TertiaryActionEnabled = false;
	}
	
	void EnableInteractAction()
	{
		m_TertiaryActionEnabled = true;		
	}
	
	void EnableActions()
	{
		//Print("ActionManager - Enable actions");
		EnableContinuousAction();
		EnableSingleUseAction();
		EnableInteractAction();
	}
	
	void DisableActions()
	{
		//Print("ActionManager - Disable actions");
		DisableContinuousAction();
		DisableSingleUseAction();
		DisableInteractAction();
	}
	//---------------------------------------------------------------------
		
	int GetActionState(ActionBase action)
	{
		if( m_CurrentActionData )
		{
			return m_CurrentActionData.m_State;
		}
		return UA_NONE; // TODO check if it is correct constant
	}
	
	//---------------------------------
	// EVENTS
	//---------------------------------
	void OnContinuousStart()
	{
	}
	
	void OnContinuousCancel()
	{	
	}
		
	void OnSingleUse()
	{
	}
	
	void OnInteractAction() //Interact
	{
	}

	void OnInstantAction(int user_action_id, Param data)
	{
	}
	
	void OnActionEnd( )
	{
		m_CurrentActionData = NULL;
		m_Player.ResetActionEndInput();
	}
	
	void OnWeaponFsmEnd()
	{
		FirearmActionBase weapon_action = FirearmActionBase.Cast(GetRunningAction());
		if(weapon_action)
		{
			weapon_action.OnWeaponFsmEnd(m_CurrentActionData);
		}
	}

	bool OnInputUserDataProcess(int userDataType, ParamsReadContext ctx)
	{
		return false;
	}
	
	float GetActionComponentProgress()
	{
		if(m_CurrentActionData)
			return m_CurrentActionData.m_Action.GetProgress(m_CurrentActionData);
		return 0.0;
	}
	
	int GetActionState()
	{
		if(m_CurrentActionData)
			return m_CurrentActionData.m_Action.GetState(m_CurrentActionData);
		return UA_NONE;
	}
};