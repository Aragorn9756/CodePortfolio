package lib.TisTheSeason.SantaStates
{
	import lib.TisTheSeason.Player;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import lib.TisTheSeason.SantaStates.Segment;
	
	public class FrontRightState implements ISantaStates {
		
		private var startRot:Number = 10;
		private var counter:Number = 0;
		private var initial:Boolean = true;
		private var segL:Segment;
		private var segR:Segment;

		public function enterState(player:Player):void{
			player.gotoAndStop(9);
			
			player.santaFR.frArm.rotation = startRot;
			counter = 0;
			
			if (initial == true) {
				initial = false;
				
				//create left segment and attach it to the leg.
				segL = player.createLeg(player.santaFR.frBod, player.santaFR.frLegL);
				player.santaFR.addChildAt(segL,0);
				player.santaFR.frLegL.x = segL.getPin().x;
				player.santaFR.frLegL.y = segL.getPin().y;
				
				segR = player.createLeg(player.santaFR.frBod, player.santaFR.frLegR);
				player.santaFR.addChildAt(segR,0);
				player.santaFR.frLegR.x = segR.getPin().x;
				player.santaFR.frLegR.y = segR.getPin().y;
			}
		}
		
		public function update(player:Player):void
		{
			//move arm forward...
			if (counter % 20 < 10) {
				player.santaFR.frArm.rotation -= 5;
			}//...and back
			else {player.santaFR.frArm.rotation += 5;}
			
			//move legs
			player.walk(segL, player.santaFR.frLegL, player.cycle);
			player.walk(segR, player.santaFR.frLegR, player.cycle + Math.PI);
			
			counter++;
		}

	}
	
}