package lib.TisTheSeason
{
	import lib.TisTheSeason.Child;
	import flash.display.Sprite;
	import flash.display.MovieClip;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.ui.Keyboard;
	import flash.text.*;
	import flash.text.engine.TabAlignment;
	import lib.TisTheSeason.Player;
	import lib.TisTheSeason.Child;
	
	public class TisTheSeasonGame extends MovieClip 
	{
		var background:Sprite;
		var presentsLayer:Sprite;
		var characterLayer:Sprite;
		var wallLayer:Sprite;
		var wallsPic:WallsPic;
		var player:Player;
		var childrenArray: Array;
		var tree:MovieClip;
		var carpet:Sprite;
		var wallsDetection:Sprite;
		private var scoreText:TextField;
		private var score:uint;
		var housePresents:Array;
		var santaPresents:Array;
		var numPresents:Number = 15;

		
		public function TisTheSeasonGame() {
			childrenArray = new Array();
			addEventListener(Event.ENTER_FRAME, gameLoop);
			background = new Floor();
			addChild(background);
			setUpLayers();
			santaPresents = new Array();
			addEventListener(Event.ADDED_TO_STAGE, setupKeyHandlers);
		}
		
		private function setupKeyHandlers(evt:Event):void
		{
			stage.addEventListener(KeyboardEvent.KEY_DOWN, keyDownHandler);
			stage.addEventListener(KeyboardEvent.KEY_UP, keyUpHandler);
		}
		
		private function setUpLayers():void
		{
			
			wallLayer = new Sprite();
			background.addChild(wallLayer);
			wallsPic = new WallsPic();
			wallLayer.addChild(wallsPic);
			
			presentsLayer = new Sprite();
			background.addChild(presentsLayer);
			//addPresents();
			
			player = new SantaClip();
			background.addChild(player);
			
			for (var i: int = 0; i < 20; i++) {
				var child: Child;
				child = new BKid();
				child.setTarget(player);
				background.addChild(child);
				childrenArray.push(child)
				child.x = Math.random() * wallsPic.width - wallsPic.width/2;
				child.y = Math.random() * wallsPic.height - wallsPic.height/2;
			}
			
			tree = new Tree();
			tree.x = 116;
			tree.y = -550;
			background.addChild(tree);
			
			carpet = new Carpet();
			background.addChild(carpet);
			wallsDetection = new WallsDetection();
			background.addChildAt(wallsDetection, 0);//puts WallsDetection behind everything
			
			/*scoreText = new TextField;
			scoreText.x = 10;
			scoreText.y = 10;
			scoreText.width = 400;
			scoreText.textColor = 0xffffff;
			addEventListener(Event.ENTER_FRAME, startingScore);
			addChild(scoreText);

			function startingScore(evt:Event): void 
			{
				score = 0;
				scoreText = score;
			removeEventListener(Event.ENTER_FRAME, startingScore);
			}*/

		}
		
		/*private function addPresents():void
		{
			housePresents = new Array();
			var i = 0;
			while (i < numPresents){
				var present:MovieClip = new Present1();
				
				housePresents.push(present);
				presentsLayer.addChild(present);
				
				present.x = Math.random() * background.width;
				present.y = Math.random() * background.height;
			}
		}*/
		
		private function keyDownHandler(evt:KeyboardEvent):void
		{
			player.speed = 10
			if (evt.keyCode == 38)
			{
				player.directionY = "up";
			}
			else if (evt.keyCode == 40)
			{
				player.directionY = "down";
			}
			else if (evt.keyCode == 39)
			{
				player.directionX = "right";
			}
			else if (evt.keyCode == 37)
			{
				player.directionX = "left";
			}
		}
		
		private function keyUpHandler(evt:KeyboardEvent):void
		{
			
			if (evt.keyCode == 38 || evt.keyCode == 40)
			{
				player.directionY = "none";
				//player.thrust = 0;
			}
			else if (evt.keyCode == 37 || evt.keyCode == 39)
			{
				player.directionX = "none";
				//player.rotates = 0;
			}
			if(player.directionX == "none" && player.directionY == "none")
			{
				player.speed = 0;
			}
		}
		
		private function gameLoop(e:Event):void 
		{
			updatePlayer();
			
			for (var i: int = 0; i < childrenArray.length; i++) {
				childrenArray[i].update(wallsDetection,background);
			}
		}
		
		private function updatePlayer():void 
		{
			player.update();
			background.x = -player.x + stage.stageWidth / 2;
			background.y = -player.y + stage.stageHeight / 2;
			wallCollisionTest();
		}
		
		public function wallCollisionTest ():void 
		{
			while (wallsDetection.hitTestPoint(player.x+background.x, player.y + player.height/2+background.y, true)) {
				player.speed = 0;
				player.y -= 1;
			}
			while (wallsDetection.hitTestPoint(player.x+background.x, player.y - player.height/2+background.y, true)) {
				player.speed = 0;
				player.y += 1;
			} 
			while (wallsDetection.hitTestPoint(player.x - player.width/2+background.x, player.y+background.y, true)) {
				player.speed = 0;
				player.x += 1;
			}
			while (wallsDetection.hitTestPoint(player.x + player.width/2+background.x, player.y+background.y, true)) {
				player.speed = 0;
				player.x -= 1;
			}
			return;
		}
		
	}
	
}