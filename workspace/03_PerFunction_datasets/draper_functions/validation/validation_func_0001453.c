ghc_try_random(void)
{
	g_assert(ghc_connecting);

	if (!ghc_pick()) {
		ghc_connecting = FALSE;
	}
}
