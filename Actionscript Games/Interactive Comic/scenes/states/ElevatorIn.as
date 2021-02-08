package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public class ElevatorIn implements iBehaviors {

		public function enter(map: SceneMain): void {
			map.AddPlayer(1000,700,100,100,300,300);
			map.player.gotoAndStop(4); 
			map.sceneCycles = 0;
			map.LoadElevatorIn();
		}
		public function exit(map: SceneMain): void {
			map.RemovePlayer();
			map.RemoveElevatorIn();
		}
		public function update(map: SceneMain): void {
			map.sceneCycles++;
			//trace(map.player.x);
			//trace(map.player.y);
			if (map._previousScene == SceneMain.OFFICE_HALL && map.sceneCycles > 60) {
				map.SetScene(SceneMain.ELEVATOR_OUT);
			}
			if (map._previousScene == SceneMain.ELEVATOR_OUT && map.sceneCycles > 60) {
				map.SetScene(SceneMain.OFFICE_HALL);
			}
		} //end update
	}
}