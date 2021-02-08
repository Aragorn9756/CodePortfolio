package lib.survive
{
	import flash.display.MovieClip;
	import lib.survive.Particle;
	import lib.survive.Player;
	public class Turret extends MovieClip
	{
		public var target:Player;
		public var needsTarget:Boolean;
		public var turnRate:Number;
		public var bulletDelay:int;
		public var shotSpeed:Number;
		private var bulletCounter:int;
		private var turretLife:int;//added turret life
		
		public function Turret()
		{
			shotSpeed = 10;
			bulletDelay = 45;
			bulletCounter = Math.random() * bulletDelay;
			turnRate = 10;
			needsTarget = true;
			turretLife = 30;
		}
		
		public function update():Particle
		{
			var bullet:Particle;

			if (target != null/* && target.status != "Dead"*/)
			{
				//old method
				var targetAngle:Number = Math.atan2(target.y - y, target.x - x) * 180 / Math.PI;
				
				//compliments of http://jobemakar.blogspot.com/2008/01/predictive-shooting.html
				
				/*
				var targetRot:Number = Math.atan2(target.yVel, target.xVel);
				
				var cosTheta:Number = Math.cos(targetRot);
				var sinTheta:Number = Math.sin(targetRot);
				
				var targetSpeed:Number = Math.sqrt(Math.pow(target.xVel, 2) + Math.pow(target.yVel, 2));
				
				
				
				
				var xDiff:Number = target.x - x;
				var yDiff:Number = target.y - y;
				
				
				var A:Number = -Math.pow(shotSpeed, 2) + Math.pow(targetSpeed, 2) * Math.pow(cosTheta, 2) + Math.pow(targetSpeed, 2) * Math.pow(sinTheta, 2);
				var B:Number = (2 * xDiff * targetSpeed * cosTheta) + (2 * yDiff * targetSpeed * sinTheta);
				var E:Number = Math.pow(xDiff, 2) + Math.pow(yDiff, 2);
				
				var val:Number = Math.abs(B * B - 4 * A * E);
				var sqrt:Number;
				
				if (val < 0)
				{
					sqrt = -Math.sqrt(Math.abs(val));
				}
				else
				{
					sqrt = Math.sqrt(val);
				}
				
				var t:Number = (-B - sqrt) / (2 * A);
				
				var collisionX:Number = target.x + targetSpeed * cosTheta * t;
				var collisionY:Number = target.y + targetSpeed * sinTheta * t;
								
				var targetAngle:Number = Math.atan2(collisionY - y, collisionX - x) * 180 / Math.PI;
				*/
				//end compliments
				
				if (Math.abs(targetAngle - rotation) < turnRate)
				{
					rotation = targetAngle;
				}
				else
				{
					if (targetAngle - rotation > 180)
					{
						targetAngle -= 360;
					}
					else if (targetAngle - rotation < -180)
					{
						targetAngle += 360;
					}
					
					if (targetAngle - rotation > 0)
					{
						rotation += turnRate;
					}
					else
					{
						rotation -= turnRate;
					}
				}
					
				if (bulletCounter >= bulletDelay)
				{
					bullet = createBullet();
					//bullet.speed = shotSpeed;
					
					bullet.ownedByPlayer = false;
					bullet.xVel = Math.cos(rotation * Math.PI / 180) * shotSpeed;
					bullet.yVel = Math.sin(rotation * Math.PI / 180) * shotSpeed;
					bulletCounter = 0;
				}
				else
				{
					bulletCounter ++;
				}
			}
			else
			{
				needsTarget = true;
			}
			return bullet;
		}
		
		private function createBullet():Particle
		{
			var bullet:Particle = new Bullet();
			
			bullet.x = x;
			bullet.y = y;
			bullet.rotation = rotation;
			
			return bullet;
		}
		
		public function hit (health:Number):void {
			turretLife -= health;
		}
		
		public function getTurretLife ():Number {
			return turretLife;
		}
	}
}