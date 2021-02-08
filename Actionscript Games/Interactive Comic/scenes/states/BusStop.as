package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public class BusStop implements iBehaviors {

		public function enter(map: SceneMain): void {
			SceneMain.roomText4 = "Go Home";
			SceneMain.roomText1 = "Catch the Next Bus";
			map.AddPlayer(221, 600, 200, 200, 600, 600);
			map.LoadBusStop();
		}
		public function exit(map: SceneMain): void {
			map.RemovePlayer();
			map.RemoveBusStop();
			if (map.busTouch) {
				map.busTouch = false;
			}
		}
		public function update(map: SceneMain): void {
			map.sceneCycles++;
			//trace(map.player.x);
			//trace(map.player.y);

			if (map.sceneCycles > 200) {
				map.moveBus = true;
			}
			if (map.coatTouch) {
				map.CoatPickup();
			}
			if (map.moveBus) {
				map.MoveBus();
			}

			if (SceneMain.leaveRoom) {
				if (map.activeArrow == map.RightArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.BED_ROOM);
				}
				if (map.activeArrow == map.DownArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.BUS_INSIDE);
				}
			}
		} //end update
	}
}