package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public class Breakroom implements iBehaviors {
		private var numSecs: int = 6;
		private var fps: int = 24;

		public function enter(map: SceneMain): void {
			map.AddPlayer(500, 400, 0, 1000, 2776, 1440);
			map.LoadBreakroom();
			
		}
		public function exit(map: SceneMain): void {
			map.RemovePlayer();
			map.RemoveBreakroom();
		}
		public function update(map: SceneMain): void {
			map.sceneCycles++;
			if (map.sceneCycles == fps * numSecs) {
				map.SetScene(SceneMain.OFFICE_HALL);
			}
			if (map.buttlerflyTouch) {
				map.butterflyPinPickupTimer++;
			}
			if (map.butterflyPinPickupTimer > 60) {
				map.ResetDefaultPlayer();
			}
			if (SceneMain.leaveRoom) {
				SceneMain.leaveRoom = false;
				map.SetScene(SceneMain.OFFICE_HALL);
			}




			//end update
		}

	}
}