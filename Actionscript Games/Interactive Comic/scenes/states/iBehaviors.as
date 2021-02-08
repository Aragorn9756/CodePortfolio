package scenes.states {
	
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public interface iBehaviors {
		
		function update(map: SceneMain):void;
		function enter(map: SceneMain):void;
		function exit(map: SceneMain):void;
	}
}
