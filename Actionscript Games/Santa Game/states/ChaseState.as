package lib.TisTheSeason.states
{
	import lib.TisTheSeason.Child;
	public class ChaseState implements IChildState
	{
		
		/* INTERFACE agent.states.IChildState */
		
		public function update(c:Child):void
		{
			//what the kid does during the state
		}
		
		public function enter(c:Child):void
		{
			//what the kid does when the state begins
		}
		
		public function exit(c:Child):void
		{
			//what the kid does when the state ends
		}
		
	}

}