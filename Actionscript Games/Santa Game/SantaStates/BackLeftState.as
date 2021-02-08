package lib.TisTheSeason.SantaStates
{
	import lib.TisTheSeason.Player;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import lib.TisTheSeason.SantaStates.Segment;
	
	public class BackLeftState implements ISantaStates {
		
		private var startRot:Number = -10;
		private var counter:Number = 0;
		private var initial:Boolean = true;
		private var segL:Segment;
		private var segR:Segment;

		public function enterState(player:Player):void{
			player.gotoAndStop(5);
			player.santaBL.blArm.rotation = startRot;
			counter = 0;
			
			if (initial == true) {
				initial = false;
				
				//create left segment and attach it to the leg.
				segL = player.createLeg(player.santaBL.blBod, player.santaBL.blLegL);
				player.santaBL.addChildAt(segL,0);
				player.santaBL.blLegL.x = segL.getPin().x;
				player.santaBL.blLegL.y = segL.getPin().y;
				
				segR = player.createLeg(player.santaBL.blBod, player.santaBL.blLegR);
				player.santaBL.addChildAt(segR,0);
				player.santaBL.blLegR.x = segR.getPin().x;
				player.santaBL.blLegR.y = segR.getPin().y;
			}
		}
		
		public function update(player:Player):void
		{
			//move arm forward...
			if (counter % 20 < 10) {
				player.santaBL.blArm.rotation += 5;
			}//...and back
			else {player.santaBL.blArm.rotation -= 5;}
			
			//move legs
			player.walk(segL, player.santaBL.blLegL, player.cycle);
			player.walk(segR, player.santaBL.blLegR, player.cycle + Math.PI);
			
			counter++;
		}
		
	}
	
}