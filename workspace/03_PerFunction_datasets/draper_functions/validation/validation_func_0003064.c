alx_reinit(struct alx_priv *alx)
{
	ASSERT_RTNL();

	alx_halt(alx);
	alx_activate(alx);
}
