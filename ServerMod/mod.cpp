class CfgMods
{
	class ServerMod
	{
		dir = "ServerMod";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "Server side changes, using DrZed's Zombiemod as reference";
		credits = "Mka0207";
		author = "Mka0207";
		authorID = "0"; 
		version = "1.0"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game", "World", "Mission"};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"com/CameraMod/scripts/3_Game"};
			};

			class worldScriptModule
			{
				value = "";
				files[] = {"com/CameraMod/scripts/4_World"};
			};

			class missionScriptModule
			{
				value = "";
				files[] = {"com/CameraMod/scripts/5_Mission"};
			};
		}
	};
};
