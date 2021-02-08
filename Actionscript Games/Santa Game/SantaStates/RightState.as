package lib.TisTheSeason.SantaStates
{
	import lib.TisTheSeason.Player;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import lib.TisTheSeason.SantaStates.Segment;
	
	public class RightState implements ISantaStates {
		
		private var startRot:Number = -25;
		private var counter:Number = 0;
		private var initial:Boolean = true;
		private var segL:Segment;
		private var segR:Segment;

		public function enterState(player:Player):void{
			player.gotoAndStop(8);
			
			player.santaR.rArm.rotation = startRot;
			counter = 0;
			
			if (initial == true) {
				initial = false;
				
				//create left segment and attach it to the leg.
				segL = player.createLeg(player.santaR.rBod, player.santaR.rLegL);
				player.santaR.addChildAt(segL,0);
				player.santaR.rLegL.x = segL.getPin().x;
				player.santaR.rLegL.y = segL.getPin().y;
				
				segR = player.createLeg(player.santaR.rBod, player.santaR.rLegR);
				player.santaR.addChildAt(segR,0);
				player.santaR.rLegR.x = segR.getPin().x;
				player.santaR.rLegR.y = segR.getPin().y;
			}
		}
		
		public function update(player:Player):void
		{
			//move arm forward...
			if (counter % 20 < 10) {
				player.santaR.rArm.rotation -= 5;
			}//...and back
			else {player.santaR.rArm.rotation += 5;}
			
			//move legs
			player.walk(segL, player.santaR.rLegL, player.cycle);
			player.walk(segR, player.santaR.rLegR, player.cycle + Math.PI);
			
			counter++;
		}

	}
	
}