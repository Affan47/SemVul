setup()
{
  CRITICAL(anim = animation_load(path_to_data("firebomb.png"),
				 1,32,30));
  animation_set_alpha(anim,200);
  animation_last_frame(anim)->trigger = frame_trigger;
  return 0;
}
