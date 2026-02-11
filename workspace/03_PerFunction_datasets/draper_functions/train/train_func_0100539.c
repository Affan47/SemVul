reloadpalette()
{
	ht_uformat_viewer::reloadpalette();
	if (analy_sub) analy_sub->output->changeConfig();
}
