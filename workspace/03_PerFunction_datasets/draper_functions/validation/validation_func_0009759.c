FPS(const u32 newFPS)
{
  fps = newFPS;

  if (fps)
    timer.Start(1000L/fps);
  else
    timer.Pause();
}
