package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	//all the names inside each state need to be changed to reflect their actual names
	//for an example of a state that 'matches' correctly see the "Bedroom" state
	public class OfficeHall implements iBehaviors {

		public function enter(map: SceneMain): void {
			SceneMain.roomText1 = "Get Out of Here";
			SceneMain.roomText2 = "Take a Break";
			SceneMain.roomText3 = "Go to Your Cubicle";
			SceneMain.roomText4 = "Look at a" + "\n" + "Friend's Cubicle";
			map.AddPlayer(775, 400, 450, 0, 650, 800);
			map.LoadHallWay();
			/*
			if (SceneMain.objectNum > 0) {
				map.SetColor(SceneMain.SEPIA);
			}
			if (SceneMain.objectNum > 1) {
				map.SetColor(SceneMain.DESATURATED);
			}
			if (SceneMain.objectNum > 2) {
				map.SetColor(SceneMain.COLOR);
			}
			*/
		}
		public function exit(map: SceneMain): void {
			map.RemovePlayer();
			map.ExitHallWay();
		}
		public function update(map: SceneMain): void {
			if (map.player.y > 200) {
				map.player.height = map.player.y;
				map.player.width = map.player.y / 2;
			}
			if (SceneMain.leaveRoom) {
				if (map.activeArrow == map.DownArrow) {
					SceneMain.leaveRoom = false;
					trace("astrid you're right i knew it");
					map.SetScene(SceneMain.ELEVATOR_IN);
				}
				if (map.activeArrow == map.UpArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.BREAK_ROOM);
				}
				if (map.activeArrow == map.RightArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.CUBICLE_OTHERS);
				}
				if (map.activeArrow == map.LeftArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.CUBICLE_YOURS);
				}
			}

		} //end update
	}
}