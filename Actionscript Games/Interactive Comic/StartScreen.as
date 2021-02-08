package {
	import flash.display.Stage;
	import flash.display.StageScaleMode;
	import flash.display.StageAlign;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import GameMain;
	import flash.system.Capabilities;
	import flash.events.TouchEvent;
	import flash.ui.Multitouch;
	import flash.ui.MultitouchInputMode;
	public class StartScreen extends MovieClip {
		public function StartScreen() {
			// constructor code
			init();
		}
		public function init() {
			stage.scaleMode = StageScaleMode.NO_SCALE;
			stage.align = StageAlign.TOP_LEFT;

			createStartMenu();
			trace("Game boot up");
		}
		private function createStartMenu(): void {
			Multitouch.inputMode = MultitouchInputMode.TOUCH_POINT;

			var startMenu: _TitleScreen = new _TitleScreen();
			startMenu.width = Capabilities.screenResolutionX;
			startMenu.height = Capabilities.screenResolutionY;
			startMenu.x = 0;
			startMenu.y = 0;
			addChild(startMenu)

			startMenu.StartBTN.addEventListener(TouchEvent.TOUCH_TAP, startComicHandler);

		}

		private function startComicHandler(evt: TouchEvent): void {
			evt.currentTarget.removeEventListener(TouchEvent.TOUCH_TAP, startComicHandler);
			removeChild(evt.currentTarget.parent);
			createComic();
		}

		private function createComic(): void {
			trace("MakeComic");
			var comic: GameMain = new GameMain();
			addChild(comic);
		}
	}
}