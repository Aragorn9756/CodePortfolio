package lib.TisTheSeason.SantaStates
{
	import lib.TisTheSeason.Player;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import lib.TisTheSeason.SantaStates.Segment;
	
	public class FrontLeftState implements ISantaStates {
		
		private var startRot:Number = -15;
		private var counter:Number = 0;
		private var initial:Boolean = true;
		private var segL:Segment;
		private var segR:Segment;

		public function enterState(player:Player):void{
			player.gotoAndStop(3);
			player.santaFL.flArm.rotation = startRot;
			counter = 0;
			if (initial == true) {
				initial = false;
				
				//create left segment and attach it to the leg.
				segL = player.createLeg(player.santaFL.flBod, player.santaFL.flLegL);
				player.santaFL.addChildAt(segL,0);
				player.santaFL.flLegL.x = segL.getPin().x;
				player.santaFL.flLegL.y = segL.getPin().y;
				
				segR = player.createLeg(player.santaFL.flBod, player.santaFL.flLegR);
				player.santaFL.addChildAt(segR,0);
				player.santaFL.flLegR.x = segR.getPin().x;
				player.santaFL.flLegR.y = segR.getPin().y;
			}
		}
		
		public function update(player:Player):void
		{
			//move arm forward...
			if (counter % 20 < 10) {
				player.santaFL.flArm.rotation += 5;
			}//...and back
			else {player.santaFL.flArm.rotation -= 5;}
			
			//move legs
			player.walk(segL, player.santaFL.flLegL, player.cycle);
			player.walk(segR, player.santaFL.flLegR, player.cycle + Math.PI);
			
			counter++;
		}

	}
	
}