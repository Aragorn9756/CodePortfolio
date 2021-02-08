package lib.TisTheSeason 
{
	import flash.display.MovieClip;
	import flash.display.StageScaleMode;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import lib.TisTheSeason.TisTheSeasonGame;
	
	public class GameOpen extends MovieClip{
		var animation:Animation

		public function GameOpen()
		{
			stage.scaleMode = StageScaleMode.NO_SCALE;
			
			gotoAndStop(1);
			
			createStartMenu();
		}
		
		private function createStartMenu():void
		{
			var startMenu:StartScreen = new StartScreen(); //create new start screen
			addChild(startMenu);
			startMenu.goButton.addEventListener(MouseEvent.CLICK, animationTest);
		}
		
		private function animationTest(evt: Event): void {
			removeChild(evt.currentTarget.parent);
			evt.currentTarget.removeEventListener(MouseEvent.CLICK, animationTest);
			animation = new Animation();
			addChild(animation);
			animation.x = stage.stageWidth/2;
			animation.y =stage.stageHeight/2;			
			animation.gotoAndPlay(1);
			addEventListener(Event.ENTER_FRAME, animationChecking);
		}
		
		private function animationChecking (evt:Event):void {
			if (animation.currentFrame >= 255) {
				removeChild(animation);
				evt.currentTarget.removeEventListener(Event.ENTER_FRAME, animationChecking);
				createGame();
			}
		}

		private function createGame(): void {
			var game: TisTheSeasonGame = new TisTheSeasonGame();
			addChild(game);
		}
	}
	
}
