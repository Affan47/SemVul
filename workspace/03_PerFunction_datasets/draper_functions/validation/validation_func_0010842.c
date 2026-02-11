moveaccelerator (int n)
{
   if (enemy[n].y >= komiy - tonguelength)
   {
      enemy[n].speedx += (float)sign(komix - enemy[n].x) / (enemy[n].floatvar * 2);
   }
   if (fabs(enemy[n].speedx) > enemy[n].floatvar)
   {
      enemy[n].speedx = enemy[n].floatvar * sign(enemy[n].speedx);
   }

   if (levelinfo.guardianaccels)
   {
      enemy[n].y = lightningy + enemy[n].intvar;
   }

   enemy[n].x += enemy[n].speedx;
   if (enemy[n].x < SPRITE_SIZE / 2)
   {
      enemy[n].x = SPRITE_SIZE / 2;
      enemy[n].speedx = fabs(enemy[n].speedx);
   }
   if (enemy[n].x > WIDTH - (SPRITE_SIZE / 2))
   {
      enemy[n].x = WIDTH - (SPRITE_SIZE / 2);
      enemy[n].speedx = fabs(enemy[n].speedx) * -1;
   }

   return;
}
