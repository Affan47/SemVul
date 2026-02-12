set_conversions(TTY * tty_settings)
{
#ifdef ONLCR
    tty_settings->c_oflag |= ONLCR;
#endif
    tty_settings->c_iflag |= ICRNL;
    tty_settings->c_lflag |= ECHO;
#ifdef OXTABS
    tty_settings->c_oflag |= OXTABS;
#endif


    if (VALID_STRING(newline) && newline[0] == '\n' && !newline[1]) {

#ifdef ONLCR
	tty_settings->c_oflag &= ~((unsigned) ONLCR);
#endif
	tty_settings->c_iflag &= ~((unsigned) ICRNL);
    }
#ifdef OXTABS

    if (VALID_STRING(set_tab) && VALID_STRING(clear_all_tabs))
	tty_settings->c_oflag &= ~OXTABS;
#endif
    tty_settings->c_lflag |= (ECHOE | ECHOK);
}
