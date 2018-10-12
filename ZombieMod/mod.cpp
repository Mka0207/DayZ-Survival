class CfgMods
{
	class ZombieMod
	{
		dir = "ZombieMod";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "Fixed FPP Camera";
		credits = "Jacob_Mango, Sumrak";
		author = "Jacob Kumar";
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
