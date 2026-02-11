handle_BIT_SYNC(float val)
{
  float p;
  static int cnt = 0;

  p = (100.0 * (val - _lock)) / _lock;

  if (_verbose > 1)
    printf("BIT SYNC: %6.2f, %6.2f => %6.2f\n", val, _lock, p);

  if (p > 50)
    cnt++;

  if (cnt == 2)
    {
      cnt = 0;
      set_state(STATE_BIT);
    }
}
