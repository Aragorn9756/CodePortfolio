package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public class CubicleYours_Laptop implements iBehaviors {

		public function enter(map: SceneMain): void {
			map.LoadCubicleYours_Laptop();
		}
		public function exit(map: SceneMain): void {
			map.RemoveCubicleYours_Laptop();
		}
		public function update(map: SceneMain): void {
			map.sceneCycles++;
			trace("map.clock == " + map.clock);
			if (map.sceneCycles == 48) {
				map.sceneCycles = 0;
				if (map.clock < 13) {
					map.clock++;
				}
				if (map.clock == 12) {
					map.AM_true = false;
				}
				if (map.clock == 13) {
					map.clock = 1;
				}
				if (map.clock == 2) {
					map.SetScene(SceneMain.BREAK_ROOM);
				}
				if (map.clock == 7) {
					map.clock = 8;
					map.AM_true = true;
					SceneMain.wentToWork = true;
					trace("wentToWork: " + SceneMain.wentToWork);
					map.SetScene(SceneMain.BREAK_ROOM);
				} else
				if (map.AM_true) {
					map.clockText.text = map.clock.toString() + ":00 " + map.AM;
				} else if (!map.AM_true) {
					map.clockText.text = map.clock.toString() + ":00 " + map.PM;
				}
			}

		}
	}
}