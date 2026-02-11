mode(dashboard_modes_t m)
{
	int vis;
	_mode = m;
	switch(_mode)
	{
	  case DASHBOARD_GAME:
		vis = 1;
		break;
	  default:
		vis = 0;
		break;
	}
	wmain->visible(vis);
	whealth->visible(vis);
	wtemp->visible(vis);
	wttemp->visible(vis);
	wradar->visible(vis);
	dhigh->visible(vis);
	dscore->visible(vis);
	dstage->visible(vis);
	dships->visible(vis);
	switch(_mode)
	{
	  case DASHBOARD_OFF:
		break;
	  default:
		gengine->invalidate();
		gengine->flip();
		gengine->invalidate();
		gengine->flip();
		gengine->invalidate();
		break;
	}
}
