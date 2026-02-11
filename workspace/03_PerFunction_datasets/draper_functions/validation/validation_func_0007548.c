objects_setup(void)
{
  int i,x,y;
  sprite_t *sp;
  float v[2];

  srand(23);

  sp = sprite_create(&bonusmachine);
  sprite_group_insert(mech_group,sp);
  sprite_set_pos(sp,level.xmax/2,15);

  for (i=0;i<3;i++)
    {
      sp = sprite_create(&bird);
      sprite_group_insert(mech_group,sp);
    }

  for (i=0;i<5;i++)
    {
      sp = sprite_create(&bouncer);
      sprite_group_insert(mech_group,sp);
      sprite_set_pos(sp,rand() % 700 + 50,rand() % 200 + 100);
    }

  sp = sprite_create(&cloud);
  sprite_group_insert(foreground_group,sp);
  sprite_set_pos(sp,400,70);
  v[0] = 15; v[1] = 0;
  sprite_set_vel(sp,v);

  sp = sprite_create(&cloud);
  sprite_group_insert(foreground_group,sp);
  sprite_set_pos(sp,0,150);
  v[0] = 10; v[1] = 0;
  sprite_set_vel(sp,v);

  sp = sprite_create(&zeppelin);
  sprite_group_insert(mech_group,sp);
  sprite_set_pos(sp,50,200);

  sp = sprite_create(&airballoon);
  sprite_group_insert(mech_group,sp);
  sprite_set_pos(sp,100,150);
  v[0] = 5; v[1] = 3;
  sprite_set_vel(sp,v);

  sp = sprite_create(&cannon);
  sprite_group_insert(mech_group,sp);
  sprite_set_pos(sp,380,518);
}
