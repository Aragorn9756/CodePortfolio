package lib.TisTheSeason.SantaStates
{
	import lib.TisTheSeason.Player;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import lib.TisTheSeason.SantaStates.Segment;
	
	public class FrontState implements ISantaStates {
		
		//holds the original y position of the legs relative to the movieclip
		private var originalPos:Number = 31.5;
		private var counter:Number = 0;
		private var initial:Boolean = true;
		private var armSeg:Segment;
		private var angleDiff:Number = 42.1369;//difference in angle between armUp and armSeg

		public function enterState(player:Player):void{
			player.gotoAndStop(2);
			
			if (initial == true) {
				initial = false;
				
				//create left segment and attach it to the leg.
				armSeg = player.createLeg(player.santaF.armUp, player.santaF.armLow);
				armSeg.rotation -= 95;
				player.santaF.addChildAt(armSeg, 0);
				player.santaF.armLow.x = armSeg.getPin().x;
				player.santaF.armLow.y = armSeg.getPin().y;
			}
			
			if (player.cycle == 0)
			{
				player.santaF.fLegL.y = originalPos;
				player.santaF.fLegR.y = originalPos;
				
				//reset arm
				player.santaF.armUp.rotation = 0;
				player.santaF.armLow.rotation = 0;
				armSeg.rotation = angleDiff;
				player.santaF.armLow.x = armSeg.getPin().x;
				player.santaF.armLow.y = armSeg.getPin().y;
				
				counter = 0;
			}
		}
		
		public function update(player:Player):void
		{
			//wait 5 cycles
			if (player.cycle >= 1.3) counter++;
			//make legs move one direction for the first 5 frames, then every other ten frames
			if (counter % 20 == 0 || counter%20 > 10)
			{
				player.santaF.fLegL.y += 1;
				player.santaF.fLegR.y -= 1;
			}
			else//make the legs reverse for 10 frames
			{
				player.santaF.fLegL.y -= 1;
				player.santaF.fLegR.y += 1;
			}
			
			//make arm move
			swingArm(player.santaF.armUp, player.santaF.armLow, player.cycle);
		}
		
		//calculations for swinging his arm
		public function swingArm(upper:MovieClip, lower:MovieClip, cycle:Number):void
		{
			var angle1:Number = Math.sin(cycle) * 15 + angleDiff;
			var angle2:Number = Math.sin(cycle + Math.PI/(-2))*15;
			armSeg.rotation = angle1;
			upper.rotation = angle1 - angleDiff;
			lower.rotation = upper.rotation + angle2;
			lower.x = armSeg.getPin().x;
			lower.y = armSeg.getPin().y;
		}

	}
	
}
