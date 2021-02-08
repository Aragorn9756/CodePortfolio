package scenes.colorState {

	import scenes.SceneMain;
	import scenes.states.iBehaviors;

	public class Black implements iColors {

		public function update(map: SceneMain): void {
			if(SceneMain.objectNum > 0)
			{
				map.SetColor(SceneMain.SEPIA);
			}
		}
		public function enter(map: SceneMain): void {
		}
		public function exit(map: SceneMain): void {

		}
	}
}