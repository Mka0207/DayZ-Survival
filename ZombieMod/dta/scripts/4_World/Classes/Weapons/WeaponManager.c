class WeaponManager
{
	protected PlayerBase 				m_player;
	
	protected int						m_LastAcknowledgmentID;
	
	protected int 						m_PendingWeaponActionAcknowledgmentID;
	protected Magazine 					m_PendingTargetMagazine;
	protected ref InventoryLocation		m_TargetInventoryLocation;
	protected int 						m_PendingWeaponAction; 
	protected ref InventoryLocation		m_PendingInventoryLocation;
	
	protected bool						m_canEnd;
	protected bool						m_justStart;
	protected bool						m_InProgress;
	protected bool						m_IsEventSended;
	protected bool						m_WantContinue;
	protected bool						m_InIronSight;
	protected bool						m_InOptic;
	protected Weapon_Base				m_WeaponInHand;
	protected FirearmActionBase			m_ControlAction;
	
	
	void WeaponManager(PlayerBase player)
	{
		m_player = player;
		m_PendingWeaponActionAcknowledgmentID = -1;
		m_PendingTargetMagazine = NULL;
		m_PendingInventoryLocation = NULL;
		m_WeaponInHand = NULL;
		m_ControlAction = NULL;
		m_PendingWeaponAction = -1;
		m_LastAcknowledgmentID = 1;
		m_InProgress = false;
		m_WantContinue = true;
		m_IsEventSended = false;
		m_canEnd = false;
	}
//----------------------------------------------------------------------------	
// Weapon Action conditions
//----------------------------------------------------------------------------
	bool CanAttachMagazine(Weapon_Base wpn, Magazine mag)
	{	
		if ( !wpn || !mag )
			return false;
		
		if ( m_player.GetHumanInventory().GetEntityInHands() != wpn )
			return false;
		
		InventoryLocation invLoc;
		invLoc = new InventoryLocation;
		
		mag.GetInventory().GetCurrentInventoryLocation(invLoc);
		Weapon_Base wnp2;
		//magazine is already in weapon
		if( Class.CastTo(wnp2,  invLoc.GetParent()) )
			return false;
			
		int muzzleIndex = wpn.GetCurrentMuzzle();
		
		if(wpn.CanAttachMagazine(muzzleIndex, mag))
			return true;

		return false;
		
	}
//---------------------------------------------------------------------------	
	
	bool CanSwapMagazine(Weapon_Base wpn, Magazine mag)
	{
		if ( !wpn || !mag )
			return false;
		
		if ( m_player.GetHumanInventory().GetEntityInHands() != wpn )
			return false;

		InventoryLocation invLoc;
		invLoc = new InventoryLocation;
		
		mag.GetInventory().GetCurrentInventoryLocation(invLoc);
		Weapon_Base wnp2;
		//second magazine is already in weapon
		if( Class.CastTo(wnp2,  invLoc.GetParent()) )
			return false;		
		
		int muzzleIndex = wpn.GetCurrentMuzzle();	
					
		Magazine mag2;
		if( !Class.CastTo(mag2, wpn.GetMagazine(muzzleIndex)) || !GameInventory.CanSwapEntities( mag, mag2 ) )
			return false;
		
		return true;
	}
//----------------------------------------------------------------------------			
	bool CanDetachMagazine(Weapon_Base wpn, Magazine mag)
	{
		if ( !wpn || !mag )
			return false;
		
		if ( m_player.GetHumanInventory().GetEntityInHands() != wpn )
			return false;
		
		if ( mag.GetParent() != wpn );
			return false;
		
		return true;
	}
//---------------------------------------------------------------------------
	bool CanLoadBullet(Weapon_Base wpn, Magazine mag)
	{
		if ( !wpn || !mag )
			return false;
		
		if( mag.IsDamageDestroyed())
			return false;
		
		if ( m_player.GetHumanInventory().GetEntityInHands() != wpn )
			return false;
		
		int muzzleIndex = wpn.GetCurrentMuzzle();
		
		if( !wpn.CanChamberBullet( muzzleIndex, mag ) )
			return false;
		
		return true;
	}
//---------------------------------------------------------------------------	
	bool CanUnjam(Weapon_Base wpn)
	{
		if( !wpn )
			return false;
		 
		if( m_player.GetHumanInventory().GetEntityInHands() != wpn)
			return false;
		
		if( wpn.IsChamberJammed(wpn.GetCurrentMuzzle()) )
			return false;
		 
		return true;
	}
	
	bool CanEjectBullet(Weapon_Base wpn)
	{
		if( !wpn )
			return false;
		 
		if( m_player.GetHumanInventory().GetEntityInHands() != wpn)
			return false;
		
		if( wpn.IsChamberJammed(wpn.GetCurrentMuzzle()) )
			return false;
		 
		return true;
	}
//----------------------------------------------------------------------------
	bool InventoryReservation( Magazine mag, InventoryLocation invLoc)
	{
		
		Weapon_Base weapon;
		InventoryLocation ilWeapon = new InventoryLocation;
		if (Weapon_Base.CastTo(weapon, m_player.GetItemInHands()) )
		{
			weapon.GetInventory().GetCurrentInventoryLocation(ilWeapon); 
			if(!m_player.GetInventory().AddInventoryReservation(weapon,ilWeapon,GameInventory.c_InventoryReservationTimeoutMS) )
			{
				return false;
			}
		}
		
		if( invLoc )
		{
			if ( !m_player.GetInventory().AddInventoryReservation(invLoc.GetItem(),invLoc,GameInventory.c_InventoryReservationTimeoutMS) )
			{
				m_player.GetInventory().ClearInventoryReservation(weapon, ilWeapon);
				return false;
			}
		}
		
		if( mag )
		{
			m_TargetInventoryLocation = new InventoryLocation;
			mag.GetInventory().GetCurrentInventoryLocation(m_TargetInventoryLocation);
			
			if ( !m_player.GetInventory().AddInventoryReservation(mag, m_TargetInventoryLocation, GameInventory.c_InventoryReservationTimeoutMS) )
			//if ( !m_player.GetInventory().AddInventoryReservation( mag, m_TargetInventoryLocation, GameInventory.c_InventoryReservationTimeoutMS) )
			{
				m_player.GetInventory().ClearInventoryReservation(weapon, ilWeapon);
				if (invLoc)
				{
					m_player.GetInventory().ClearInventoryReservation(invLoc.GetItem(), invLoc);
				}
				return false;
			}
		}
		m_PendingTargetMagazine = mag;
		m_PendingInventoryLocation = invLoc;
		
		return true;
	}	
	
//----------------------------------------------------------------------------	
// Weapon Actions	
//----------------------------------------------------------------------------
	void AttachMagazine( Magazine mag , FirearmActionBase control_action = NULL )
	{
		StartAction(AT_WPN_ATTACH_MAGAZINE, mag, NULL, control_action);
	}
	
	void DetachMagazine( InventoryLocation invLoc)
	{
		StartAction(AT_WPN_DETACH_MAGAZINE, NULL, invLoc, NULL);
	}
	
	void SwapMagazine( Magazine mag, FirearmActionBase control_action = NULL )
	{
		StartAction(AT_WPN_SWAP_MAGAZINE, mag, NULL, control_action);
	}
	
	void LoadBullet( Magazine mag, FirearmActionBase control_action = NULL )
	{
		StartAction(AT_WPN_LOAD_BULLET, mag, NULL, control_action);
	}
	
	void LoadMultiBullet( Magazine mag, FirearmActionBase control_action = NULL )
	{
		StartAction(AT_WPN_LOAD_MULTI_BULLETS_START, mag, NULL, control_action);
	}
	
	void LoadMultiBulletStop( )
	{
		if(m_InProgress) m_WantContinue = false;

	}
	
	void Unjam( FirearmActionBase control_action = NULL)
	{
		StartAction(AT_WPN_UNJAM, NULL, NULL, control_action);
	}

	void EjectBullet()
	{
		StartAction(AT_WPN_EJECT_BULLET, NULL, NULL, NULL);
	}
//-------------------------------------------------------------------------------------	
// Synchronize - initialize from client side
//-------------------------------------------------------------------------------------

	//Client
	private void Synchronize( )
	{
		if( GetGame().IsClient() )
		{
			m_PendingWeaponActionAcknowledgmentID = m_LastAcknowledgmentID++;
			ScriptInputUserData ctx = new ScriptInputUserData;
			
			ctx.Write(INPUT_UDT_WEAPON_ACTION);
			ctx.Write(m_PendingWeaponAction);
			ctx.Write(m_PendingWeaponActionAcknowledgmentID);
			
			
			switch (m_PendingWeaponAction)
			{
				case AT_WPN_ATTACH_MAGAZINE:
				{	
					ctx.Write(m_PendingTargetMagazine);
					break;
				}
				case AT_WPN_SWAP_MAGAZINE:
				{
					ctx.Write(m_PendingTargetMagazine);
					break;
				}
				case AT_WPN_DETACH_MAGAZINE:
				{
					m_PendingInventoryLocation.WriteToContext(ctx);
					break;
				}
				case AT_WPN_LOAD_BULLET:
				{
					ctx.Write(m_PendingTargetMagazine);
					break;
				}
				case AT_WPN_LOAD_MULTI_BULLETS_START:
				{
					ctx.Write(m_PendingTargetMagazine);
					break;
				}
				case AT_WPN_UNJAM:
				{
					break;
				}
				case AT_WPN_EJECT_BULLET:
				{
					break;
				}
				default: 
				break;
			}
			ctx.Send();
			//if( !m_player.GetDayZPlayerInventory().HasLockedHands() )
			//	m_player.GetDayZPlayerInventory().LockHands();
		}
	}
	

	
	void OnSyncJuncture(int pJunctureID, ParamsReadContext pCtx)
	{
		int AcknowledgmentID;
		pCtx.Read(AcknowledgmentID);
		if ( AcknowledgmentID == m_PendingWeaponActionAcknowledgmentID)
		{
			if (pJunctureID == DayZPlayerSyncJunctures.SJ_WEAPON_ACTION_ACK_ACCEPT)
			{
				StartPendingAction();
			}
			else if (pJunctureID == DayZPlayerSyncJunctures.SJ_WEAPON_ACTION_ACK_REJECT)
			{
				if(m_PendingWeaponAction >= 0 )
				{
					if(!(GetGame().IsServer() && GetGame().IsMultiplayer()))
					{
						InventoryLocation ilWeapon = new InventoryLocation;
						ItemBase weapon = m_player.GetItemInHands();
						weapon.GetInventory().GetCurrentInventoryLocation(ilWeapon);
						m_player.GetInventory().ClearInventoryReservation(m_player.GetItemInHands(),ilWeapon);
						
						if( m_PendingTargetMagazine )
						{
							m_PendingTargetMagazine.GetInventory().ClearInventoryReservation(m_PendingTargetMagazine, m_TargetInventoryLocation );
						}
						
						if( m_PendingInventoryLocation )
						{
							m_player.GetInventory().ClearInventoryReservation( NULL, m_PendingInventoryLocation );
						}
					}
					m_PendingWeaponActionAcknowledgmentID = -1;
					m_PendingTargetMagazine = NULL;
					m_PendingWeaponAction = -1;
					m_PendingInventoryLocation = NULL;
					m_InProgress = false;
				}
			}
		}
	}
	

		//Server
	bool OnInputUserDataProcess(int userDataType, ParamsReadContext ctx)
	{
		Weapon_Base wpn;
		InventoryLocation il;
		int slotID;
		bool accepted = false;
		if( userDataType == INPUT_UDT_WEAPON_ACTION)
		{
			if (!ctx.Read(m_PendingWeaponAction))
				return false;
			
			if (!ctx.Read(m_PendingWeaponActionAcknowledgmentID))
				return false;
			
			if(m_PendingTargetMagazine)
			{
				GetGame().ClearJuncture(m_player, m_PendingTargetMagazine);
				m_PendingTargetMagazine = NULL;
			}
			m_InProgress = true;
			m_IsEventSended = false;
			Magazine mag = NULL;
			switch (m_PendingWeaponAction)
			{
				case AT_WPN_ATTACH_MAGAZINE:
				{
					ctx.Read(mag);
					
					
					if ( !Weapon_Base.CastTo(wpn, m_player.GetItemInHands()) )
					{
						accepted = false;
					}
					else
					{
						slotID = wpn.GetSlotFromMuzzleIndex( wpn.GetCurrentMuzzle() );
						il = new InventoryLocation;
						il.SetAttachment(wpn,mag,slotID);
						if( GetGame().AddInventoryJuncture(m_player,mag,il, false, 10000) )
							accepted = true;
					}
					m_PendingTargetMagazine = mag;
					
					//AttachMagazine(mag);
					break;
				}
				case AT_WPN_SWAP_MAGAZINE:
				{
					ctx.Read(mag);
					if( GetGame().AddActionJuncture(m_player,mag,10000) )
						accepted = true;
					m_PendingTargetMagazine = mag;
					//SwapMagazine(mag);
					break;
				}
				case AT_WPN_DETACH_MAGAZINE:
				{
					il = new InventoryLocation;
					il.ReadFromContext(ctx);
					if( GetGame().AddInventoryJuncture(m_player, il.GetItem(), il, true, 10000))
						accepted = true;
					m_PendingInventoryLocation = il;
					m_PendingTargetMagazine = Magazine.Cast(il.GetItem());
					//DetachMagazine(il);
					break;
				}
				case AT_WPN_LOAD_BULLET:
				{
					ctx.Read(mag);
					if( GetGame().AddActionJuncture(m_player,mag,10000) )
						accepted = true;
					m_PendingTargetMagazine = mag;
					//LoadBullet(mag);
					break;
				}
				case AT_WPN_LOAD_MULTI_BULLETS_START:
				{
					ctx.Read(mag);
					if( GetGame().AddActionJuncture(m_player,mag,10000) )
						accepted = true;
					m_PendingTargetMagazine = mag;
					break;
				}
				case AT_WPN_UNJAM:
				{
					accepted = true;
					//Unjam();
					break;
				}
				case AT_WPN_EJECT_BULLET:
				{
					accepted = true;
					break;
				}
				default:
					Error("unknown actionID=" + m_PendingWeaponAction);
					return false;
			}
			DayZPlayerSyncJunctures.SendWeaponActionAcknowledgment(m_player, m_PendingWeaponActionAcknowledgmentID, accepted);
		}
		
		return accepted;
	}
	
	bool StartAction(int action, Magazine mag, InventoryLocation il, ActionBase control_action = NULL)
	{
		//if it is controled by action inventory reservation and synchronization provide action itself
		if(control_action)
		{
			m_ControlAction = control_action;
			m_PendingWeaponAction = action;
			m_InProgress = true;
			m_IsEventSended = false;
			m_PendingTargetMagazine = mag;
			m_PendingInventoryLocation = il;
			StartPendingAction();
			
			return true;
		}
		
		
		if (GetGame().IsMultiplayer() && GetGame().IsServer())
			return false;
		
		if ( !ScriptInputUserData.CanStoreInputUserData() )
			return false;
		if ( !InventoryReservation(mag, il) )
			return false;

		m_PendingWeaponAction = action;
		m_InProgress = true;
		m_IsEventSended = false;
		
		if ( !GetGame().IsMultiplayer() )
			StartPendingAction();
		else
			Synchronize();
		
		return true;
	}
	
	void StartPendingAction()
	{		
		m_WeaponInHand = Weapon_Base.Cast(m_player.GetItemInHands());
		
		switch (m_PendingWeaponAction)
		{
			case AT_WPN_ATTACH_MAGAZINE:
			{
				m_player.GetDayZPlayerInventory().PostWeaponEvent( new WeaponEventAttachMagazine(m_player, m_PendingTargetMagazine) );
				break;
			}
			case AT_WPN_SWAP_MAGAZINE:
			{
				m_player.GetDayZPlayerInventory().PostWeaponEvent( new WeaponEventSwapMagazine(m_player, m_PendingTargetMagazine) );
				break;
			}
			case AT_WPN_DETACH_MAGAZINE:
			{
				Magazine mag = Magazine.Cast(m_PendingInventoryLocation.GetItem());
				m_player.GetDayZPlayerInventory().PostWeaponEvent( new WeaponEventDetachMagazine(m_player, mag, m_PendingInventoryLocation) );
				break;
			}
			case AT_WPN_LOAD_BULLET:
			{
				m_WantContinue = false;
				m_player.GetDayZPlayerInventory().PostWeaponEvent( new WeaponEventLoad1Bullet(m_player, m_PendingTargetMagazine) );
				break;
			}
			case AT_WPN_LOAD_MULTI_BULLETS_START:
			{
				m_player.GetDayZPlayerInventory().PostWeaponEvent( new WeaponEventLoad1Bullet(m_player, m_PendingTargetMagazine) );
				break;
			}
			case AT_WPN_LOAD_MULTI_BULLETS_END:
			{
				m_player.GetDayZPlayerInventory().PostWeaponEvent( new WeaponEventContinuousLoadBulletEnd(m_player) );
				break;
			}
			case AT_WPN_UNJAM:
			{
				m_player.GetDayZPlayerInventory().PostWeaponEvent( new WeaponEventUnjam(m_player, NULL) );
				break;
			}
			case AT_WPN_EJECT_BULLET:
			{
				m_player.GetDayZPlayerInventory().PostWeaponEvent( new WeaponEventMechanism(m_player, NULL) );
				break;
			}
			default:
				m_InProgress = false;
				Error("unknown actionID=" + m_PendingWeaponAction);
		}	
		m_IsEventSended = true;
		m_canEnd = false;
	}
	
	bool IsRunning()
	{
		return m_InProgress;
	}
	
	void SetRunning( bool value)
	{
		m_InProgress = value;
	}
	
	void Update( float deltaT )
	{
		if( !m_InProgress || !m_IsEventSended )
			return;
		
		if(m_canEnd)
		{
			
			if(m_WeaponInHand.IsIdle())
			{
				OnWeaponActionEnd();
			}
			else if(m_justStart)
			{
				m_InIronSight = m_player.IsInIronsights();
				m_InOptic = m_player.IsInOptics();
		
				if(m_InIronSight || m_InOptic)
				{
					m_player.ExitSights();
				}
				
				m_justStart = false;
			}
			
		}
		else
		{
			m_canEnd = true;
			m_justStart = true;
		}
		
	}

	void OnWeaponActionEnd()
	{
		if ( !m_InProgress )
			return;
		
		if(m_ControlAction)
		{
			m_player.GetActionManager().OnWeaponFsmEnd();
		}
		else
		{
			if(GetGame().IsServer() && GetGame().IsMultiplayer())
			{
				if(m_PendingTargetMagazine)
				{
					GetGame().ClearJuncture(m_player,m_PendingTargetMagazine);
				}
			}
			else
			{
				InventoryLocation ilWeapon = new InventoryLocation;
				ItemBase weapon = m_player.GetItemInHands();
				weapon.GetInventory().GetCurrentInventoryLocation(ilWeapon);
				m_player.GetInventory().ClearInventoryReservation(weapon,ilWeapon);
						
				if( m_PendingTargetMagazine )
				{
					m_player.GetInventory().ClearInventoryReservation(m_PendingTargetMagazine, m_TargetInventoryLocation );
				}
						
				if( m_PendingInventoryLocation )
				{
					m_player.GetInventory().ClearInventoryReservation( m_PendingInventoryLocation.GetItem(), m_PendingInventoryLocation );
				}
			}
		}
		
		if(!m_justStart && m_player.IsRaised())
		{
			if(m_InIronSight)
				m_player.SetIronsights(m_InIronSight);
			if(m_InOptic)
			{
				ItemOptics optic = m_WeaponInHand.GetAttachedOptics();
				if(optic)
					m_player.SwitchOptics(optic,true);
			}
		}
		m_ControlAction = NULL;
		m_PendingWeaponAction = -1;
		m_PendingTargetMagazine = NULL;
		m_PendingInventoryLocation = NULL;
		m_TargetInventoryLocation = NULL;
		m_PendingWeaponActionAcknowledgmentID = -1;
		m_InProgress = false;
		m_WantContinue = true;
		
	}
	
	bool WantContinue()
	{
		return m_WantContinue;
	}

}
