package scenes {

	import scenes.states.Bedroom;
	import scenes.states.Breakroom;
	import scenes.states.BusInside;
	import scenes.states.BusStop;
	import scenes.states.CubicleOthers;
	import scenes.states.CubicleYours;
	import scenes.states.ElevatorIn;
	import scenes.states.ElevatorOut;
	import scenes.states.FlowerShopIn;
	import scenes.states.FlowerShopOut;
	import scenes.states.NewsStand;
	import scenes.states.OfficeHall;
	import scenes.states.iBehaviors;
	import scenes.states.CubicleYours_Laptop;
	//importing the Scene State Machine

	import scenes.colorState.iColors;
	import scenes.colorState.Black;
	import scenes.colorState.Sepia;
	import scenes.colorState.Desaturated;
	import scenes.colorState.FullColor;
	//importing the Color State Machine

	import lib.com.greensock.*;

	import flash.geom.Point;
	import flash.geom.Matrix;
	import flash.geom.Rectangle;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.ui.Keyboard;
	import flash.events.KeyboardEvent;
	import flash.events.Event;
	import flash.display.Shape;
	import flash.events.MouseEvent;

	//needed for multitouch
	import flash.events.TouchEvent;
	import flash.ui.Multitouch;
	import flash.ui.MultitouchInputMode;

	//needed for gesture events
	import flash.events.GestureEvent;
	import flash.events.GesturePhase;
	import flash.events.TransformGestureEvent;

	//needed for the Accelerometer
	import flash.sensors.Accelerometer;
	import flash.events.AccelerometerEvent;

	//needed for custom scaling based on the display
	import flash.display.Stage;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.system.Capabilities;

	//needed to trigger an event function
	//when the device display changes between landscape and portrait mode
	import flash.events.StageOrientationEvent;
	import flash.globalization.LastOperationStatus;

	//needed for the TextField
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;

	//for setInterval function
	import flash.utils.*;
	import fl.transitions.Tween;
	import fl.transitions.easing.None;
	import flash.events.TimerEvent;

	public class SceneMain extends MovieClip {

		public static const COLOR_CHANGE: String = "NewColor";

		public static const BED_ROOM: iBehaviors = new Bedroom();
		public static const BREAK_ROOM: iBehaviors = new Breakroom();
		public static const BUS_INSIDE: iBehaviors = new BusInside();
		public static const BUS_STOP: iBehaviors = new BusStop();
		public static const CUBICLE_OTHERS: iBehaviors = new CubicleOthers();
		public static const CUBICLE_YOURS: iBehaviors = new CubicleYours();
		public static const CUBICLE_YOURS_LAPTOP: iBehaviors = new CubicleYours_Laptop();
		public static const ELEVATOR_IN: iBehaviors = new ElevatorIn();
		public static const ELEVATOR_OUT: iBehaviors = new ElevatorOut();
		public static const FLOWER_SHOP_IN: iBehaviors = new FlowerShopIn();
		public static const FLOWER_SHOP_OUT: iBehaviors = new FlowerShopOut();
		public static const NEWS_STAND: iBehaviors = new NewsStand();
		public static const OFFICE_HALL: iBehaviors = new OfficeHall();
		//initializing the Scene States, to refence the states use the ALL_CAPS so that it's immediately obvious

		public static const BLACK: iColors = new Black();
		public static const SEPIA: iColors = new Sepia();
		public static const DESATURATED: iColors = new Desaturated();
		public static const COLOR: iColors = new FullColor();
		//initializing the Color States

		private var bedroom: MovieClip = new _Bedroom();
		private var breakroom: MovieClip = new _Breakroom();
		private var busInside: MovieClip = new _BusInside();
		private var busStop: MovieClip = new _BusStop();
		private var cubicleOthers: MovieClip = new _CubicleOthers();
		private var cubicleYours: MovieClip = new _CubicleYours();
		private var cubicleYours_Laptop: MovieClip = new _CubicleYours_Laptop();
		private var elevatorIn: MovieClip = new _ElevatorIn();
		private var elevatorOut: MovieClip = new _ElevatorOut();
		private var flowerShopIn: MovieClip = new _FlowerShopIn();
		private var flowerShopOut: MovieClip = new _FlowerShopOut();
		private var newsStand: MovieClip = new _NewsStand();
		private var officeHall: MovieClip = new _OfficeHall();
		//initializing all the Scene MovieClips

		private var _MapsStateArray: Array = [BED_ROOM, BREAK_ROOM, BUS_INSIDE, BUS_STOP, CUBICLE_OTHERS, CUBICLE_YOURS, CUBICLE_YOURS_LAPTOP, ELEVATOR_IN, ELEVATOR_OUT, FLOWER_SHOP_IN, FLOWER_SHOP_OUT, NEWS_STAND, OFFICE_HALL];
		private var _ColorStateArray: Array = [BLACK, SEPIA, DESATURATED, COLOR];
		//the _MapsStateArray Array is going to hold all of our Scene States
		//the _ColorStateArray Array is going to hold all of our Color States
		private var _MapsMCArray: Array = new Array();
		private var _ColorMCArray: Array = new Array();
		//the _MapsArray Array is going to hold all of our Scene MovieClips
		//the _ColorArray Array is going to hold all of the Color Variations of each of our Scene MovieClips during the ColorChange() function

		public const RAD_DEG: Number = 180 / Math.PI; //for converting radians to degrees if we need it to make code more understandable at a glance

		public var isActive: Boolean = false; //can be used to set the current Scene "Active" or "Inactive"

		public var _previousScene: iBehaviors; //The previously executing scene
		public var _currentScene: iBehaviors; //The currently executing scene

		public var _previousColor: iColors; //The previously executing color
		public var _currentColor: iColors; //The currently executing color

		public var grabRadius: Number = 500; //Radius where the Player can "grab" this, we will use this and test the radius later
		public var depositRadius: Number = 500; //Radius where the Player can "deposit" things that can be dropped only in a specific place, test and ajust later

		public var wallHit: Boolean = false; //if we want certain objects/animations to detect edges/wall collisions

		public var gravity: Number = 1;
		public var xVel: Number;
		public var yVel: Number;
		public var fric: Number = 1;
		public var speed: Number = 1;
		//basic variables we may need later if we decide to use physics in any of our animations

		public var FPS: int; //if we ever wanted to change FPS later

		private var baseHeight: Number;
		private var baseWidth: Number;
		//for setting the displayed Scene's width and height, we will multiply these by the X and Y Scales

		private var moveBoundsX: Number;
		//starting X of the Movement Area
		private var moveBoundsY: Number;
		//starting Y of the Movement Area
		private var moveBoundsEndX: Number;
		//ending X of the Movement Area
		private var moveBoundsEndY: Number;
		//starting Y of the Movement Area
		private var moveBoundsR: Number;
		//rotation of the Movement Area
		private var movementRectangle: Sprite = new Sprite();

		public var sceneCycles: int = 0; //useful for timers if we add +1 to this every frame in the Update() function
		public var colorCycles: int = 0;

		public var targetAngle: Number = 0;
		public var turnRate: int = 3;
		public var rotateX: Number;
		public var rotateY: Number;
		//basic variables that are useful if we want to program any rotation animations
		public var player: MovieClip = new Human();
		private var playerCenterW: Number = player.width / 2;
		private var playerCenterH: Number = player.height / 2;
		private var movePlayer: Boolean = false;
		private var mouseClick: Point = new Point();

		private var posNeg: Number = 0;
		//using this to determine if the player is moving left or right

		private var touchLayer: Sprite = new Sprite();

		//***ASTRID***//
		private var trashCan: MovieClip = new _trashCan();
		private var bus: MovieClip = new _bus();
		public var busTouch: Boolean = false;
		public var playerCoat: Boolean = false;
		public var coatTouch: Boolean = false;
		private var coat: MovieClip = new _coat();
		private var coatFull: MovieClip = new _coatFull();
		private var coatPickupTimer: int = 0;
		private var busDestinationX: Number = 0;
		private var busDestinationY: Number = 0;
		private var xMove: Number = 0;
		public var moveBus: Boolean = false;

		//***Maxx***//
		private var scarab: MovieClip = new _scarab();
		private var kidArt: MovieClip = new _kidArt();
		private var kidMom: MovieClip = new _kidMom();
		private var flowerGirl: MovieClip = new _flowerGirl();
		public var cactusTouch: Boolean = false;
		public var kidArtTouch: Boolean = false;
		public var daisyTouch: Boolean = false;
		public var scarabTouch: Boolean = false;
		private var cactusPickupTimer: int = 0;
		private var daisyPickupTimer: int = 0;
		private var scarabPickupTimer: int = 0;
		private var kidArtPickupTimer: int = 0;

		//Stephen
		public var posterTouch: Boolean = false;
		private var moveNewsStand: Tween;
		private var myTimer: Timer = new Timer(5000, 1);
		public static var dayNumber: int = 3;
		public static var cardTouch = false;
		public var tarot: MovieClip = new TarotCard();

		//***MADDIE***//
		public var AM: String = "AM";
		public var PM: String = "PM";
		public var AM_true: Boolean = true;
		public var clock: int = 8;
		private var officeWorkerStationary: MovieClip = new _officeWorkerStationary();
		public var clockText: TextField = new TextField();
		private var chair: MovieClip = new _chair();
		private var daisy: MovieClip = new _daisy();
		private var cactus: MovieClip = new _cactus();
		private var kidArtRotated: MovieClip = new _kidArtRotated();
		private var motivationalPosterRotated: MovieClip = new _motivationalPosterRotated();
		private var butterflyHairPinRotated: MovieClip = new _butterflyHairPin();
		public var posterInteract: Boolean = false;
		public var daisyInteract: Boolean = false;
		public var cactusInteract: Boolean = false;
		public var kidArtInteract: Boolean = false;
		public var coatInteract: Boolean = false;
		public var butterflyHairPinInteract: Boolean = false;
		public var chairTouch: Boolean = false;
		private var coatOffice: MovieClip = new _coatOffice();
		private var laptopOnly: MovieClip = new _laptopOnly();
		private var warningSign: MovieClip = new _warningSign();
		private var typingHands2: MovieClip = new _typingHands2();
		private var _worker: MovieClip = new _workerSittingNoHands();

		//***Lauren***//
		public var buttlerflyTouch: Boolean = false;
		private var butterflyPin: MovieClip = new _butterflyPin();
		public var butterflyPinPickupTimer: int = 0;

		//Drew - all arrows
		public var DownArrow: MovieClip = new downArrow();
		public var UpArrow: MovieClip = new upArrow();
		public var LeftArrow: MovieClip = new leftArrow();
		public var RightArrow: MovieClip = new rightArrow();
		public var activeArrow: MovieClip = new MovieClip();
		private var up: Boolean = false;
		private var down: Boolean = false;
		private var left: Boolean = false;
		private var right: Boolean = false;

		public var SceneButton: MovieClip = new sceneButton();

		//Drew - Number of objects interacted with
		public static var objectNum: int = 0;
		//Drew - Leaving Bedroom Var
		public static var leaveRoom: Boolean = false;
		public var activeDist: int = 250;

		private var accl: Accelerometer;
		private var acclActive: Boolean = false;
		private var avgX: Number = 0;
		private var avgY: Number = 0;
		private var avgZ: Number = 0;
		private const FACTOR: Number = 0.25;
		private var xSpeed: Number = 0;
		private var ySpeed: Number = 0;
		private const TILT: Number = 200;
		//all of these are being used by the Accelerometer

		private var sizeFactorX: Number = 1;
		private var sizeFactorY: Number = 1;

		private var activeScene: MovieClip;
		private var objectsLayer: Sprite = new Sprite();
		private var buttonsLayer: Sprite = new Sprite();
		private var activeObjectsArray: Array = new Array();
		public var daysTracker: int = 0;
		public static var wentToWork: Boolean = false;
		private var sceneEnd: Boolean = false;

		public static var roomText1: String = new String();
		public static var roomText2: String = new String();
		public static var roomText3: String = new String();
		public static var roomText4: String = new String();
		public static var buttonText: TextField = new TextField();
		private var leave: Boolean = false;
		
		public var hints: MovieClip = new Hints();
		
		public var daisyHit:Boolean = false;
		public var posterHit:Boolean = false;
		public var coatHit:Boolean = false;

		public static var NEXTDAY: Boolean = false;
		public static var endGame: Boolean = false;
		public static var playEnd: Boolean = false;
		
		public var ending: MovieClip = new EndingAnimation();

		//public var mcMask: Mask = new Mask(); //Black MovieClip the size of the stage
		//public var outerMask: Shape = new Shape(); //this object masks the areas outside the bounds of mcMask object

		public function SceneMain(player: Human) { //this function executes automatically, only once
			init();
		} //end of the SceneMain() Constructor
		public function init() {
			_MapsMCArray.push(bedroom, breakroom, busInside, busStop, cubicleOthers, cubicleYours, cubicleYours_Laptop, elevatorIn, elevatorOut, flowerShopIn, flowerShopOut, newsStand, officeHall);
			for (var i: int = 0; _MapsMCArray.length > i; i++) { //this is a textbook use of an array and a for loop being used together, study the syntax if it's new to you!
				addChildAt(_MapsMCArray[i], i); //adds the Scene at the current index in the _MapsArray as a Child of SceneMain Class
				_MapsMCArray[i].visible = false;
			}

			roomText1 = "TEXT DOWN";
			roomText2 = "TEXT UP";
			roomText3 = "TEXT LEFT";
			roomText4 = "TEXT RIGHT";
			buttonText.text = roomText1;

			this.FPS = FPS; //sets the FPS variable == whatever we initially set the FPS as
			scaleX = scaleY = 1; //we will probably change this depending on the current Scene if we want to "zoom" out or in

			baseHeight = this.height * this.scaleY;
			baseWidth = this.width * this.scaleX;
			//multiplying the Height and Width by the current X/Y Scale and using that as the new values for baseHeight and baseWidth

			_currentColor = BLACK;
			_currentScene = BED_ROOM; //Sets the initial State as the Bedroom scene

			activeScene = SceneChange();

			_currentColor.enter(this);
			_currentScene.enter(this); //executes the 'enter()' function in the current State and sends it information from the SceneMain Class

			ColorChange();
		}
		public function MergeArrays(rows: Array, collums: Array): Array {
			var newArray: Array = new Array();
			for (var i: int = 0; i < collums.length; i++) {
				newArray.insertAt([i][0], collums[i]);
				for (var j: int = 0; j < rows.length; j++) {
					newArray.insertAt([i][j + 1], rows[j]);
				}
			}
			trace("things in newArray: " + newArray);
			return newArray;
		}
		public function AddPlayer(playerX: Number, playerY: Number, boundaryStartX: Number, boundaryStartY: Number, boundaryWidth: Number, boundaryHeight: Number): void {
			moveBoundsX = boundaryStartX * sizeFactorX;
			moveBoundsEndX = (boundaryStartX + boundaryWidth) * sizeFactorX;
			moveBoundsY = boundaryStartY * sizeFactorY;
			moveBoundsEndY = (boundaryStartY + boundaryHeight) * sizeFactorY;
			//moveBoundsR = -boundaryRotationDegrees;
			PlayerBounds();
			if (player.currentFrame != 4) {
				if (playerCoat) {
					player._coat.visible = true;
					player._body.visible = false;
				} else {
					player._coat.visible = false;
					player._body.visible = true;
				}
			}
			addChildAt(objectsLayer, _MapsStateArray.length + 1);
			addChildAt(player, _MapsStateArray.length + 2);
			player.x = playerX * sizeFactorX;
			player.y = playerY * sizeFactorY;
			player.width = 233 * sizeFactorX;
			player.height = 435 * sizeFactorY;
			player.gotoAndStop(1); //Lauren - added this so I could flip the player around to the backview in the elevator
			mouseClick.x = 0;
			mouseClick.y = 0;

			SetupTouchLayer();
		}

		public function RemovePlayer(): void {
			player.width = 233;
			player.height = 435;
			xVel = 0;
			yVel = 0;
			movePlayer = false;
			//resetting player velocity
			if (!busTouch) {
				removeChild(player);
			}
			touchLayer.removeEventListener(TouchEvent.TOUCH_TAP, MovePlayer);
			removeChild(touchLayer);
			removeChild(movementRectangle);
		}

		public function NextDay(): void {
				daysTracker++;
				SetScene(BED_ROOM);
				trace(daysTracker + "!!!!!!!!!!!!!");
		}

		public function LoadBedRoom(): void {
			up = false;
			down = true;
			left = false;
			right = false;

			DownArrow.x = 200 * sizeFactorX;
			DownArrow.y = 900 * sizeFactorY;

			AddSceneButtons(up, down, left, right);
			touchLayer.addChild(hints);
			hints.x = 500;
			hints.y = 100;
		}

		public function LoadHallWay(): void {
			up = true;
			down = true;
			left = true;
			right = true;

			DownArrow.x = 1200 * sizeFactorX;
			DownArrow.y = 1160 * sizeFactorY;

			UpArrow.x = 1198 * sizeFactorX;
			UpArrow.y = 150 * sizeFactorY;

			LeftArrow.x = 750 * sizeFactorX;
			LeftArrow.y = 600 * sizeFactorY;

			RightArrow.x = 1700 * sizeFactorX;
			RightArrow.y = 600 * sizeFactorY;

			AddSceneButtons(up, down, left, right);
		}
		public function ExitHallWay(): void {
			sceneEnd = true;
			officeHall.width /= sizeFactorX;
			officeHall.height /= sizeFactorY;

			RemoveSceneButtons(up, down, left, right);
		}
		public function ExitBedRoom(): void {
			sceneEnd = true;
			touchLayer.removeChild(hints);

			RemoveSceneButtons(up, down, left, right);
		}
		private function RemoveSceneButtons(up: Boolean, down: Boolean, left: Boolean, right: Boolean): void {
			if (up) {
				UpArrow.removeEventListener(TouchEvent.TOUCH_TAP, arrowUp);
				touchLayer.removeChild(UpArrow);
			}
			if (down) {
				DownArrow.removeEventListener(TouchEvent.TOUCH_TAP, arrowDown);
				touchLayer.removeChild(DownArrow);
			}
			if (left) {
				LeftArrow.removeEventListener(TouchEvent.TOUCH_TAP, arrowLeft);
				touchLayer.removeChild(LeftArrow);
			}
			if (right) {
				RightArrow.removeEventListener(TouchEvent.TOUCH_TAP, arrowRight);
				touchLayer.removeChild(RightArrow);
			}

			SceneButton.removeEventListener(TouchEvent.TOUCH_TAP, OnLeaveScene);
			touchLayer.removeChild(SceneButton);
			touchLayer.removeChild(buttonText);
		}

		public function distToPlayer(other: MovieClip): int {
			var dist: int = Math.sqrt(Math.pow((other.x + (other.width / 2) - player.x + playerCenterW), 2) + Math.pow((other.y - (other.height / 2) - player.y + playerCenterH), 2));
			return dist;
		}

		//drew arrow events

		public function OnLeaveScene(event: TouchEvent) {
			leave = true;
			LeaveScene();
		}
		private function LeaveScene(): void {
			if (leave) {
				leave = false;
				trace("activeArrow DistanceToPlayer: " + DistanceToPlayer(activeArrow.x, activeArrow.y) + ", activeDist: " + activeDist);
				if (DistanceToPlayer(activeArrow.x, activeArrow.y) < activeDist) {
					trace("leaveRoom == true");
					leaveRoom = true;
				} else {
					leaveRoom = false;
				}
			} else { //if leave == false
				leaveRoom = false;
			} //leave == false
		}

		//drew arrow events
		public function arrowDown(event: TouchEvent) {
			activeArrow = DownArrow;
			mouseClick.x = event.stageX;
			mouseClick.y = event.stageY;
			movePlayer = true;

		}
		//drew arrow events
		public function arrowUp(event: TouchEvent) {
			activeArrow = UpArrow;
			mouseClick.x = event.stageX;
			mouseClick.y = event.stageY;
			movePlayer = true;

		}
		public function arrowLeft(event: TouchEvent) {
			activeArrow = LeftArrow;
			mouseClick.x = event.stageX;
			mouseClick.y = event.stageY;
			movePlayer = true;

		}
		public function arrowRight(event: TouchEvent) {
			activeArrow = RightArrow;
			mouseClick.x = event.stageX;
			mouseClick.y = event.stageY;
			movePlayer = true;
		}

		//STEPHEN
		public function LoadCubicleOthers(): void {
			cubicleOthers.x = 0;
			cubicleOthers.y = 0;

			up = false;
			down = true;
			left = false;
			right = false;

			DownArrow.x = 645 * sizeFactorX;
			DownArrow.y = 700 * sizeFactorY;

			AddSceneButtons(up, down, left, right);

			if (Accelerometer.isSupported) {
				//checking to see if the Accelerometer is supported on this device before loading it
				//LoadAccelerometer();
			}
			if (!posterTouch) {
				activeObjectsArray.push(motivationalPosterRotated);
				motivationalPosterRotated.width *= sizeFactorX;
				motivationalPosterRotated.height *= sizeFactorY;
				//trace("adding child");
			}
			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop adds everything in the activeObjectsArray to the objectsLayer
				objectsLayer.addChild(activeObjectsArray[i]);
			}
		}

		//STEPHEN
		public function RemoveCubicleOthers(): void {
			sceneEnd = true;

			cubicleOthers.width = 2776;
			cubicleOthers.height = 1440;
			cubicleOthers.x = 0;
			cubicleOthers.y = 0;

			RemoveSceneButtons(up, down, left, right);

			if (!posterTouch) {
				activeObjectsArray.splice(motivationalPosterRotated);
				motivationalPosterRotated.width /= sizeFactorX;
				motivationalPosterRotated.height /= sizeFactorY;
				objectsLayer.removeChild(motivationalPosterRotated);
			}

			if (Accelerometer.isSupported) { ////checking to see if the Accelerometer is supported on this device before unloading it
				//RemoveAccelerometer();
			}
		}

		//STEPHEN
		public function StartLoadNewsStand(): void {
			newsStand.x = 0;

			player.visible = false;

			//if (dayNumber == 2 && !cardTouch) {
			activeObjectsArray.push(tarot);
			tarot.width *= sizeFactorX / 2;
			tarot.height *= sizeFactorY;
			tarot.x = 5000 * sizeFactorX;
			tarot.y = 200 * sizeFactorY;
			//}
			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop adds everything in the activeObjectsArray to the objectsLayer
				objectsLayer.addChild(activeObjectsArray[i]);
			}

			if (_previousScene == ELEVATOR_OUT) {
				newsStand.y = 0;
				moveNewsStand = new Tween(newsStand, "y", None.easeNone, newsStand.y, -newsStand.height / 2, 5, true);
				if (dayNumber == 2 && !cardTouch) {
					var moveCard: Tween = new Tween(tarot, "y", None.easeNone,
						newsStand.y - (newsStand.height / 6), -newsStand.height / 2, 5, true);
				}
				myTimer.start();
				myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, EnterTimerHandler);
			} else if (_previousScene == FLOWER_SHOP_OUT) {
				newsStand.y = -newsStand.height / 2;
				FinishLoadNewsStand();
			}
			//DONT USE ACCELEROMETER ON THIS SCENE
			// it made it so I could pull the mc up past the stage beyond 200 px

		}

		public function FinishLoadNewsStand(): void {
			if (_previousScene == ELEVATOR_OUT) {
				player.x = 720 * sizeFactorX;
				player.y = 150 * sizeFactorY;
			} else if (_previousScene == FLOWER_SHOP_OUT) {
				player.x = 100 * sizeFactorX;
				player.y = 500 * sizeFactorY;
			}

			player.height = player.y / 1.5;
			player.width = player.y / 3;

			up = true;
			down = false;
			left = true;
			right = false;

			UpArrow.x = 720 * sizeFactorX;
			UpArrow.y = 150 * sizeFactorY;

			LeftArrow.x = 100 * sizeFactorX;
			LeftArrow.y = 650 * sizeFactorY;
			RemovePlayer();
			AddPlayer(221.95, 900, 0, 1000, 2776, 1440);

			AddSceneButtons(up, down, left, right);
			player.visible = true;
		}

		//STEPHEN
		public function RemoveNewsStand(): void {
			sceneEnd = true;

			newsStand.width = 1440;
			newsStand.height = 2776;
			newsStand.x = 0;
			newsStand.y = 0;

			RemoveSceneButtons(up, down, left, right);

			tarot.x = 0;
			tarot.y = 0;
			tarot.height = 96;
			tarot.width = 76;

			activeObjectsArray.splice(0, activeObjectsArray.length);
			objectsLayer.removeChildren();
			//removeChild(objectsLayer);
		}

		//STEPHEN
		public function EnterOfficeBuilding(): void {

			if (!cardTouch) {
				tarot.x = -500 * sizeFactorX;
			}
			player.x = -500 * sizeFactorX;
			myTimer.reset();
			myTimer.start();
			var upBuilding: Tween = new Tween(newsStand, "y", None.easeNone, newsStand.y, 0, 5, true);
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, ExitTimerHandler);
		}

		//Stephen
		public function EnterTimerHandler(evt: TimerEvent): void {
			FinishLoadNewsStand();
			myTimer.removeEventListener(TimerEvent.TIMER_COMPLETE, EnterTimerHandler);
		}

		//Stephen
		private function ExitTimerHandler(evt: TimerEvent): void {
			myTimer.removeEventListener(TimerEvent.TIMER_COMPLETE, ExitTimerHandler);
			SetScene(ELEVATOR_OUT);
		}

		//Lauren 
		public function LoadElevatorOut(): void {
			up = false;
			down = false;
			left = true;
			right = true;

			LeftArrow.x = 50 * sizeFactorX;
			LeftArrow.y = 1050 * sizeFactorY;

			RightArrow.x = 930 * sizeFactorX;
			RightArrow.y = 1050 * sizeFactorY;

			elevatorOut.x = 0;
			elevatorOut.y = 0;

			if (Accelerometer.isSupported) {
				//checking to see if the Accelerometer is supported on this device before loading it
				//LoadAccelerometer();
			}
			AddSceneButtons(up, down, left, right);
		}
		private function AddSceneButtons(up: Boolean, down: Boolean, left: Boolean, right: Boolean): void {
			if (left) {
				LeftArrow.width = 40 * sizeFactorX;
				LeftArrow.height = 80 * sizeFactorY;
				touchLayer.addChild(LeftArrow);
				LeftArrow.addEventListener(TouchEvent.TOUCH_TAP, arrowLeft);
			}
			if (right) {
				RightArrow.width = 40 * sizeFactorX;
				RightArrow.height = 80 * sizeFactorY;
				touchLayer.addChild(RightArrow);
				RightArrow.addEventListener(TouchEvent.TOUCH_TAP, arrowRight);
			}
			if (up) {
				UpArrow.width = 80 * sizeFactorX;
				UpArrow.height = 40 * sizeFactorY;
				touchLayer.addChild(UpArrow);
				UpArrow.addEventListener(TouchEvent.TOUCH_TAP, arrowUp);
			}
			if (down) {
				DownArrow.width = 80 * sizeFactorX;
				DownArrow.height = 40 * sizeFactorY;
				touchLayer.addChild(DownArrow);
				DownArrow.addEventListener(TouchEvent.TOUCH_TAP, arrowDown);
			}

			SceneButton.x = 1350 * sizeFactorX;
			SceneButton.y = 800 * sizeFactorY;
			touchLayer.addChild(SceneButton);
			touchLayer.addChild(buttonText);
			SceneButton.addEventListener(TouchEvent.TOUCH_TAP, OnLeaveScene);
		}

		//Lauren 
		public function RemoveElevatorOut(): void {
			sceneEnd = true;

			elevatorOut.x = 0;
			elevatorOut.y = 0;
			elevatorOut.width = 2776;
			elevatorOut.height = 1440;
			//setting the x, y, width, and height of the busStop MovieClip back to their values before they were scaled

			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop removes everything in the activeObjectsArray using the purgeObject method
				purgeObject(activeObjectsArray[i]);
			}

			RemoveSceneButtons(up, down, left, right);

			//removeChild(objectsLayer);
			//remove the objectsLayer

			if (Accelerometer.isSupported) { ////checking to see if the Accelerometer is supported on this device before unloading it
				//RemoveAccelerometer();
			}
		}

		//Lauren 
		public function LoadElevatorIn(): void {
			if (Accelerometer.isSupported) {
				//checking to see if the Accelerometer is supported on this device before loading it
				//LoadAccelerometer();
			}
			elevatorIn.x = 0;
			elevatorIn.y = 0;
		}


		//Lauren 
		public function RemoveElevatorIn(): void {
			sceneEnd = true;
			elevatorIn.x = 0;
			elevatorIn.y = 0;
			elevatorIn.width = 2776;
			elevatorIn.height = 1440;
			//setting the x, y, width, and height of the busStop MovieClip back to their values before they were scaled

			if (Accelerometer.isSupported) { ////checking to see if the Accelerometer is supported on this device before unloading it
				//RemoveAccelerometer();
			}
		}


		//Lauren 
		public function LoadBreakroom(): void {
			trace("player.width in LoadBreakroom(): " + player.width);
			player.width = 233 * 2 * sizeFactorX;
			trace("player.width after LoadBreakroom(): " + player.width);
			player.height = 435 * 2 * sizeFactorY;
			if (daysTracker == 3) {
				activeObjectsArray.push(butterflyPin);
				butterflyPin.x = 2000 * sizeFactorX;
				butterflyPin.y = 848 * sizeFactorY;
				butterflyPin.width = 168 * sizeFactorX;
				butterflyPin.height = 168 * sizeFactorY;
				butterflyPin.rotation = 320;
			} //for some reason the daystracker is causing a sizing error
			if (Accelerometer.isSupported) {
				//checking to see if the Accelerometer is supported on this device before loading it
				//LoadAccelerometer();
			}
			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop adds everything in the activeObjectsArray to the objectsLayer
				objectsLayer.addChild(activeObjectsArray[i]);
			}

		}

		//Lauren
		public function RemoveBreakroom(): void {
			sceneEnd = true;
			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop adds everything in the activeObjectsArray to the objectsLayer
				purgeObject(activeObjectsArray[i]);
			}
			if (Accelerometer.isSupported) { ////checking to see if the Accelerometer is supported on this device before unloading it
				//RemoveAccelerometer();
			}
			//removeChild(objectsLayer);
		}

		//-Maxx
		public function LoadFlowerShopIn(): void {
			up = false;
			down = false;
			left = false;
			right = true;


			RightArrow.x = 930 * sizeFactorX;
			RightArrow.y = 750 * sizeFactorY;

			AddSceneButtons(up, down, left, right);

			if (Accelerometer.isSupported) {
				//checking to see if the Accelerometer is supported on this device before loading it
				//LoadAccelerometer();
			}
			//putting all of the Interactive Objects in this Scene into the activeObjectsArray
			activeObjectsArray.push(flowerGirl);
			flowerGirl.x = 1456 * sizeFactorX;
			flowerGirl.y = 544 * sizeFactorY;
			flowerGirl.width *= sizeFactorX;
			flowerGirl.height *= sizeFactorY;
			//setting trashCan x, y, width, and height, to scale with the stage in the scene
			if (daysTracker == 2) { //checking to make sure we're not in one of the first two days
				activeObjectsArray.push(daisy);
				//adding the coat to the activeObjectsArray

				daisy.x = 1100 * sizeFactorX;
				daisy.y = 760 * sizeFactorY
				daisy.width *= sizeFactorX * 1.5;
				daisy.height *= sizeFactorY * 1.5;
				//setting the starting x and y to scale with the stage
			}
			if (daysTracker == 5) {
				activeObjectsArray.push(cactus);
				//adding the coat to the activeObjectsArray

				cactus.x = 1100 * sizeFactorX;
				cactus.y = 760 * sizeFactorY;
				cactus.width *= sizeFactorX * 1.5;
				cactus.height *= sizeFactorY * 1.5;
			}

			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop adds everything in the activeObjectsArray to the objectsLayer
				objectsLayer.addChild(activeObjectsArray[i]);
			}


		}

		//-Maxx
		public function RemoveFlowerShopIn(): void {
			sceneEnd = true;

			RemoveSceneButtons(up, down, left, right);

			flowerGirl.width /= sizeFactorX;
			flowerGirl.height /= sizeFactorY;
			if (daysTracker == 2) {
				daisy.width /= sizeFactorX * 1.5;
				daisy.height /= sizeFactorY * 1.5;
			}
			if (daysTracker == 5) {
				cactus.width /= sizeFactorX * 1.5;
				cactus.height /= sizeFactorY * 1.5;
			}
			flowerShopIn.x = 0;
			flowerShopIn.y = 0;
			flowerShopIn.width = 2776;
			flowerShopIn.height = 1440;

			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop removes everything in the activeObjectsArray using the purgeObject method
				purgeObject(activeObjectsArray[i]);
			}

			//removeChild(objectsLayer);
			//remove the objectsLayer

			if (Accelerometer.isSupported) { ////checking to see if the Accelerometer is supported on this device before unloading it
				//RemoveAccelerometer();
			}
		}

		//-Max
		public function LoadFlowerShopOut(): void {
			up = true;
			down = false;
			left = true;
			right = true;

			UpArrow.x = 700 * sizeFactorX;
			UpArrow.y = 400 * sizeFactorY;


			LeftArrow.x = 450 * sizeFactorX;
			LeftArrow.y = 750 * sizeFactorY;

			RightArrow.x = 930 * sizeFactorX;
			RightArrow.y = 750 * sizeFactorY;

			AddSceneButtons(up, down, left, right);

			if (Accelerometer.isSupported) {
				//checking to see if the Accelerometer is supported on this device before loading it
				//LoadAccelerometer();
			}
			//setting the scaling factor of things in this Scene based on how we're going to scale the size of the busStop MovieClip

			activeObjectsArray.push(kidMom);
			//putting all of the Interactive Objects in this Scene into the activeObjectsArray

			kidMom.x = 1456 * sizeFactorX;
			kidMom.y = 544 * sizeFactorY;
			kidMom.width *= sizeFactorX;
			kidMom.height *= sizeFactorY;
			//setting trashCan x, y, width, and height, to scale with the stage in the scene

			if (daysTracker > 3) { //checking to make sure we're not in one of the first two days
				if (scarabTouch && daysTracker == 5) {
					activeObjectsArray.push(kidArt);
					//adding the KidArt to the activeObjectsArray
					kidArt.x = 1100 * sizeFactorX;
					kidArt.y = 760 * sizeFactorY;
					kidArt.width *= sizeFactorX * 1.5;
					kidArt.height *= sizeFactorY * 1.5;
					//setting the starting x and y to scale with the stage
				}
				if (cardTouch && !scarabTouch) {
					activeObjectsArray.push(scarab);

					scarab.x = 1100 * sizeFactorX;
					scarab.y = 760 * sizeFactorY;
					scarab.width *= sizeFactorX * 1.5;
					scarab.height *= sizeFactorY * 1.5;
				}
			}

			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop adds everything in the activeObjectsArray to the objectsLayer
				objectsLayer.addChild(activeObjectsArray[i]);
			}
		}


		//-Max
		public function RemoveFlowerShopOut(): void {
			sceneEnd = true;

			RemoveSceneButtons(up, down, left, right);

			flowerShopOut.x = 0;
			flowerShopOut.y = 0;
			flowerShopOut.width = 2776;
			flowerShopOut.height = 1440;
			//setting the x, y, width, and height of the FlowerShop MovieClip back to their values before they were scaled

			if (daysTracker > 3) { //checking to make sure we're not in one of the first two days
				if (scarabTouch && daysTracker == 5) {
					kidArt.width /= sizeFactorX * 1.5;
					kidArt.height /= sizeFactorY * 1.5;
				}
				if (cardTouch && scarabTouch) {
					scarab.width /= sizeFactorX * 1.5;
					scarab.height /= sizeFactorY * 1.5;
				}
			}

			kidMom.width /= sizeFactorX;
			kidMom.height /= sizeFactorY;
			//undoing the kidMom scaling
			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop removes everything in the activeObjectsArray using the purgeObject method
				purgeObject(activeObjectsArray[i]);
			}

			//removeChild(objectsLayer);
			//remove the objectsLayer

			if (Accelerometer.isSupported) { ////checking to see if the Accelerometer is supported on this device before unloading it
				//RemoveAccelerometer();
			}
		}

		public function LoadBusInside(): void {
			if (Accelerometer.isSupported) {
				//checking to see if the Accelerometer is supported on this device before loading it
				//LoadAccelerometer();
			}
			//adding the coat to the activeObjectsArray

			addChild(officeWorkerStationary);

			officeWorkerStationary.x = 1500 * sizeFactorX;
			officeWorkerStationary.y = 400 * sizeFactorY;
			officeWorkerStationary.width *= sizeFactorX;
			officeWorkerStationary.height *= sizeFactorY;
			//setting the starting x and y to scale with the stage
		}

		public function RemoveBusInside(): void {
			sceneEnd = true;
			busInside.x = 0;
			busInside.y = 0;
			busInside.width = 2776;
			busInside.height = 1440;
			//setting the x, y, width, and height of the busStop MovieClip back to their values before they were scaled

			officeWorkerStationary.width /= sizeFactorX;
			officeWorkerStationary.height /= sizeFactorY;

			if (Accelerometer.isSupported) { ////checking to see if the Accelerometer is supported on this device before unloading it
				//RemoveAccelerometer();
			}
			removeChild(officeWorkerStationary);
		}

		private function RemoveObjectsLayer(): void {
			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop removes everything in the activeObjectsArray using the purgeObject method
				purgeObject(activeObjectsArray[i]);
			}
			removeChild(objectsLayer);
			//remove the objectsLayer
		}

		public function LoadBusStop(): void {
			up = false;
			down = true;
			left = false;
			right = true;

			RightArrow.x = 2300 * sizeFactorX;
			RightArrow.y = 1050 * sizeFactorY;

			DownArrow.x = 200 * sizeFactorX;
			DownArrow.y = 1300 * sizeFactorY;

			AddSceneButtons(up, down, left, right);
			//the objectsLayer is the layer where we will add all Interactive Objects
			if (Accelerometer.isSupported) {
				//checking to see if the Accelerometer is supported on this device before loading it
				//LoadAccelerometer();
			}

			activeObjectsArray.push(bus, trashCan);
			//putting all of the Interactive Objects in this Scene into the activeObjectsArray

			trashCan.x = 1456 * sizeFactorX;
			trashCan.y = 544 * sizeFactorY;
			trashCan.width *= sizeFactorX;
			trashCan.height *= sizeFactorY;
			//setting trashCan x, y, width, and height, to scale with the stage in the scene

			bus.x = 2800 * sizeFactorX;
			bus.y = 500 * sizeFactorY;
			bus.width *= sizeFactorX;
			bus.height *= sizeFactorY;
			busDestinationX = (busStop.x * sizeFactorX) - (bus.width * sizeFactorY);
			busDestinationY = 500 * sizeFactorY;

			if (daysTracker == 4) {
				activeObjectsArray.push(coat);
				//adding the coat to the activeObjectsArray
				coat.x = 1100 * sizeFactorX;
				coat.y = 760 * sizeFactorY;
				coat.width *= sizeFactorX * 1.5;
				coat.height *= sizeFactorY * 1.5;
				//setting the starting x and y to scale with the stage
			}

			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop adds everything in the activeObjectsArray to the objectsLayer
				if (activeObjectsArray[i] == bus) {
					addChild(activeObjectsArray[i]);
				} else {
					objectsLayer.addChild(activeObjectsArray[i]);
				}
			}

			UpdateTrashCan();
			UpdateBus();
		}
		public function RemoveBusStop(): void {
			sceneEnd = true;
			RemoveSceneButtons(up, down, left, right);

			busStop.x = 0;
			busStop.y = 0;
			busStop.width = 2776;
			busStop.height = 1440;
			//setting the x, y, width, and height of the busStop MovieClip back to their values before they were scaled

			trashCan.width /= sizeFactorX;
			trashCan.height /= sizeFactorY;
			//undoing the trashCan scaling

			bus.width /= sizeFactorX;
			bus.height /= sizeFactorY;
			if (daysTracker == 4) {
				coat.width /= sizeFactorX * 1.5;
				coat.height /= sizeFactorY * 1.5;
			}

			RemoveObjectsLayer();

			if (Accelerometer.isSupported) { ////checking to see if the Accelerometer is supported on this device before unloading it
				//RemoveAccelerometer();
			}
		}


		public function LoadCubicleYours(): void {
			up = false;
			down = true;
			left = false;
			right = false;

			_worker.visible = false;
			typingHands2.visible = false;

			DownArrow.x = 200 * sizeFactorX;
			DownArrow.y = 1300 * sizeFactorY;

			AddSceneButtons(up, down, left, right);

			if (Accelerometer.isSupported) {
				//checking to see if the Accelerometer is supported on this device before loading it
				//LoadAccelerometer();
			}

			//if (coatInteract == true) { //THIS NEEDS TO BE ADJUSTED!!!!!!! 4/1/19
			activeObjectsArray.push(warningSign);
			//adding the warning sign to the activeObjectsArray

			warningSign.x = 900 * sizeFactorX;
			warningSign.y = 300 * sizeFactorY;
			warningSign.width *= sizeFactorX;
			warningSign.height *= sizeFactorY;
			//setting the starting x and y to scale with the stage

			//}			

			//if (coatInteract == true) { //checking to make sure the cactus has been interacted with
			activeObjectsArray.push(coatOffice);
			//adding the coat to the activeObjectsArray

			coatOffice.x = 400 * sizeFactorX;
			coatOffice.y = 400 * sizeFactorY;
			coatOffice.width *= sizeFactorX;
			coatOffice.height *= sizeFactorY;
			//setting the starting x and y to scale with the stage

			//}


			//if (kidArtInteract == true) { //checking to make sure the butterfly pin has been interacted with
			activeObjectsArray.push(kidArtRotated);
			//adding the coat to the activeObjectsArray

			kidArtRotated.x = 0;
			kidArtRotated.y = 0;
			kidArtRotated.width *= sizeFactorX;
			kidArtRotated.height *= sizeFactorY;
			//setting the starting x and y to scale with the stage
			//}

			if (daisyHit == true) { //checking to make sure the daisy has been interacted with
				activeObjectsArray.push(daisy);
			//adding the coat to the activeObjectsArray

				daisy.x = 962 * sizeFactorX;
				daisy.y = 298 * sizeFactorY;
				daisy.width *= sizeFactorX;
				daisy.height *= sizeFactorY;
			}
			//setting the starting x and y to scale with the stage

			//}

			if (posterHit == true) { //checking to make sure the motivational poster has been interacted yet
				activeObjectsArray.push(motivationalPosterRotated);
			//adding the coat to the activeObjectsArray

				motivationalPosterRotated.x = 0;
				motivationalPosterRotated.y = 0;
				motivationalPosterRotated.width *= sizeFactorX;
				motivationalPosterRotated.height *= sizeFactorY;
			}
			//setting the starting x and y to scale with the stage

			//}

			activeObjectsArray.push(laptopOnly);
			//adding the laptop to the activeObjectsArray

			laptopOnly.x = 800 * sizeFactorX;
			laptopOnly.y = 250 * sizeFactorY;
			laptopOnly.width *= sizeFactorX;
			laptopOnly.height *= sizeFactorY;
			//setting the starting x and y to scale with the stage

			//adding the coat to the activeObjectsArray
			activeObjectsArray.push(typingHands2);
			typingHands2.x = 815 * sizeFactorX;
			typingHands2.y = 324 * sizeFactorY;
			typingHands2.width *= sizeFactorX;
			typingHands2.height *= sizeFactorY;
			//setting the starting x and y to scale with the stage
			activeObjectsArray.push(_worker);
			_worker.x = 768.90 * sizeFactorX;
			_worker.y = 64.45 * sizeFactorY;
			_worker.width *= sizeFactorX;
			_worker.height *= sizeFactorY;

			activeObjectsArray.push(chair);
			//putting all of the Interactive Objects in this Scene into the activeObjectsArray

			chair.x = 800 * sizeFactorX;
			chair.y = 250 * sizeFactorY;
			chair.width *= sizeFactorX;
			chair.height *= sizeFactorY;
			//setting trashCan x, y, width, and height, to scale with the stage in the scene

			//if (objectNum > 3) { // This will have warningSign appear when 3+ objects show up
			activeObjectsArray.push(warningSign);
			//adding the warning sign to the activeObjectsArray

			warningSign.x = 260 * sizeFactorX;
			warningSign.y = 300 * sizeFactorY;
			warningSign.width *= sizeFactorX;
			warningSign.height *= sizeFactorY;
			//setting the starting x and y to scale with the stage

			//}		

			//if (cactusInteract == true) { //checking to make sure the cactus has been interacted with
			activeObjectsArray.push(cactus);
			//adding the coat to the activeObjectsArray

			cactus.x = 700 * sizeFactorX;
			cactus.y = 310 * sizeFactorY;
			cactus.width *= sizeFactorX;
			cactus.height *= sizeFactorY;
			//setting the starting x and y to scale with the stage

			//}

			//if (butterflyHairPinInteract == true) { //checking to make sure the butterfly pin has been interacted with
			activeObjectsArray.push(butterflyHairPinRotated);
			//adding the coat to the activeObjectsArray

			butterflyHairPinRotated.x = 500 * sizeFactorX;
			butterflyHairPinRotated.y = 140 * sizeFactorY;
			butterflyHairPinRotated.width *= sizeFactorX;
			butterflyHairPinRotated.height *= sizeFactorY;
			//setting the starting x and y to scale with the stage
			//}
			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop adds everything in the activeObjectsArray to the objectsLayer
				objectsLayer.addChild(activeObjectsArray[i]);
			}
			trace("activeObjectsArray in CubicleYours(): " + activeObjectsArray);

		}

		public function RemoveCubicleYours(): void {
			sceneEnd = true;

			RemoveSceneButtons(up, down, left, right);

			cubicleYours.x = 0;
			cubicleYours.y = 0;
			cubicleYours.width = 1456;
			cubicleYours.height = 897;
			//setting the x, y, width, and height of the busStop MovieClip back to their values before they were scaled

			kidArtRotated.width /= sizeFactorX;
			kidArtRotated.height /= sizeFactorY;
			daisy.width /= sizeFactorX;
			daisy.height /= sizeFactorY;
			chair.width /= sizeFactorX;
			chair.height /= sizeFactorY;
			motivationalPosterRotated.width /= sizeFactorX;
			motivationalPosterRotated.height /= sizeFactorY;
			cactus.width /= sizeFactorX;
			cactus.height /= sizeFactorY;
			butterflyHairPinRotated.width /= sizeFactorX;
			butterflyHairPinRotated.height /= sizeFactorY;
			coatOffice.width /= sizeFactorX;
			coatOffice.height /= sizeFactorY;
			laptopOnly.width /= sizeFactorX;
			laptopOnly.height /= sizeFactorY;
			warningSign.width /= sizeFactorX;
			warningSign.height /= sizeFactorY;
			typingHands2.width /= sizeFactorX;
			typingHands2.height /= sizeFactorY;
			_worker.width /= sizeFactorX;
			_worker.height /= sizeFactorY;

			if (Accelerometer.isSupported) { ////checking to see if the Accelerometer is supported on this device before unloading it
				//RemoveAccelerometer();
			}
			if (chairTouch) {
				chairTouch = false;
				activeObjectsArray.splice(_worker);
				activeObjectsArray.splice(typingHands2);
				objectsLayer.removeChild(_worker);
				objectsLayer.removeChild(typingHands2);
			}

			activeObjectsArray.splice(0, activeObjectsArray.length);
			objectsLayer.removeChildren();
			//remove the objectsLayer
			trace("activeObjectsArray after leaving CubicleYours(): " + activeObjectsArray);
			trace("objectsLayer's number of children after leaving CubicleYours(): " + objectsLayer.numChildren);
		}

		public function LoadCubicleYours_Laptop(): void {
			var format: TextFormat = new TextFormat();
			format.font = "Verdana";
			format.color = 0xFF000000;
			format.size = 30;
			clockText.autoSize = TextFieldAutoSize.RIGHT;
			clockText.defaultTextFormat = format;
			clockText.x = 1700 * sizeFactorX;
			clockText.y = 750 * sizeFactorY;
			clockText.scaleX = sizeFactorX;
			clockText.scaleY = sizeFactorY;

			addChild(clockText);
			//the objectsLayer is the layer where we will add all Interactive Objects
			if (Accelerometer.isSupported) {
				//checking to see if the Accelerometer is supported on this device before loading it
				//LoadAccelerometer();
			}
		}

		public function RemoveCubicleYours_Laptop(): void {
			sceneEnd = true;
			cubicleYours_Laptop.x = 0;
			cubicleYours_Laptop.y = 0;
			cubicleYours_Laptop.width = 1008;
			cubicleYours_Laptop.height = 864;
			//setting the x, y, width, and height of the busStop MovieClip back to their values before they were scaled
			for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop removes everything in the activeObjectsArray using the purgeObject method
				trace("CUBICLEYOURS_LAPTOP WHAT IS IN ACTIVEOBJECTSARRAY? " + activeObjectsArray);
				purgeObject(activeObjectsArray[i]);
			}
			AM_true = true;
			removeChild(clockText);
		}

		private function UpdateAccelerometer(event: AccelerometerEvent): void {
			AccelerometerRollingAvg(event);
			xSpeed -= avgX;
			ySpeed += avgY;
		}
		private function AccelerometerRollingAvg(event: AccelerometerEvent): void {
			avgX = (event.accelerationX * FACTOR) + (avgX * (1 - FACTOR));
			avgY = (event.accelerationY * FACTOR) + (avgY * (1 - FACTOR));
			avgZ = (event.accelerationZ * FACTOR) + (avgZ * (1 - FACTOR));
		}

		private function LoadAccelerometer(): void {
			accl = new Accelerometer();
			accl.setRequestedUpdateInterval(100);
			accl.addEventListener(AccelerometerEvent.UPDATE, UpdateAccelerometer);
			acclActive = true;
		}
		private function RemoveAccelerometer(): void {
			accl.removeEventListener(AccelerometerEvent.UPDATE, UpdateAccelerometer);
			acclActive = false;
			xSpeed = 0;
			ySpeed = 0;
		}

		private function SetupTouchLayer(): void {
			Multitouch.inputMode = MultitouchInputMode.TOUCH_POINT;

			for (var i: int = 0; _MapsStateArray.length > i; i++) {
				if (_MapsStateArray[i] == _currentScene) {

					addChildAt(touchLayer, _MapsMCArray.length + 3);

					touchLayer.graphics.beginFill(0x000000, 0.001);
					touchLayer.graphics.drawRect(0, 0, _MapsMCArray[i].width, _MapsMCArray[i].height);
					touchLayer.graphics.endFill();

					touchLayer.addEventListener(TouchEvent.TOUCH_TAP, MovePlayer);
				}
			}
		}

		private function RotateAroundCenter(object: Sprite, angleDegrees: Number): void {
			if (object.rotation == angleDegrees) {
				return;
			}

			var matrix: Matrix = object.transform.matrix;
			var rect: Rectangle = object.getBounds(object.parent);

			matrix.translate(-(rect.left + (rect.width / 2)), -(rect.top + (rect.height / 2)));
			matrix.rotate((angleDegrees / 180) * Math.PI);
			matrix.translate(rect.left + (rect.width / 2), rect.top + (rect.height / 2));
			object.transform.matrix = matrix;

			object.rotation = Math.round(object.rotation);
		}

		private function PlayerBounds(): void {
			if (movementRectangle.graphics != null) {
				movementRectangle.graphics.clear();
			}
			movementRectangle.graphics.beginFill(0xCCCCCC, 0.3);
			//choose colour for fill (black), and alpha value
			movementRectangle.graphics.drawRect(moveBoundsX, moveBoundsY, moveBoundsEndX, moveBoundsEndY);
			//draw shape
			movementRectangle.graphics.endFill();
			//end fill
			//RotateAroundCenter(movementRectangle, moveBoundsR);
			//set rotation value
			addChild(movementRectangle);
			//add "rectangle" to stage
		}

		private function MovePlayer(event: TouchEvent) {
			trace("moving player");

			mouseClick.x = event.stageX;
			mouseClick.y = event.stageY;
			//setting new values for mouseClick.x and mouseClick.y based on where the TouchEvent occured

			movePlayer = true;
			//allows the Update() function to start moving the player

		}
		private function UpdatePlayerLocation(): void {
			//trace("player.width: " + player.width + ", player.height: " + player.height);
			//trace("player.x: " + player.x + ", player.y: " + player.y);
			//trace("activeArrow.x: " + activeArrow.x + ", activeArrow.y: " + activeArrow.y);

			var dx: Number = player.x + playerCenterW - mouseClick.x; //dx is just the 'difference' between the object you want to rotate and the 'player' current location.x
			//get adjacent length
			var dy: Number = player.y + playerCenterH - mouseClick.y; //dy is the 'difference' on the location.y
			//get opposite length
			var rad: Number = Math.atan2(dy, dx);
			//get hypotenuse length
			var powerOfMovement: Number = DistanceToPlayer(mouseClick.x, mouseClick.y);
			speed = powerOfMovement / 10;
			//set speed of the player based on distance from tap event

			xVel = Math.cos(rad);
			yVel = Math.sin(rad);
			//set the x and y velocities of the player

			xVel *= fric;
			yVel *= fric;
			//useful if we want to artificially slow down the player or speed them up depending on which scene is active, set a lower fric value (between 1 and 0) when the scene loads to slow movement

			if (mouseClick.x < movementRectangle.x) {
				xVel *= 0.5;
				player.x -= xVel * speed;
			} else if (mouseClick.x > movementRectangle.x + movementRectangle.width) {
				xVel *= 0.5;
				player.x -= xVel * speed;
			} else {
				player.x -= xVel * speed;
			}

			if (mouseClick.y < movementRectangle.y - movementRectangle.height) {
				yVel *= 0.5;
				player.y -= yVel * speed;
			} else if (mouseClick.y > movementRectangle.y) {
				yVel *= 0.5;
				player.y -= yVel * speed;
			} else {
				player.y -= yVel * speed;
			}

			if (speed < 4) {
				speed = 4;
				if (powerOfMovement / 10 < 2) {
					trace("stop movement");
					movePlayer = false;
				}
			}

			if (coatTouch) {
				coatFull.x = player.x + playerCenterW / 2;
				coatFull.y = player.y - playerCenterH / 2;
			}
			CollisionDetection();
		}

		private function CollisionDetection(): void {
			for (var object: int = 0; object < activeObjectsArray.length; object++) {
				if (player.hitTestObject(activeObjectsArray[object])) {

					if (CurrentScene == BREAK_ROOM) {
						if (activeObjectsArray[object].name == butterflyPin.name) {
							if (!buttlerflyTouch) {
								buttlerflyTouch = true;
								purgeObject(activeObjectsArray[object]);
								player.gotoAndStop(3);
								objectNum++;
							}
						}
					} else if (CurrentScene == CUBICLE_OTHERS) { //STEPHEN
						if (activeObjectsArray[object].name == motivationalPosterRotated.name) {
							posterHit = true;
							posterTouch = true;
							objectNum++;
							purgeObject(activeObjectsArray[object]);
						}
					} else if (CurrentScene == NEWS_STAND) { //STEPHEN
						cardTouch = true;
						objectNum++;
						purgeObject(activeObjectsArray[object]);
					} else if (CurrentScene == BUS_STOP) {
						if (activeObjectsArray[object].name == coat.name) {
							if (!coatTouch) {
								coatTouch = true;
								coatFull.x = player.x + playerCenterW / 2;
								coatFull.y = player.y - playerCenterH / 2;
								addChild(coatFull);
								playerCoat = true;
								purgeObject(activeObjectsArray[object]);
								objectNum++;
							}
						} //if coat
						else if (activeObjectsArray[object].name == bus.name) {
							trace("bus COLLISIONDETECTED");
							busTouch = true;
							removeChild(player);
						} else if (activeObjectsArray[object].name != trashCan.name) {
							purgeObject(activeObjectsArray[object]);
						}
					} //if BUS_STOP
					else if (CurrentScene == CUBICLE_YOURS) {
						if (activeObjectsArray[object].name == chair.name) {
							chairTouch = true;
							purgeObject(chair);
							_worker.visible = true;
							typingHands2.visible = true;
							RemovePlayer();
						}
					} //end CUBICLE_YOURS
					else if (CurrentScene == FLOWER_SHOP_IN || FLOWER_SHOP_OUT) {
						var times:int = 0;
						if (activeObjectsArray[object].name != flowerGirl.name && activeObjectsArray[object].name != kidMom.name) {
							purgeObject(activeObjectsArray[object]);
							times++;
							if(times == 1)
							{
								daisyHit = true;
								objectNum++;
							}
							if(times == 2)
							{
								objectNum++;
							}
						}
					} //end FLOWER_SHOP_IN && FLOWER_SHOP_OUT
					else { //**DEFAULT BEHAVIOR: PURGE ALL THE OBJECTS IN THE activeObjectsArray***
						purgeObject(activeObjectsArray[object]);
					} //**DEFAULT BEHAVIOR: PURGE ALL THE OBJECTS IN THE activeObjectsArray***
				}
			} //end for activeObjectsArray
		} //end CollisionDetection

		public function ResetDefaultPlayer(): void {
			player.gotoAndStop(1);
		}
		private function MoveActiveScene(objects: Array): void {

			var newX: Number = activeScene.x + xSpeed;
			var newY: Number = activeScene.y + ySpeed;

			if (newX < -TILT) {
				activeScene.x = -TILT;
				xSpeed = 0;
			} else if (newX > TILT) {
				activeScene.x = TILT;
				xSpeed = 0;
			} else {
				activeScene.x += xSpeed;
				player.x += xSpeed;
				movementRectangle.x += xSpeed;
				for (var i: int = 0; objects.length > i; i++) {
					objects[i].x += xSpeed
				}
			}

			if (newY < -TILT) {
				activeScene.y = -TILT;
				ySpeed = 0;
			} else if (newY > TILT) {
				activeScene.y = TILT;
				ySpeed = 0;
			} else {
				activeScene.y += ySpeed;
				player.y += ySpeed;
				movementRectangle.y += ySpeed;
				for (var j: int = 0; objects.length > j; j++) {
					objects[j].y += ySpeed
				}
			}
		}
		public function CoatPickup(): void {
			coatPickupTimer++;
			if (coatPickupTimer < 50) {
				if (coatPickupTimer % 5) {
					coatFull.visible = true;
				} else {
					coatFull.visible = false;
				}
			} else {
				removeChild(coatFull);
				coatTouch = false;
				player._coat.visible = true;
				player._body.visible = false;
			}
		}
		public function CactusPickup(): void { // pick up the cactus -Max
			cactusPickupTimer++;
			if (cactusPickupTimer < 50) {
				if (cactusPickupTimer % 5) {
					cactus.visible = true;
				} else {
					cactus.visible = false;
				}
			} else {
				removeChild(cactus);
			}
		}
		public function DaisyPickup(): void { // pick up the cactus -Max
			daisyPickupTimer++;
			if (daisyPickupTimer < 50) {
				if (daisyPickupTimer % 5) {
					daisy.visible = true;
				} else {
					daisy.visible = false;
				}
			} else {
				removeChild(daisy);
			}
		}

		public function ScarabPickup(): void { // pick up the cactus -Max
			scarabPickupTimer++;
			if (scarabPickupTimer < 50) {
				if (scarabPickupTimer % 5) {
					//scarabPickupTimer.visible = true;
				} else {
					scarab.visible = false;
				}
			} else {
				removeChild(scarab);
			}
		}

		public function KidArtPickup(): void { // pick up the cactus -Max
			kidArtPickupTimer++;
			if (kidArtPickupTimer < 50) {
				if (kidArtPickupTimer % 5) {
					kidArt.visible = true;
				} else {
					kidArt.visible = false;
				}
			} else {
				removeChild(kidArt);
			}
		}

		private function UpdateTrashCan(): void {
			trace("TrashCan " + _currentColor);
			if (_currentColor == BLACK || _currentColor == SEPIA) {
				trashCan._sepia.visible = true;
				trashCan._color.visible = false;
			} else if (_currentColor == DESATURATED || _currentColor == COLOR) {
				trashCan._sepia.visible = false;
				trashCan._color.visible = true;
			}
		}

		private function UpdateBus(): void {
			trace("Bus " + _currentColor);
			if (_currentColor == BLACK) {
				bus._black.visible = true;
				bus._sepia.visible = false;
				bus._desaturated.visible = false;
				bus._color.visible = false;
			} else if (_currentColor == SEPIA) {
				bus._black.visible = false;
				bus._sepia.visible = true;
				bus._desaturated.visible = false;
				bus._color.visible = false;
			} else if (_currentColor == DESATURATED) {
				bus._black.visible = false;
				bus._sepia.visible = false;
				bus._desaturated.visible = true;
				bus._color.visible = false;
			} else if (_currentColor == COLOR) {
				bus._black.visible = false;
				bus._sepia.visible = false;
				bus._desaturated.visible = false;
				bus._color.visible = true;
			}
		}

		public function MoveBus(): void {

			var busMoveSpeed: int = 50;
			var dx: Number = bus.x + busDestinationX; //dx is just the 'difference' between the object you want to rotate and the 'player' current location.x
			//get adjacent length
			var dy: Number = bus.y + busDestinationY; //dy is the 'difference' on the location.y
			//get opposite length
			var rad: Number = Math.atan2(dy, dx);
			//get hypotenuse length

			xMove = Math.cos(rad);
			//set the x velocities of the bus

			xMove *= fric;

			bus.x += xMove * busMoveSpeed;

			if (bus.x < busDestinationX * 1.5) {
				if (busTouch) {
					SetScene(BUS_INSIDE);
				} else {
					moveBus = false;
					sceneCycles = 0;
					bus.x = 2800 * sizeFactorX;
				}
			}
		}

		private function purgeObject(targetObject: MovieClip): void {
			//targetArrow.removeEventListener(Particle.PURGE_EVENT, purgeArrowHandler);
			try {
				if (targetObject.name == bus.name) {
					trace("REMOVING BUS IN PURGEOBJECT");
					activeObjectsArray.splice(0, 1);
					removeChild(targetObject);
				} else if (!sceneEnd) {
					trace("IN PURGEOBJECT, SCENE END == FALSE " + targetObject);
					activeObjectsArray.splice(0, 1);
					objectsLayer.removeChild(targetObject);
					trace("WHAT'S LEFT IN ACTIVEOBJECTSARRAY? " + activeObjectsArray);
				} else if (sceneEnd) {
					trace("IN PURGEOBJECT, SCENE END " + targetObject);
					activeObjectsArray.splice(0, activeObjectsArray.length);
					objectsLayer.removeChildren();
					trace("WHAT'S LEFT IN ACTIVEOBJECTSARRAY? " + activeObjectsArray);
				}
			} catch (e: Error) {
				trace("Failed to remove Object!", e);
			}
		}
		private function CloserArrow(): MovieClip {
			var newActiveArrow: MovieClip = activeArrow;
			if (DownArrow.x + DownArrow.y != 0) {
				if (DistanceToArrow(player.x, player.y, DownArrow) < activeDist) {
					if (DistanceToArrow(player.x, player.y, DownArrow) < DistanceToArrow(player.x, player.y, activeArrow)) {
						newActiveArrow = DownArrow;
					}
				}
			}
			if (UpArrow.x + UpArrow.y != 0) {
				if (DistanceToArrow(player.x, player.y, UpArrow) < activeDist) {
					if (DistanceToArrow(player.x, player.y, UpArrow) < DistanceToArrow(player.x, player.y, activeArrow)) {
						newActiveArrow = UpArrow;
					}
				}
			}
			if (LeftArrow.x + LeftArrow.y != 0) {
				if (DistanceToArrow(player.x, player.y, LeftArrow) < activeDist) {
					if (DistanceToArrow(player.x, player.y, LeftArrow) < DistanceToArrow(player.x, player.y, activeArrow)) {
						newActiveArrow = LeftArrow;
					}
				}
			}
			if (RightArrow.x + RightArrow.y != 0) {
				if (DistanceToArrow(player.x, player.y, RightArrow) < activeDist) {
					if (DistanceToArrow(player.x, player.y, RightArrow) < DistanceToArrow(player.x, player.y, activeArrow)) {
						newActiveArrow = RightArrow;
					}
				}
			}
			return newActiveArrow;
		}
		public function Clear(): void {
			this.removeChildren();
		}
		private function Buttons(): void {
			SceneButton.visible = true;
			buttonText.visible = true;
			buttonText.x = SceneButton.x - SceneButton.width / 3;
			buttonText.y = SceneButton.y + SceneButton.height / 3;
			buttonText.scaleX = sizeFactorX;
			buttonText.scaleY = sizeFactorY;
			//leaveRoom = true;
		}

		private function ClosestArrow(): void {
			activeArrow = CloserArrow();
			if (DistanceToArrow(mouseClick.x, mouseClick.y, activeArrow) > activeDist) {
				SceneButton.visible = false;
				buttonText.visible = false;
			} else { //if closer than activeDist to the nearest arrow
				if (activeArrow.name == DownArrow.name) {
					buttonText.text = roomText1;
					Buttons();
					//trace("activeArrow = DownArrow");
				} else if (activeArrow.name == UpArrow.name) {
					buttonText.text = roomText2;
					Buttons();
					//trace("activeArrow = UpArrow");
				} else if (activeArrow.name == LeftArrow.name) {
					buttonText.text = roomText3;
					Buttons();
					//trace("activeArrow = LeftArrow");
				} else if (activeArrow.name == RightArrow.name) {
					buttonText.text = roomText4;
					Buttons();
					//trace("activeArrow = RightArrow");
				} else {
					SceneButton.visible = false;
					buttonText.visible = false;

				} //if closer than activeDist to the nearest arrow
			}
		}

		public function Update(): void {
			if(playEnd)
			{
				addChild(ending);
				ending.gotoAndPlay(1);
				playEnd = false;
			}
			if (daysTracker == 2)
			{
				hints.gotoAndStop(2);
			}
			if(objectNum == 1)
			{
				hints.gotoAndStop(3);
			}
			if(objectNum == 2)
			{
				hints.gotoAndStop(4);
			}
			if(objectNum == 3)
			{
				hints.gotoAndStop(5);
			}
			if(daysTracker >= 4 && objectNum >= 3)
			{
				endGame = true;
			}
			//trace("UpArrow Location: " + UpArrow.x + " " + UpArrow.y + "\n" + "DownArrow Location: " + DownArrow.x + " " + DownArrow.y + "\n" + "LeftArrow Location: " + LeftArrow.x + " " + LeftArrow.y + "\n" + "RightArrow Location: " + RightArrow.x + " " + RightArrow.y);
			ClosestArrow();
			//trace("Scene:" + _currentScene + " Color:" + _currentColor);
			if (!_currentScene || !_currentColor) { //if this is NOT the current scene or color, return to whatever sent you here
				return;
			} else { //if this IS the current State, execute the rest of the Update() function
				_currentScene.update(this); //runs the update() function in the current State
				_currentColor.update(this);
				//remember to use lowercase when executing the enter(), update(), exit() functions inside the states!!
			} //end if/else Current State test
			if (movePlayer) {
				UpdatePlayerLocation();
				playerCenterW = player.width / 2;
				playerCenterH = player.height / 2;
			} //if movePlayer == true
			/*if (acclActive) {
				MoveActiveScene(activeObjectsArray);
			}*/
		} //end Update()

		/*
			if (win) {
			this.removeEventListener(Event.ADDED_TO_STAGE, SetupTouchLayer);
			touchLayer.removeEventListener(MouseEvent.MOUSE_DOWN, MovePlayer);
			removeChild(touchLayer);
			}
		*/

		public function FacePlayer(multiplier: Number): void { //super nifty function that can rotate an object relative to the player, can easily be changed to rotate relative something else (dog that always faces its owner, kid that faces their mom, etc.)
			//when you call this function if you call it as 'facePlayer(1)' the object will rotate according to the player's location
			//if you call the function as 'facePlayer(-1)' the object will always face AWAY from the player (kid won't look at you while crying, etc.)
			//uses the xVelel and yVelel variables to accomplish this
			//said another way:
			//inputing a multiplier of '1' will face the player
			//a multiplier of '-1' will face away from the player
			var dx: Number = player.x - x; //dx is just the 'difference' between the object you want to rotate and the 'player' current location.x
			var dy: Number = player.y - y; //dy is the 'difference' on the location.y
			var rad: Number = Math.atan2(dy, dx);
			xVel = Math.cos(rad * multiplier) / 180 * Math.PI;
			yVel = Math.sin(rad * multiplier) / 180 * Math.PI;
		}

		public function DistanceToPlayer(givenX: Number, givenY: Number): Number { //calculates how far from the player an object is
			//exactly what you think it is
			//could be used to make something 'follow' the player
			//are you thinking of the kid yet? or am I still not being heavy handed enough
			var dx: Number = player.x + playerCenterW - givenX;
			var dy: Number = player.y + playerCenterH - givenY;
			return Math.sqrt(dx * dx + dy * dy);
		}
		private function DistanceToArrow(givenX: Number, givenY: Number, target: MovieClip): int {
			var dx: Number = target.x + (target.width / 2) - givenX;
			var dy: Number = target.y + (target.height / 2) - givenY;
			return Math.sqrt(dx * dx + dy * dy);
		}

		public function RandomDirection(): void { //exactly what the name implies
			var a: Number = Math.random() * 5.5;
			xVel = Math.cos(a);
			yVel = Math.sin(a);
		}

		public function SetPos(x, y): void { //I believe in your ability to figure this one out too
			this.x = x;
			this.y = y;
		}

		public function GetLocation(): Point { //returns the location of something in the current Scene
			var point = new Point(this.x, this.y);
			return (point);
		}

		public function SetScene(newScene: iBehaviors): void { //this is the function that makes the state machine work
			if (_currentScene == newScene) return;
			if (_currentScene) {
				trace("EXITING CURRENT SCENE");
				_currentScene.exit(this);
				if (activeObjectsArray.length > 0) {
					for (var i: int = 0; i < activeObjectsArray.length; i++) { //this loop removes everything in the activeObjectsArray using the purgeObject method
						if (activeObjectsArray[i].name == bus.name) {
							trace("REMOVING BUS IN SetScene() " + activeObjectsArray[i]);
							purgeObject(activeObjectsArray[i]);
							trace("IS BUS GONE? " + activeObjectsArray);
						} else {
							trace("SENDING THESE TO PURGEOBJECT FROM SetScene(): " + activeObjectsArray);
							purgeObject(activeObjectsArray[i]);
						}
					}
				}
			}
			SceneButton.visible = false;
			buttonText.visible = false;
			_previousScene = _currentScene;
			_currentScene = newScene;
			activeScene = SceneChange();
			trace("ENTERING NEW SCENE");
			_currentScene.enter(this);
			sceneCycles = 0; //sets the timer back to 0 once a new Scene has been triggered
			ColorChange();
		}

		public function SetColor(newColor: iColors): void { //this is the function that makes the state machine work
			if (_currentColor == newColor) return;
			if (_currentColor) {
				_currentColor.exit(this);
			}
			_previousColor = _currentColor;
			_currentColor = newColor;
			_currentColor.enter(this);
			colorCycles = 0; //sets the timer back to 0 once a new Scene has been triggered
			//trace("Scene: " + _currentScene + "Color: " + _currentColor);
			ColorChange();
		}

		public function ColorChange(): void {
			//trace("CurrentScene: " + _currentScene);
			for (var i: int = 0; _MapsStateArray.length > i; i++) {
				//trace("Do these two Match?" + _currentScene + _MapsStateArray[i]);
				if (_MapsStateArray[i] != _currentScene) {
					if (_MapsMCArray[i].visible) {
						_MapsMCArray[i].visible = false;
					}
				} else {
					_MapsMCArray[i].visible = true;
					var _black: MovieClip = _MapsMCArray[i]._black;
					var _sepia: MovieClip = _MapsMCArray[i]._sepia;
					var _desaturated: MovieClip = _MapsMCArray[i]._desaturated; //***Registers as Null in the Bedroom??***
					var _color: MovieClip = _MapsMCArray[i]._color;
					_ColorMCArray.push(_black, _sepia, _desaturated, _color);

					if (_MapsStateArray[i] == BUS_STOP) {
						UpdateTrashCan();
						UpdateBus();
					}

					//trace("_ColorArray Values:" + _ColorMCArray)

					for (var j: int = 0; _ColorStateArray.length > j; j++) {
						if (_ColorStateArray[j] != _currentColor) {
							_ColorMCArray[j].visible = false;
							//trace("_ColorMCArray[j] visible should be false: " + _ColorMCArray[j].visible);
						} else {
							_ColorMCArray[j].visible = true;
							//trace("_ColorMCArray[j] visible should be true: " + _ColorMCArray[j].visible);
						} //end else if _ColorsArray[j] == newColor
					} //end for _ColorsArray
					if (_ColorMCArray.length > 0) {
						_ColorMCArray.splice(0, _ColorMCArray.length);
						//trace("_ColorMCArray Should be Clear:" + _ColorMCArray);
					}
				} //end else if _MapsArray[i] == newScene
			} //end for _MapsArray
			sceneEnd = false;
		} //end ColorChange()

		public function SceneChange(): MovieClip {
			var scene = MovieClip;
			for (var i: int = 0; _MapsStateArray.length > i; i++) {
				//_MapsMCArray.push(bedroom, breakroom, busInside, busStop, cubicleOthers, cubicleYours, elevatorIn, elevatorOut, flowerShopIn, flowerShopOut, newsStand, officeHall);


				/*
				if (_MapsStateArray[i] != CurrentScene) {
					_MapsMCArray.splice(0, i);
					trace(_MapsMCArray);
				
				*/
				if (_MapsStateArray[i] != _currentScene) {
					_MapsMCArray[i].visible = false;
				} else {
					if (_currentScene != NEWS_STAND) {
						_MapsMCArray[i].visible = true;
						scene = _MapsMCArray[i];
						sizeFactorX = (Capabilities.screenResolutionX / _MapsMCArray[i].width);
						sizeFactorY = (Capabilities.screenResolutionY / _MapsMCArray[i].height);
						_MapsMCArray[i].width = Capabilities.screenResolutionX;
						_MapsMCArray[i].height = Capabilities.screenResolutionY;
					} else {
						_MapsMCArray[i].visible = true;
						scene = _MapsMCArray[i];
						sizeFactorX = (Capabilities.screenResolutionX / _MapsMCArray[i].width);
						sizeFactorY = Capabilities.screenResolutionY * 2 / _MapsMCArray[i].height;
						_MapsMCArray[i].width = Capabilities.screenResolutionX;
						_MapsMCArray[i].height = Capabilities.screenResolutionY * 2;
					}
				}
			}
			trace("SizeFactorX: " + sizeFactorX + ", " + "SizeFactorY: " + sizeFactorY);
			return scene;
		}

		public function get PreviousScene(): iBehaviors { //gets the previously executing Scene
			return _previousScene;
		}

		public function get CurrentScene(): iBehaviors { //gets the currently executing Scene
			return _currentScene;
		}

		public function get PreviousColor(): iColors { //gets the previously executing Color
			return _previousColor;
		}

		public function get CurrentColor(): iColors { //gets the currently executing Color
			return _currentColor;
		}

		public function ToggleActive(): void { //essentially is like flicking a lightswitch on or off to set a Scene as Active or Inactive
			if (isActive) {
				isActive = false;
			} else {
				isActive = true;
			}

		}

	}
}