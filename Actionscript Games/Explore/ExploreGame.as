package lib.survive
{
	import flash.text.TextFormat;
	import flash.text.TextField;
	import flash.utils.*;
	import flash.display.MovieClip
	import flash.geom.Point;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.Sprite;
	import flash.events.KeyboardEvent;
	import flash.ui.Keyboard;
	import lib.survive.Player;
	import lib.survive.Particle;
	import com.adobe.tvsdk.mediacore.TextFormat;
	import com.greensock.*;
	
	
	public class ExploreGame extends MovieClip
	{
		private var bullets:Array;
		private var turrets:Array;
		private var batteries:Array
		private var touchLayer:Sprite;
		private var background:Sprite;
		private var player:Player;
		private var particlesLayer:Sprite;
		private var turretsLayer:Sprite;
		private var batteriesLayer:Sprite;
		private var batteriesNum:int;
		private var splodeSpread:Number;
		private var splodeNum:Number;
		private var turretsNum:int;
		private var score:Number;
		private var gameScore:TextField;
		private var splosionShrinkInterval:uint;
		private var splosionRemoveInterval:uint;
		private var splosion:Particle;
		private var healthBar:MovieClip;
		private var healthLabel:TextField;
		
		private var playerHalfWidth:Number = 33;//half the width of the rocket MC
		private var badGuyHalfWidth:Number = 46.5;//half the width of the badGuy MC
		
		public function ExploreGame()
		{
			turretsNum = 10;
			splodeSpread = 0.5;
			splodeNum = 2;
			batteriesNum = 10;
			makeLevelOne();
			
			bullets = new Array();
			
			addEventListener(Event.ENTER_FRAME, update);
			
			touchLayer = new Sprite();
			
			addChild(touchLayer);
			addEventListener(Event.ADDED_TO_STAGE, setupTouchLayer);
			touchLayer.addEventListener(MouseEvent.MOUSE_DOWN, startFiring);
			touchLayer.addEventListener(MouseEvent.MOUSE_UP, stopFiring);
		}
		
		private function startFiring(evt:MouseEvent):void
		{
			player.startFiring();
		}
		
		private function stopFiring(evt:MouseEvent):void
		{
			player.stopFiring();
		}
		
		private function keyDownHandler(evt:KeyboardEvent):void//changed this to allow
		//for movement including thrust
		{
			
			//87=w 68=d 83=s 65=a
			if (evt.keyCode == 87)
			{
				player.directionY = "up";
			}
			else if (evt.keyCode == 83)
			{
				player.directionY = "down";
			}
			else if (evt.keyCode == 68)
			{
				player.directionX = "right";
			}
			else if (evt.keyCode == 65)
			{
				player.directionX = "left";
			}
			//87=w 68=d 83=s 65=a
			/*if (evt.keyCode == Keyboard.W)//changed this
			{
				player.thrust = 50;
			}
			else if (evt.keyCode == Keyboard.S)
			{
				player.thrust = -3;
			}
		
			else if (evt.keyCode == Keyboard.D)
			{
				player.rotationVel = 5;
			}
			else if (evt.keyCode == Keyboard.A)
			{
				player.rotationVel = -5;
			}*/
		}
		
		private function keyUpHandler(evt:KeyboardEvent):void
		{
			//87=w 68=d 83=s 65=a
			/*if (evt.keyCode == Keyboard.W || evt.keyCode == Keyboard.S)
			{
				player.thrust = 0;
			}
			else if (evt.keyCode == Keyboard.A || evt.keyCode == Keyboard.D)
			{
				player.rotationVel = 0;
			}*/
			//87=w 68=d 83=s 65=a
			if (evt.keyCode == 87 || evt.keyCode == 83)
			{
				player.directionY = "none";
				//player.thrust = 0;
			}
			else if (evt.keyCode == 68 || evt.keyCode == 65)
			{
				player.directionX = "none";
				//player.rotates = 0;
			}
		}
		
		private function setupTouchLayer(evt:Event):void
		{
			touchLayer.graphics.beginFill(0x000000, 0);
			touchLayer.graphics.drawRect(0, 0, stage.stageWidth, stage.stageHeight);
			touchLayer.graphics.endFill();
	
			player.x = 2941;
			player.y = 1508;
			stage.addEventListener(KeyboardEvent.KEY_DOWN, keyDownHandler);
			stage.addEventListener(KeyboardEvent.KEY_UP, keyUpHandler);
		}
		
		private function makeLevelOne():void
		{
			player = new Rocket();
			background = new SolarSystem();
			
			var myFormat:TextFormat = new TextFormat();
			myFormat.size = 25;
			
			//make Scoreboard
			score = 0;
			gameScore = new TextField();
			gameScore.x = 552;
			gameScore.y = 76;
			gameScore.textColor = 0xFFFFFF;
			gameScore.background = false;
			gameScore.defaultTextFormat = myFormat;
			gameScore.text = "Enemies Defeated: 0";
			gameScore.width = 400;
			
			//make health bar
			healthLabel = new TextField();
			healthLabel.x = 124;
			healthLabel.y = 492;
			healthLabel.textColor = 0xFFFFFF;
			healthLabel.background = false;
			healthLabel.defaultTextFormat = myFormat;
			healthLabel.text = "Power";
			healthLabel.width = 74;
			
			healthBar = new HealthBar();
			healthBar.height = 34;
			healthBar.width = 400;
			healthBar.x = 202;
			healthBar.y = 493;
			
			addChild(background);
			
			turretsLayer = new Sprite();
			background.addChild(turretsLayer);
			
			batteriesLayer = new Sprite();
			background.addChild(batteriesLayer);
			
			background.addChild(player);
			
			particlesLayer = new Sprite();
			background.addChild(particlesLayer);
			
			makeTurrets();
			makeBatteries();
			
			addChild(gameScore);
			addChild(healthLabel);
			addChild(healthBar);
		}
		
		private function makeTurrets():void
		{
			turrets = new Array();
			
			while (turrets.length < turretsNum)
			{
				var turret:Turret = new BadGuy();
				
				turrets.push(turret);
				turretsLayer.addChild(turret);
				
				turret.target = player;
				
				turret.x = Math.random() * background.width;
				turret.y = Math.random() * background.height;
			}
		}
		
		private function makeBatteries():void {
			batteries = new Array();
			
			while (batteries.length < batteriesNum) {
				var battery:MovieClip = new Battery();
				
				batteries.push(battery);
				batteriesLayer.addChild(battery);
				
				battery.x = Math.random() * background.width;
				battery.y = Math.random() * background.height;
			}
		}
		
		private function updatePlayer():void
		{
			player.update();
			background.x = -player.x + stage.stageWidth / 2;
			background.y = -player.y + stage.stageHeight / 2;
			player.wallCollisionTest(background);
			var shot:Particle = player.fire();
			if (shot != null)
			{
				particlesLayer.addChild(shot);
				bullets.push(shot);
			}
		}
		
		private function killBullet(bullet:Particle):void
		{
			try
			{
				var i:int;
				for (i = 0; i < bullets.length; i++)
				{
					if (bullets[i].name == bullet.name)
					{
						bullets.splice(i, 1);
						particlesLayer.removeChild(bullet);
						
						if (bullet.interacts)
						{
							var j:int;
							for (j = 0; j < splodeNum; j++)
							{
								var splode:Particle = new Explosion();
								splode.scaleX = splode.scaleY = 1 + Math.random();
								splode.x = bullet.x;
								splode.y = bullet.y;
								splode.xVel = Math.random() * splodeSpread - splodeSpread / 2;
								splode.yVel = Math.random() * splodeSpread - splodeSpread / 2;
								splode.life = 20;
								splode.interacts = false;
								bullets.push(splode);
								particlesLayer.addChild(splode);
							}
						}
						
						i = bullets.length;
					}
				}
			}
			catch(e:Error)
			{
				trace("Failed to delete bullet!", e);
			}
		}
		
		private function update(evt:Event):void
		{
			//trace(turretsLayer.x, particlesLayer.x);
			
			var target:Point = new Point(stage.mouseX, stage.mouseY);
			
			var angleRad:Number = Math.atan2(target.y, target.x);
			
			var angle:Number = angleRad * 180 / Math.PI;
			
			updatePlayer();
			
			/*if (player.getHealth <= 0) {
				endGame();
			}*/
			
			checkBatteryCollision();
			
			var i:Number = 0;	
			
			for each (var bullet:Particle in bullets)
			{
				bullet.update();
				
				if (bullet.life <= 0)
				{
					killBullet(bullet);
				}
				else if (bullet.interacts)
				{
					if (bullet.ownedByPlayer)
					{
						for each (var targetTurret:Turret in turrets)
						{
							if (targetTurret.hitTestPoint(bullet.x + background.x, bullet.y + background.y, true))
							{
								killBullet(bullet);
								targetTurret.hit(1);//added this
								checkTurretHealth(targetTurret, i);
								
								break;
							}
							i++;//keeps track of turret index
						}
					}
					else
					{
						if (player.hitTestPoint(bullet.x + background.x, bullet.y + background.y, true))
						{
							killBullet(bullet);
							player.hit(1, healthBar);
						}
					}
				}
			}
			i = 0;//reinitialize i for recording index values in array
			for each (var turret:Turret in turrets)
			{
				collisionCheck(turret, i);
				i++;
				
				var shot:Particle = turret.update();
				if (shot != null)
				{
					particlesLayer.addChild(shot);
					bullets.push(shot);
				}
			}
		}
		
		//checks to see if player has hit the reference point of the battery movieclip.
		//if so, battery is deleted and replaced, and player gets +25 health
		private function checkBatteryCollision ():void {
			
			var i:Number = 0;
			
			for each (var battery:Battery in batteries) {
				
				if (player.hitTestPoint(battery.x + background.x, battery.y + background.y, true)) {
					
					removeBattery(battery, i);
					
					 var healthLoss:Number = player.initialLife - player.getLife();
					
					//if less than 25 pts health lost, refill as much health lost
					if (healthLoss < 25) {
						player.rechargeBattery(healthLoss, healthBar);
					}
					//otherwise replenish 25 pts
					else {
						player.rechargeBattery(25, healthBar)
					}
					
					return;
				}
				
				i++
			}
		}
		
		//delete battery and respawn somewhere else on the field.
		private function removeBattery (battery:Battery, index:Number):void {
			
			batteriesLayer.removeChild(battery);
			delete batteries[index];
			
			var newBattery:Battery = new Battery();
			batteries.push(newBattery);
			batteriesLayer.addChild(newBattery);
			
			newBattery.x = Math.random() * background.width;
			newBattery.y = Math.random() * background.height;
			
		}
		
		//checks turret health. if health is below 0, then the turret is destroyed and 
		//replaced
		private function checkTurretHealth (turret:Turret, index:Number):void {
			if (turret.getTurretLife() <= 0){
				killTurret(turret,index);
				
				//add another turret in its place
				var newTurret:Turret = new BadGuy();
				turrets.push(newTurret);
				turretsLayer.addChild(newTurret);
				
				newTurret.target = player;
				
				newTurret.x = Math.random() * background.width;
				newTurret.y = Math.random() * background.height;
			}
			
			return;
		}
		
		private function killTurret(turret:Turret, index:Number):void {
			
			//hold onto coordinates of the turret
			var splosionX:Number = turret.x;
			var splosionY:Number = turret.y;
			
			//get rid of turret
			turretsLayer.removeChild(turret);
			turret.target = null;
			delete turrets[index];
			
			//SPLOSION!!!
			splosion = new Splosion();
			splosion.x = splosionX;
			splosion.y = splosionY;
			splosion.life = 3;
			
			turretsLayer.addChild(splosion);
			//TO-DO:!!! find a way to put pauses between the next three actions
			TweenLite.to(splosion, 1, {scaleX:3, scaleY:3, rotation:360});
			splosionShrinkInterval = setInterval(splosionShrink, 1000);
			splosionRemoveInterval = setInterval(splosionRemove, 2000);
			
			//increment score
			score++;
			gameScore.text = "Enemies Defeated: " + score.toString();
			
			//interval functions
			function splosionShrink ():void {
				TweenLite.to(splosion, 1, {scaleX:.33, scaleY:.33, rotation:360});
				clearInterval(splosionShrinkInterval);
			}
			
			function splosionRemove():void {
				turretsLayer.removeChild(splosion);
				clearInterval(splosionRemoveInterval);
			}
		}
		
		//looks at the position of the player and each of the turrets. if the player hits
		//a turret, the player bounces off and the turrets take 5 damage 
		private function collisionCheck(turret:Turret, i:Number):void {
			/*
			var dx:Number = turret.x - player.x;
			var dy:Number = turret.y - player.y;
			var dist:Number = Math.sqrt((dx * dx) - (dy * dy));
			var minDist = playerHalfWidth + badGuyHalfWidth;*/
			
			//if (dist <= minDist) {
			if (turret.hitTestObject(player)) {
				turret.hit(5);
				checkTurretHealth(turret, i);
									
				player.xVel *= -2;
				player.yVel *= -2;
			}
			
			return;
		}
		
		//TODO: complete endgame
		private function endGame ():void {
			//delete all children and return to start screen.
		}
	}
}