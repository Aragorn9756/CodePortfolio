package lib.TisTheSeason.states
{
	import lib.TisTheSeason.Child;
	
	public interface IChildState 
	{
		function update(c:Child):void;
		function enter(c:Child):void;
		function exit(c:Child):void;
	}
	
}