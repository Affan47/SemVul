bringSlavesUpToMin(EventSelector *es,
		   int fd,
		   unsigned int flags,
		   void *data)
{
    Slave *s;
    char reason[200];

    minScheduled = 0;

    if (NUM_RUNNING_SLAVES >= Settings.minSlaves) {

	return;
    }


    s = Slaves[STATE_STOPPED];
    if (s) {
	snprintf(reason, sizeof(reason),
		 "Bringing slaves up to minSlaves (%d)", Settings.minSlaves);
	if (activateSlave(s, reason) >= 0) {


	}
    }


    if (NUM_RUNNING_SLAVES < Settings.minSlaves) {
	scheduleBringSlavesUpToMin(es);
    }
}
