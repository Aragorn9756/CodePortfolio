package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public class FlowerShopIn implements iBehaviors {

		public function enter(map: SceneMain): void {
			SceneMain.roomText4 = "Back Outside";
			map.AddPlayer(500, 550, 200, 200, 600, 600);
			map.LoadFlowerShopIn();
		}
		public function exit(map: SceneMain): void {
			map.RemovePlayer();
			map.RemoveFlowerShopIn();
		}
		public function update(map: SceneMain): void {
			map.sceneCycles++;
			if (map.cactusTouch) {
				map.CactusPickup();
			}
			if (map.daisyTouch) {
				map.DaisyPickup();
			}
			if (SceneMain.leaveRoom) {
				if (map.activeArrow == map.RightArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.FLOWER_SHOP_OUT);
				}
			}
			//end update
		}
	}
}