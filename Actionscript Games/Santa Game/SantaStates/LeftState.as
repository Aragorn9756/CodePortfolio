package lib.TisTheSeason.SantaStates
{
	import lib.TisTheSeason.Player;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import lib.TisTheSeason.SantaStates.Segment;
	
	public class LeftState implements ISantaStates {
		
		private var startRot:Number = 25;
		private var counter:Number = 0;
		private var initial:Boolean = true;
		private var segL:Segment;
		private var segR:Segment;

		public function enterState(player:Player):void{
			player.gotoAndStop(4);
			
			player.santaL.lArm.rotation = startRot;
			counter = 0;
			
			if (initial == true) {
				initial = false;
				
				//create left segment and attach it to the leg.
				segL = player.createLeg(player.santaL.lBod, player.santaL.lLegL);
				player.santaL.addChildAt(segL,0);
				player.santaL.lLegL.x = segL.getPin().x;
				player.santaL.lLegL.y = segL.getPin().y;
				
				segR = player.createLeg(player.santaL.lBod, player.santaL.lLegR);
				player.santaL.addChildAt(segR,0);
				player.santaL.lLegR.x = segR.getPin().x;
				player.santaL.lLegR.y = segR.getPin().y;
			}
		}
		
		public function update(player:Player):void
		{
			//move arm forward...
			if (counter % 20 < 10) {
				player.santaL.lArm.rotation += 5;
			}//...and back
			else {player.santaL.lArm.rotation -= 5;}
			
			//move legs
			player.walk(segL, player.santaL.lLegL, player.cycle);
			player.walk(segR, player.santaL.lLegR, player.cycle + Math.PI);
			
			counter++;
		}
	}
	
}