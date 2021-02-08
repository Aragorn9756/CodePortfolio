package scenes.states {
	import scenes.SceneMain;
	import scenes.colorState.iColors;

	public class FlowerShopOut implements iBehaviors {

		public function enter(map: SceneMain): void {
			SceneMain.roomText2 = "Enter the Flower Shop";
			SceneMain.roomText3 = "Head to Work";
			SceneMain.roomText4 = "Walk to the Bus Stop";
			map.AddPlayer(633, 700, 200, 200, 600, 600);
			map.LoadFlowerShopOut();
		}

		public function exit(map: SceneMain): void {
			map.RemovePlayer();
			map.RemoveFlowerShopOut();
		}

		public function update(map: SceneMain): void {
			map.sceneCycles++;
			/*if (map.sceneCycles > 100) {
				map.SetScene(SceneMain.BREAK_ROOM);
			}*/
			if (map.kidArtTouch) {
				map.KidArtPickup();
			}

			if (map.scarabTouch) {
				map.ScarabPickup();
			}
			if (SceneMain.leaveRoom) {
				if (map.activeArrow == map.UpArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.FLOWER_SHOP_IN);
				}
				if (map.activeArrow == map.RightArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.BUS_STOP);
				}
				if (map.activeArrow == map.LeftArrow) {
					SceneMain.leaveRoom = false;
					map.SetScene(SceneMain.NEWS_STAND);
				}
			}
		} //end update
	}
}