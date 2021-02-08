package  lib.TisTheSeason
{	
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import lib.TisTheSeason.SantaStates.FrontState;
	import lib.TisTheSeason.SantaStates.FrontLeftState;
	import lib.TisTheSeason.SantaStates.LeftState;
	import lib.TisTheSeason.SantaStates.BackLeftState;
	import lib.TisTheSeason.SantaStates.BackState;
	import lib.TisTheSeason.SantaStates.BackRightState;
	import lib.TisTheSeason.SantaStates.RightState;
	import lib.TisTheSeason.SantaStates.FrontRightState;
	import lib.TisTheSeason.SantaStates.ISantaStates;
	import lib.TisTheSeason.SantaStates.RestState;
	import lib.TisTheSeason.SantaStates.Segment;
	
	public class Player extends MovieClip
	{		
		//state constants
		public static const FRONT:ISantaStates = new FrontState();
		public static const FRONTLEFT:ISantaStates = new FrontLeftState();
		public static const LEFT:ISantaStates = new LeftState();
		public static const BACKLEFT:ISantaStates = new BackLeftState();
		public static const BACK:ISantaStates = new BackState();
		public static const BACKRIGHT:ISantaStates = new BackRightState();
		public static const RIGHT:ISantaStates = new RightState();
		public static const FRONTRIGHT:ISantaStates = new FrontRightState();
		public static const REST:ISantaStates  = new RestState();
		
		public var speed:Number;
		public var directionX:String;
		public var directionY:String;
		public var xVel:Number;
		public var yVel:Number;
		public var targetAngle:Number;
		public var currentState:ISantaStates;
		public var previousState:ISantaStates;
		public var cycle:Number = 0;
		
		

		public function Player() {
			//initialize everything
			speed = 0;
			directionX = "none";
			directionY = "none";
			targetAngle = 0;
			xVel = 0;
			yVel = 0;
			currentState = REST;
			previousState = REST;
			currentState.enterState(this);
		}
		
		public function update():void 
		{
			if (directionX != "none" || directionY != "none")
			{
				if (directionY == "down"){
					if (directionX == "left")
					{
						targetAngle = 135;
						currentState = FRONTLEFT;
					}
					else if (directionX == "right")
					{
						targetAngle = 45;
						currentState= FRONTRIGHT;
					}
					else {
						targetAngle = 90;
						currentState = FRONT;
					}
				}
				else if (directionY == "up")
				{
					if (directionX == "left")
					{
						targetAngle = -135;
						currentState = BACKLEFT;
					}
					else if (directionX == "right")
					{
						targetAngle = -45;
						currentState = BACKRIGHT;
					}
					else {
						targetAngle = -90;
						currentState = BACK;
					}
				}
				else if (directionX == "left")
				{
					targetAngle = 180;
					currentState = LEFT;
				}
				else if (directionX == "right") {
					targetAngle = 0;
					currentState = RIGHT;
				}
			}
			else if (directionX == "none" && directionY == "none")
			{
				currentState = REST;
			}
			xVel = Math.cos(targetAngle / 180 * Math.PI) * speed;
			yVel = Math.sin(targetAngle / 180 * Math.PI) * speed;
			
			this.x += xVel;
			this.y += yVel;
			
			//increment cycle to use for kinematics
			cycle += .26895;
			
			if (currentState == REST) cycle = 0;
			if (currentState == FRONT && previousState != FRONT) cycle = 0;
			if (currentState == BACK && previousState != BACK) cycle = 0;
			
			if (currentState != previousState)
			{
				currentState.enterState(this);
			}
			previousState = currentState;
			
			currentState.update(this);
		}
		
		//creates Segment, sets it's length to be the distance between the two movieclips,
		//sets it's x and y to mc1's and sets rotation to point at mc2
		public function createLeg(mc1:MovieClip, mc2:MovieClip):Segment
		{
			//find length between body registration point and leg registration point
			var dx:Number = mc1.x - mc2.x;
			var dy:Number = mc1.y - mc2.y;
			var dist:Number = Math.sqrt((dx*dx) + (dy*dy));
			
			//calculate it's angle
			var angle:Number = Math.atan2(dy, dx)*180/Math.PI*-1;
			//place and postition leg
			var seg:Segment = new Segment(dist, 3);
			seg.x = mc1.x;
			seg.y = mc1.y;
			seg.rotation = angle;
			
			return seg;
		}
		
		//calculations for walking
		public function walk(thigh:Segment, calf:MovieClip, cycle:Number):void
		{
			var angle1:Number = Math.sin(cycle) * 35 + 90;
			var angle2:Number = Math.sin(cycle + Math.PI/(-2))*(15) -90;
			thigh.rotation = angle1;
			calf.rotation = thigh.rotation + angle2;
			calf.x = thigh.getPin().x;
			calf.y = thigh.getPin().y;
		}
	}
	
}
