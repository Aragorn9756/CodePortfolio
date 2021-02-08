package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public class CubicleOthers implements iBehaviors {
		private var numSecs: int = 2;
		private var fps: int = 24;
		public function enter(map: SceneMain): void {
			SceneMain.roomText1 = "Back to the" + "\n" + "Hallway";
			map.AddPlayer(500, 400, 334, 511, 500, 360);
			map.LoadCubicleOthers();
		}
		public function exit(map: SceneMain): void 
		{
			map.RemovePlayer();
			map.RemoveCubicleOthers();
		}
		public function update(map: SceneMain): void {
			map.sceneCycles++;
			if (map.sceneCycles == fps * numSecs) {
				map.SetScene(SceneMain.OFFICE_HALL);
			}
			/*
			if(SceneMain.objectNum > 0)
			{
				map.SetColor(SceneMain.SEPIA);
			}
			if(SceneMain.dayNumber > 3)
			{
				map.SetColor(SceneMain.DESATURATED);
			}
			if(SceneMain.dayNumber > 5)
			{
				map.SetColor(SceneMain.COLOR);
			}
			*/
			if (SceneMain.leaveRoom) {
				if (map.activeArrow == map.DownArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.OFFICE_HALL);
				}
			}
			
		} //end update
	}
}