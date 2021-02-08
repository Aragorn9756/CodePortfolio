package scenes.colorState {
	
	import scenes.SceneMain;
	import scenes.states.iBehaviors;

	public interface iColors {
		
		function update(map: SceneMain):void;
		function enter(map: SceneMain):void;
		function exit(map: SceneMain):void;
	}
}
