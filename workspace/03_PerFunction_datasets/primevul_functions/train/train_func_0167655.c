static bool tnt_speed(struct gps_device_t *session,
		      speed_t speed, char parity UNUSED, int stopbits UNUSED)
{


    unsigned int val = speed / 2400u;
    unsigned int i = 0;


    while ((val >> i) > 1)
	++i;
    return tnt_send(session, "@B6=%d", i + 1)
	&& tnt_send(session, "@F28.6=1");
}
