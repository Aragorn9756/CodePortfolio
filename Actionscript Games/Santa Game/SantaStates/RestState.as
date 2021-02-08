package lib.TisTheSeason.SantaStates
{
	import lib.TisTheSeason.Player;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import lib.TisTheSeason.SantaStates.Segment;
	
	public class RestState implements ISantaStates {
		
		private var originalPos:Number = 31.5;
		private var angleDiff:Number = 42.1369;//difference in angle between armUp and armSeg

		public function enterState(player:Player):void{
			player.gotoAndStop(10);
		}
		
		public function update(player:Player):void
		{
			
		}

	}
	
}