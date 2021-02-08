package {
	import flash.events.MouseEvent;
	import flash.display.Sprite;
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.KeyboardEvent;
	import flash.ui.Keyboard;
	import flash.events.Event;
	import flash.geom.Point;
	import lib.Particle;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.system.Capabilities;
	import flash.display.StageOrientation;

	//libraries needed for multi touch events
	import flash.ui.Multitouch;
	import flash.ui.MultitouchInputMode;
	import flash.events.MouseEvent;
	import flash.events.TouchEvent;

	//needed for gesture events: 
	import flash.events.GestureEvent;
	import flash.events.GesturePhase;
	import flash.events.TransformGestureEvent;

	import scenes.SceneMain;
	import lib.com.greensock.easing.Ease;

	//needed to trigger an event function
	//when the device display changes between landscape and portrait mode
	import flash.events.StageOrientationEvent;

	public class GameMain extends MovieClip {
		private var win: Boolean = false;
		public var mousePoint: Point;
		public var player: Human = new Human();
		public var frames: int = 0;
		private var gameOver = new GameOver();
		public var scene: SceneMain = new SceneMain(player);
		public var startMenu: _TitleScreen = new _TitleScreen();

		public function GameMain() {
			// constructor code
			init();
		}
		private function init() {
			addChild(scene);
			this.addEventListener(Event.ENTER_FRAME, Update);
		}
		public function Update(e: Event) {
			frames++;
			scene.Update();
			if (SceneMain.NEXTDAY) {
				trace("It's now NEXTDAY in GameMain");
				//this.removeEventListener(Event.ENTER_FRAME, Update);
				SceneMain.NEXTDAY = false;
				//if (this.numChildren > 0) {
					//scene.Clear();
					frames = 0;
					scene.NextDay();
				//}
			}
		}
		private function NextDay(): void {
			if (scene.daysTracker < 6) {
				trace("NexDay(): in GameMain");
				//this.addEventListener(Event.ENTER_FRAME, Update);
				scene.daysTracker++;
				//scene
				//.init();
				trace("daysTracker: " + scene.daysTracker);
			} else if (scene.daysTracker == 6) {
				addChild(startMenu);
				startMenu.width = Capabilities.screenResolutionX;
				startMenu.height = Capabilities.screenResolutionY;
				startMenu.x = 0;
				startMenu.y = 0;

				startMenu.StartBTN.addEventListener(TouchEvent.TOUCH_TAP, NewGame);
			}
		}
		public function NewGame(evt: Event) {
			evt.currentTarget.removeEventListener(TouchEvent.TOUCH_TAP, NewGame);
			removeChild(evt.currentTarget.parent);
			frames = 0;
			startMenu.init();
		}
		private function Clear(): void {
			this.removeChildren();
		}

	}

}