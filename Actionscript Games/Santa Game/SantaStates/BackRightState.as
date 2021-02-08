package lib.TisTheSeason.SantaStates
{
	import lib.TisTheSeason.Player;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import lib.TisTheSeason.SantaStates.Segment;
	
	public class BackRightState implements ISantaStates {
		
		private var startRot:Number = 10;
		private var counter:Number = 0;
		private var initial:Boolean = true;
		private var segL:Segment;
		private var segR:Segment;

		public function enterState(player:Player):void{
			player.gotoAndStop(7);
			
			player.santaBR.brArm.rotation = startRot;
			counter = 0;
			
			if (initial == true) {
				initial = false;
				
				//create left segment and attach it to the leg.
				segL = player.createLeg(player.santaBR.brBod, player.santaBR.brLegL);
				player.santaBR.addChildAt(segL,0);
				player.santaBR.brLegL.x = segL.getPin().x;
				player.santaBR.brLegL.y = segL.getPin().y;
				
				segR = player.createLeg(player.santaBR.brBod, player.santaBR.brLegR);
				player.santaBR.addChildAt(segR,0);
				player.santaBR.brLegR.x = segR.getPin().x;
				player.santaBR.brLegR.y = segR.getPin().y;
			}
		}
		
		public function update(player:Player):void
		{
			//move arm forward...
			if (counter % 20 < 10) {
				player.santaBR.brArm.rotation -= 5;
			}//...and back
			else {player.santaBR.brArm.rotation += 5;}
			
			//move legs
			player.walk(segL, player.santaBR.brLegL, player.cycle);
			player.walk(segR, player.santaBR.brLegR, player.cycle + Math.PI);
			
			counter++;
		}

	}
	
}