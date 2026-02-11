m_wallops(aClient *cptr, aClient *sptr, int parc, char *parv[])
{
	sendto_ops_butone(IsServer(cptr) ? cptr : NULL, parv[0], "%s", parv[1]);
#ifdef	USE_SERVICES
	check_services_butone(SERVICE_WANT_WALLOP, NULL, sptr,
			      ":%s WALLOP :%s", parv[0], parv[1]);
#endif
	return 2;
}
