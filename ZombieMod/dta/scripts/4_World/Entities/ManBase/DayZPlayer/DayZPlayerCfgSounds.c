class DayZPlayerTypeStepSoundLookupTableImpl extends DayZPlayerTypeStepSoundLookupTable
{
	void DayZPlayerTypeStepSoundLookupTableImpl(string pPlayerStepsCfgPath)
	{
		m_pSoundTableInstances = new map<int, ref StepSoundLookupTable>;
		m_pSoundTables = new map<int, StepSoundLookupTable>;
		
		string stepsCfgPath = pPlayerStepsCfgPath + " ";
		int stepsCount = GetGame().ConfigGetChildrenCount(stepsCfgPath);
		for(int i = 0; i < stepsCount; i++)
		{
			string stepName;
			GetGame().ConfigGetChildName(stepsCfgPath, i, stepName);
			string stepPath = stepsCfgPath + stepName + " ";
			int id = GetGame().ConfigGetInt(stepPath + "id");
			
			string tableName;
			GetGame().ConfigGetText(stepPath + "soundLookupTable", tableName);

			
			StepSoundLookupTable table = m_pSoundTableInstances.Get(tableName.Hash());
			if(table == NULL)
			{
				table = new StepSoundLookupTable();
				table.LoadTable(tableName);
				m_pSoundTableInstances.Insert(tableName.Hash(), table);
			}
			m_pSoundTables.Insert(id, table);
		}
	}

	override SoundObjectBuilder GetSoundBuilder(int eventId, int pMovement, int pSurfaceHash, AnimBootsType pBoots)
	{
		SoundLookupTable table = m_pSoundTables.Get(eventId);
		if(table == NULL)
			return NULL;
		
		SoundObjectBuilder soundBuilder = table.GetSoundBuilder(pSurfaceHash);
		if(soundBuilder == NULL)
			return NULL;
		
		if (pMovement == DayZPlayerConstants.MOVEMENTIDX_WALK)
		{
			soundBuilder.SetVariable("walk", 1);
			soundBuilder.SetVariable("run", 0);
			soundBuilder.SetVariable("sprint", 0);
		}
		else if (pMovement == DayZPlayerConstants.MOVEMENTIDX_RUN)
		{
			soundBuilder.SetVariable("walk", 0);
			soundBuilder.SetVariable("run", 1);
			soundBuilder.SetVariable("sprint", 0);
		}
		else if (pMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT)
		{
			soundBuilder.SetVariable("walk", 0);
			soundBuilder.SetVariable("run", 0);
			soundBuilder.SetVariable("sprint", 1);
		}
		else
		{
			soundBuilder.SetVariable("walk", 0);
			soundBuilder.SetVariable("run", 0);
			soundBuilder.SetVariable("sprint", 0);
		}
		
		if (pBoots == AnimBootsType.None)
		{
			soundBuilder.SetVariable("bare", 1);
			soundBuilder.SetVariable("sneakers", 0);
			soundBuilder.SetVariable("boots", 0);
		}
		else if (pBoots == AnimBootsType.Sneakers)
		{
			soundBuilder.SetVariable("bare", 0);
			soundBuilder.SetVariable("sneakers", 1);
			soundBuilder.SetVariable("boots", 0);
		}
		else if (pBoots == AnimBootsType.Boots)
		{
			soundBuilder.SetVariable("bare", 0);
			soundBuilder.SetVariable("sneakers", 0);
			soundBuilder.SetVariable("boots", 1);
		}
		
		return soundBuilder;
	}

	autoptr map<int, ref StepSoundLookupTable> m_pSoundTableInstances;//unique tables
	autoptr map<int, StepSoundLookupTable> m_pSoundTables;//pointers to tables above
}


class DayZPlayerTypeAttachmentSoundLookupTableImpl extends DayZPlayerTypeAttachmentSoundLookupTable
{
	void DayZPlayerTypeAttachmentSoundLookupTableImpl(string pPlayerAttachmentCfgPath)
	{
		m_pSoundTableInstances = new map<int, ref AttachmentSoundLookupTable>;
		m_pSoundTables = new map<int, AttachmentSoundLookupTable>();
		
		string attachCfgPath = pPlayerAttachmentCfgPath + " ";
		int attachCount = GetGame().ConfigGetChildrenCount(attachCfgPath);
		for(int i = 0; i < attachCount; i++)
		{
			string defName;
			GetGame().ConfigGetChildName(attachCfgPath, i, defName);
			string defPath = attachCfgPath + defName + " ";
			
			string slotName;
			GetGame().ConfigGetText(defPath + "slot", slotName);
			
			int id = GetGame().ConfigGetInt(defPath + "id");
			
			string tableName;
			GetGame().ConfigGetText(defPath + "soundLookupTable", tableName);
			
			AttachmentSoundLookupTable table = m_pSoundTableInstances.Get(tableName.Hash());
			if(table == NULL)
			{
				table = new AttachmentSoundLookupTable();
				table.LoadTable(tableName);
				m_pSoundTableInstances.Insert(tableName.Hash(), table);
			}

			m_pSoundTables.Insert((slotName + id).Hash(), table);
		}
	}
	
