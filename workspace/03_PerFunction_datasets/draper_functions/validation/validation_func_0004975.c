ap_get_loadavg(ap_loadavg_t *ld)
{

    ld->loadavg = -1.0;
    ld->loadavg5 = -1.0;
    ld->loadavg15 = -1.0;

#if HAVE_GETLOADAVG
    {
        double la[3];
        int num;

        num = getloadavg(la, 3);
        if (num > 0) {
            ld->loadavg = (float)la[0];
        }
        if (num > 1) {
            ld->loadavg5 = (float)la[1];
        }
        if (num > 2) {
            ld->loadavg15 = (float)la[2];
        }
    }
#endif
}
