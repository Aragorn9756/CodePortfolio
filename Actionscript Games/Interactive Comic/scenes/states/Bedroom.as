package scenes.states {

	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public class Bedroom implements iBehaviors {
		private var numSecs: int = 3;
		private var fps: int = 24;

		public function enter(map: SceneMain): void {
			SceneMain.roomText1 = "Leave House";
			map.AddPlayer(106, 639, 0, 500, 800, 300);
			map.LoadBedRoom();
			SceneMain.wentToWork = true;
		}
		public function exit(map: SceneMain): void {
			map.RemovePlayer();
			map.ExitBedRoom();
		}
		public function update(map: SceneMain): void {
			if (SceneMain.leaveRoom) {
				SceneMain.leaveRoom = false;
				map.SetScene(SceneMain.BUS_STOP);
			}
			if (SceneMain.wentToWork) {
				map.sceneCycles++;
				trace("starting timer in Bedroom");
				if (map.sceneCycles == fps * numSecs) {
					SceneMain.wentToWork = false;
					SceneMain.NEXTDAY = true;
					trace("NEXTDAY == true");
				}
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
			} //end update
		}
	}
}