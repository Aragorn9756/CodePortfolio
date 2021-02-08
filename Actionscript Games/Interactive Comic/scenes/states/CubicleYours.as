package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public class CubicleYours implements iBehaviors {

		public function enter(map: SceneMain): void {
			SceneMain.roomText1 = "Get Out of Here";
			map.AddPlayer(229, 450, 400, 400, 400, 400);
			map.LoadCubicleYours();
		}
		public function exit(map: SceneMain): void {
			if (!map.chairTouch) {
				map.RemovePlayer();
			}
			map.RemoveCubicleYours();
		}
		public function update(map: SceneMain): void {
			if (map.chairTouch) {
				map.sceneCycles++;
				if (map.sceneCycles > 100) {
					if(SceneMain.endGame)
					{
						SceneMain.playEnd = true;
					}
					else
					{
						map.SetScene(SceneMain.CUBICLE_YOURS_LAPTOP);
					}
				}
			}
			if (SceneMain.leaveRoom) {
				if (map.activeArrow == map.DownArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.OFFICE_HALL);
				}
			}
		} //end update
	}
}