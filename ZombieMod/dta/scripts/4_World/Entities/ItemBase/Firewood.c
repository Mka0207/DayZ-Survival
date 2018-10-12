class Firewood extends ItemBase
{
	override bool CanPutInCargo( EntityAI parent )
	{
		if ( super.CanPutInCargo(parent) || !( this.GetQuantity() > 5 ) )
		{
			return true;
		}
		return false;
	}
}