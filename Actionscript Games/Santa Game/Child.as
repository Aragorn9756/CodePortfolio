package lib.TisTheSeason {
	import lib.TisTheSeason.states.ChaseState;
	import lib.TisTheSeason.states.IChildState;
	import lib.TisTheSeason.states.SleepingState;
	import lib.TisTheSeason.states.SleepWalkingState;
	import lib.TisTheSeason.TisTheSeasonGame;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFormat;

	public class Child extends MovieClip {
		public static const SLEEP: IChildState = new SleepingState(); //Define possible states as static constants
		public static const SLEEPWALK: IChildState = new SleepWalkingState();
		public static const CHASE: IChildState = new ChaseState();

		private const RAD_DEG: Number = 180 / Math.PI;

		private var _previousState: IChildState; //The previous executing state
		private var _currentState: IChildState; //The currently executing state
		public var speed: Number = 0;
		public var velocity: Point = new Point();
		private var target;
		public var chaseRadius: Number = 150; //If the mouse is "seen" within this radius, we want to chase
		public var numCycles: int = 0; //Number of updates that have executed for the current state. Timing utility.
		public var turnRate:Number;
		public var _tf:TextField;
		
		public function Child() {
			_currentState = SLEEP;
			turnRate = 10;
			x = 100;
			y = 100;
			_tf = new TextField();
			_tf.defaultTextFormat = new TextFormat("_sans", 10);
			_tf.autoSize = TextFieldAutoSize.LEFT;
			addChild(_tf);
		}
		
		public function say(str:String):void {
			_tf.text = str;
			_tf.y = -_tf.height - 2;
		}

		public function getdistanceToPlayer(): Number {
			var dx: Number = x - target.x;
			var dy: Number = y - target.y;
			return Math.sqrt(dx * dx + dy * dy);
		}

		public function setTarget(player): void {
			target = player;
		}
		public function randomDirection(): void {
			var a: Number = Math.random() * 6.28;
			velocity.x = Math.cos(a);
			velocity.y = Math.sin(a);
		}

		/**
		 * Update the current state, then update the graphics
		 */
		public function update(wallsDetection,background): void {
			if (!_currentState) return; //If there's no behavior, we do nothing
			_currentState.update(this);
			if (_currentState != CHASE) //turns off timer while chasing
			{
				numCycles++;
			}
			x += velocity.x * speed;
			y += velocity.y * speed;
			
			trace(numCycles);
			wallCollisionTest(wallsDetection,background);
		}

		public function setState(newState: IChildState): void {
			if (_currentState == newState) return;
			if (_currentState) {
				_currentState.exit(this);
			}
			_previousState = _currentState;
			_currentState = newState;
			_currentState.enter(this);
			numCycles = 0;
		}

		public function get previousState(): IChildState {
			return _previousState;
		}

		public function get currentState(): IChildState {
			return _currentState;
		}
		
		public function wallCollisionTest(wallsDetection,background): void {
			while (wallsDetection.hitTestPoint(this.x + background.x, this.y + this.height / 2 + background.y, true)) {
				this.speed = 0;
				this.y -= 1;
			}
			while (wallsDetection.hitTestPoint(this.x + background.x, this.y - this.height / 2 + background.y, true)) {
				this.speed = 0;
				this.y += 1;
			}
			while (wallsDetection.hitTestPoint(this.x - this.width / 2 + background.x, this.y + background.y, true)) {
				this.speed = 0;
				this.x += 1;
			}
			while (wallsDetection.hitTestPoint(this.x + this.width / 2 + background.x, this.y + background.y, true)) {
				this.speed = 0;
				this.x -= 1;
			}
			return;
		}

	}

}