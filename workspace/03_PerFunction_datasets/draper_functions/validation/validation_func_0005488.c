NewIP(const char *ip, short port, void *cal_, int c)
{
	Calendar *cal = (Calendar *) cal_;

	if (!cal->Has(ip, port)) {
		cal->Add(new ServerScan(ip, port, cal,
			(apptime) (Clock::get()->GetAppTime() + c*INITIAL_SCANS_INTERVAL)));
	}
}
