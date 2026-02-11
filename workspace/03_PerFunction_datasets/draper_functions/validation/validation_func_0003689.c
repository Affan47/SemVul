restoreopreg()
{
    if (reguse & OPREG)
    {
#ifdef I8088
	outload();
	outregname(OPREG);
	outopsep();
	opregadr();
	outnl();
#endif
#ifdef MC6809
	outload();
	opregadr();
#endif
    }
}
