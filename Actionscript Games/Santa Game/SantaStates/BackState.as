package lib.TisTheSeason.SantaStates
{
	import lib.TisTheSeason.Player;
	import flash.display.MovieClip;
	
	public class BackState implements ISantaStates {
		
		//holds the original y position of the legs relative to the movieclip
		private var originalPos:Number = 39.05;
		private var counter:Number = 0;
		
		public function enterState(player:Player):void
		{
			player.gotoAndStop(6);
			
			//reset arm and legs if restarting the animation
			if (player.cycle == 0)
			{
				player.santaB.bArm.rotation = 0;
				player.santaB.bLegL.y = originalPos;
				player.santaB.bLegR.y = originalPos;
				
				counter = 0;
			}
			
		}

		public function update(player:Player):void
		{
			if (player.cycle >= 1.3) counter++;
			//make legs move one direction for the first 5 frames, then every other ten frames
			if (counter % 20 == 0 || counter%20 > 10)
			{
				player.santaB.bLegL.y += 1;
				player.santaB.bLegR.y -= 1;
				player.santaB.bArm.rotation += 5;
			}
			else//make the legs reverse for 10 frames
			{
				player.santaB.bLegL.y -= 1;
				player.santaB.bLegR.y += 1;
				player.santaB.bArm.rotation -= 5;
			}
		}

	}
	
}