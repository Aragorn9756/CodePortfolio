package scenes.colorState {

	import scenes.SceneMain;
	import scenes.states.iBehaviors;

	public class Desaturated implements iColors {

		public function update(map: SceneMain): void {
			if(SceneMain.objectNum > 2)
			{
				map.SetColor(SceneMain.COLOR);
			}
		}
		public function enter(map: SceneMain): void {}
		public function exit(map: SceneMain): void {}
	}
}