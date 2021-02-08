package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public class NewsStand implements iBehaviors {
		private var numSecs: int = 2;
		private var fps: int = 24;
		private var enterOffice: Boolean = false;

		public function enter(map: SceneMain): void {
			SceneMain.roomText1 = "Enter Building";
			SceneMain.roomText3 = "Head Towards the" + "\n" + "Flower Shop";
			map.AddPlayer(3000, 800, 0, 200, 2776, 1240);
			//if coming from elevator, start at top of building and go down.
			//otherwise start at bottom of building.
			map.StartLoadNewsStand();
		}
		public function exit(map: SceneMain): void {
			map.RemovePlayer();
			map.RemoveNewsStand();
		}
		public function update(map: SceneMain): void {
			if (map.player.y > 200) {
				map.player.height = map.player.y / 2;
				map.player.width = map.player.y / 4;
			}
			/*
			if (SceneMain.cardTouch) {
				map.SetColor(SceneMain.SEPIA);
			}
			if (SceneMain.dayNumber > 3) {
				map.SetColor(SceneMain.DESATURATED);
			}
			if (SceneMain.dayNumber > 5) {
				map.SetColor(SceneMain.COLOR);
			}
*/
			if (SceneMain.leaveRoom) {
				if (map.activeArrow == map.UpArrow) {
					SceneMain.leaveRoom = false;
					map.EnterOfficeBuilding();
				}
				if (map.activeArrow == map.LeftArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.FLOWER_SHOP_OUT);
				}
			}

		} //end update
	}
}