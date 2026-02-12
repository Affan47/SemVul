__weak void abort(void)
{
	BUG();


	panic("Oops failed to kill thread");
}
