//Advert System by mka0207@fwkzt.com

const float ADVERT_DELAY = 120;
float AdCheckTimer = 0.0;

TStringArray Timed_Adverts()
{
	return {
	"Contact Us @ discord.gg/npTNKeM",
	"Support Us @ fwkzt.com/donate",
	"Maintained and developed by FWKZT.com",
	"Server Changelog posted on discord.",
	"Want to tell us we suck? Tell us we don't? Join our discord to post feedback of suggestions! discord.gg/npTNKeM",
	"We also have a deathmatch server! Check our discord for info: discord.gg/npTNKeM",
	"Server restarts every 4 hours!"};
}

void OnTickAdverts( float timeslice )
{
	//Advert Custom Code
	AdCheckTimer += timeslice;
	if ( AdCheckTimer > ADVERT_DELAY )
	{
		AdCheckTimer = 0;
		GetGame().ChatPlayer( 0, Timed_Adverts().GetRandomElement() );
	}
}