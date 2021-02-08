package lib.survive
{
	import flash.display.StageScaleMode;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import lib.survive.ExploreGame;
	import flash.events.Event;
	
	public class ExploreDoc extends MovieClip
	{
		public function ExploreDoc()
		{
			stage.scaleMode = StageScaleMode.NO_SCALE;
			
			gotoAndStop(1);
			
			createStartMenu();
		}
		
		private function createStartMenu():void
		{
			var startMenu:StartScreen = new StartScreen();//create new start screen
			
			addChild(startMenu);
			
			startMenu.startButton.addEventListener(MouseEvent.CLICK, startGameHandler);
			//new start button?
		}
		
		private function startGameHandler(evt:MouseEvent):void
		{
			removeChild(evt.currentTarget.parent);
			
			evt.currentTarget.removeEventListener(MouseEvent.CLICK, startGameHandler);
			
			playIntro()
		}
		
		private function playIntro():void {
			
			gotoAndPlay(3);
			
			addEventListener(Event.ENTER_FRAME, lookForEnd);
		}
		
		private function lookForEnd(evt:Event):void {
			if (currentFrame > 108) {
				gotoAndStop(1);
				removeEventListener(Event.ENTER_FRAME, lookForEnd);
				createGame();
			}
		}
		
		private function createGame():void
		{
			var game:ExploreGame = new ExploreGame();
			
			addChild(game);
		}
	}
}