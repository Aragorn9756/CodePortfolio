package lib.TisTheSeason.states {
	
	import lib.TisTheSeason.Child;
	public class SleepingState implements IChildState{

		public function update(c:Child):void
		{
			if (c.numCycles > 250) {
					c.setState(Child.SLEEPWALK);
				}

			var targetAngle: Number = -90;

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
				
				c.gotoAndPlay(2);
				trace("hi")
				
			}
		}
		
		public function enter(c:Child):void
		{
			//what the kid does when the state begin
				c.say("Z z Z");
				c.speed = 3;
		}
		
		public function exit(c:Child):void
		{
			//what the kid does when the state ends
			c.gotoAndPlay(1);
		}
	}
	
}
