UpdateMahjong ()
{
  int x;

  MahjongData = 0;
  for (x = 0; x < 21; x++)
    {
      if (DTestButton (&MahjongButtons[x]))
	{
	  MahjongData |= 1 << x;
	}
    }
}
