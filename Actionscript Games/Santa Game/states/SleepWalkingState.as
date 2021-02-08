package lib.TisTheSeason.states
{
	import lib.TisTheSeason.Child;
	public class SleepWalkingState implements IChildState
	{
		
		public function update(c:Child):void
		{
			c.x += Math.random() * 15 * Math.cos(Math.random() * 6.28);
			c.y += Math.random() * 15 * Math.sin(Math.random() * 6.28);
		
			var targetAngle: Number = 360;

			if (Math.abs(targetAngle - c.rotation) < c.turnRate) {
				c.rotation = targetAngle;
			} else {
				if (targetAngle - c.rotation > 180) {
					targetAngle -= 360;
				} else if (targetAngle - c.rotation < -180) {
					targetAngle += 360;
				}

				if (targetAngle - c.rotation > 0) {
					c.rotation += c.turnRate;
				} else {
					c.rotation -= c.turnRate;
				}
			}
			
			if (c.numCycles > 250) {c.setState(Child.SLEEP);}
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