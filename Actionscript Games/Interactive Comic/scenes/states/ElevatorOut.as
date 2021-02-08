package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	//all the names inside each state need to be changed to reflect their actual names
	//for an example of a state that 'matches' correctly see the "Bedroom" state
	public class ElevatorOut implements iBehaviors {

		public function enter(map: SceneMain): void {
			SceneMain.roomText1 = "Take Elevator Up";
			SceneMain.roomText3 = "Exit Building";
			map.AddPlayer(221.95, 900, 0, 1000, 2776, 1440);
			map.LoadElevatorOut();
			map.sceneCycles = 0;

		}
		public function exit(map: SceneMain): void {
			map.RemovePlayer();
			map.RemoveElevatorOut();

		}
		public function update(map: SceneMain): void {
			map.sceneCycles++;
			if (SceneMain.leaveRoom) {
				if (map.activeArrow == map.RightArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.ELEVATOR_IN);
				}
				if (map.activeArrow == map.LeftArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.NEWS_STAND);
				}
			}
		} //end update
	}
}