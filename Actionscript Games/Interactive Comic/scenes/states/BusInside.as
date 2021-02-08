package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public class BusInside implements iBehaviors {
		private var numSecs: int = 5;
		private var fps: int = 24;

		public function enter(map: SceneMain): void {
			map.LoadBusInside();
			}
		public function exit(map: SceneMain): void {
			map.RemoveBusInside();
			}
		public function update(map: SceneMain): void {
			map.sceneCycles++;
			trace(map.player.x);
			trace(map.player.y);
			if (map.sceneCycles == fps * numSecs){
				map.SetScene(SceneMain.FLOWER_SHOP_OUT)
				
			}
		}
	}
}