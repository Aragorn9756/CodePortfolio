package scenes.colorState {

	import scenes.SceneMain;
	import scenes.states.iBehaviors;

	public class Sepia implements iColors {

		public function update(map: SceneMain): void {
			if(SceneMain.objectNum > 1)
			{
				map.SetColor(SceneMain.DESATURATED);
			}
		}
		public function enter(map: SceneMain): void {}
		public function exit(map: SceneMain): void {}
	}
}