	override SoundObjectBuilder GetSoundBuilder(int eventId, string slotName, int attachmentHash)
	{
		SoundLookupTable table = m_pSoundTables.Get((slotName + eventId).Hash());
		if(table == NULL)
			return NULL;
		
		SoundObjectBuilder soundBuilder = table.GetSoundBuilder(attachmentHash);
		if(soundBuilder == NULL)
			return NULL;
		
		return soundBuilder;
	}
	
	autoptr map<int, ref AttachmentSoundLookupTable> m_pSoundTableInstances;
	private autoptr map<int, AttachmentSoundLookupTable> m_pSoundTables;
}


class DayZPlayerTypeSoundTableImpl extends DayZPlayerTypeAnimTable
{
	void DayZPlayerTypeSoundTableImpl()
	{
		m_animSoundEvents = new array<ref AnimSoundEvent>;
		
		string soundsCfgPath = "CfgVehicles SurvivorBase AnimEvents Sounds ";

		int soundCount = GetGame().ConfigGetChildrenCount(soundsCfgPath);
		for(int i = 0; i < soundCount; i++)
		{
			string soundName;
			GetGame().ConfigGetChildName(soundsCfgPath, i, soundName);			
			string soundPath = soundsCfgPath + soundName + " ";
			AnimSoundEvent soundEvent = new AnimSoundEvent(soundPath);
			m_animSoundEvents.Insert(soundEvent);
		}
	}
	
	AnimSoundEvent GetSoundEvent(int event_id)
	{
		for(int i = 0; i < m_animSoundEvents.Count(); i++)
		{
			AnimSoundEvent soundEvent = m_animSoundEvents.Get(i);
			if(soundEvent.m_iID == event_id)
			{
				return soundEvent;
			}
		}

		return NULL;
	}
	
	ref array<ref AnimSoundEvent> m_animSoundEvents;
}

class DayZPlayerSoundVoiceTableImpl extends DayZPlayerTypeAnimTable
{
	void DayZPlayerSoundVoiceTableImpl()
	{
		m_animSoundEvents = new array<ref AnimSoundEvent>;
		
		string soundsCfgPath = "CfgVehicles SurvivorBase AnimEvents SoundVoice ";

		int soundCount = GetGame().ConfigGetChildrenCount(soundsCfgPath);
		for(int i = 0; i < soundCount; i++)
		{
			string soundName;
			GetGame().ConfigGetChildName(soundsCfgPath, i, soundName);			
			string soundPath = soundsCfgPath + soundName + " ";
			AnimSoundEvent soundEvent = new AnimSoundEvent(soundPath);
			m_animSoundEvents.Insert(soundEvent);
		}
	}
	
	AnimSoundEvent GetSoundEvent(int event_id)
	{
		for(int i = 0; i < m_animSoundEvents.Count(); i++)
		{
			AnimSoundEvent soundEvent = m_animSoundEvents.Get(i);
			if(soundEvent.m_iID == event_id)
			{
				return soundEvent;
			}
		}

		return NULL;
	}
	
	ref array<ref AnimSoundEvent> m_animSoundEvents;
}


void DayZPlayerTypeRegisterSounds(DayZPlayerType pType)
{
	GetGame().ProfilerStart("DayZPlayerTypeRegisterSounds");
	//! register events
	pType.RegisterStepEvent("Step", 0.2);

	pType.RegisterSoundEvent("Sound", -1);
	pType.RegisterSoundEvent("SoundWeapon", 0.2);
	pType.RegisterSoundEvent("SoundVoice", -1);
	if(GetGame().IsClient() || !GetGame().IsMultiplayer())//attachments don't generate noise, so we can ignore them on server
		pType.RegisterSoundEvent("SoundAttachment", 0.2);
	
	//pType.RegisterParticleEvent("Particle", -1);

	if(GetGame().IsClient() || !GetGame().IsMultiplayer())//sounds are unnecessary on server
	{
		//! load and register step sound lookup table
		DayZPlayerTypeStepSoundLookupTableImpl stepTable = new DayZPlayerTypeStepSoundLookupTableImpl("CfgVehicles SurvivorBase AnimEvents Steps");
		pType.RegisterStepSoundLookupTable(stepTable);
		
		DayZPlayerTypeAttachmentSoundLookupTableImpl attachTable = new DayZPlayerTypeAttachmentSoundLookupTableImpl("CfgVehicles SurvivorBase AnimEvents Attachments");
		pType.RegisterAttachmentSoundLookupTable(attachTable);
		
		DayZPlayerTypeSoundTableImpl soundTable = new DayZPlayerTypeSoundTableImpl();
		pType.RegisterSoundTable(soundTable);
		
		DayZPlayerSoundVoiceTableImpl voiceTable = new DayZPlayerSoundVoiceTableImpl();
		pType.RegisterSoundVoiceTable(voiceTable);
	}
	GetGame().ProfilerStop("DayZPlayerTypeRegisterSounds");
}