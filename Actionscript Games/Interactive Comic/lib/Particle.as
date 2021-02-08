package lib {
	import flash.display.MovieClip;
	import flash.events.Event;

	public class Particle extends MovieClip {
		public static const PURGE_PARTICLE: String = "PURGE";

		public var xVel: Number;
		public var yVel: Number;
		public var airResistance: Number;
		public var gravity: Number;

		private var cyclesTimer: int = 0;
		private var alphaDecay: Number = 0.9;

		public function Particle() {
			xVel = 0;
			yVel = 0;
			airResistance = 1.15;
			gravity = 0;
		}

		public function update(): void {
			cyclesTimer++;
			yVel += gravity;
			yVel *= airResistance;
			xVel *= airResistance;

			rotation = Math.atan2(yVel, xVel) * 180 / Math.PI;

			x += xVel;
			y += yVel;

			if (cyclesTimer > 60) {
				this.alpha *= alphaDecay;
			}
			if (cyclesTimer > 180 || this.alpha < 0.05) {
				//trace("Particle Purged!");
				dispatchEvent(new Event(Particle.PURGE_PARTICLE, true, false));
			}
		}
	}
}