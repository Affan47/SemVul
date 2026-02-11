deviceClassStep(device_ *r, int *breakPoint)
{
	devicePrivate_ *p;
	double dc;
	ReturnErrIf(r == NULL);
	p = r->private;
	ReturnErrIf(p == NULL);

	if(p->waveform != NULL) {

		Debug("Stepping %s %s %p", r->class->type, r->refdes, r);

		ReturnErrIf(waveformCalcValue(p->waveform, &dc));

		ReturnErrIf(rowRHSPlus(p->rowK, -(dc - p->dc)));
		ReturnErrIf(rowRHSPlus(p->rowJ, dc - p->dc));
		p->dc = dc;


		*breakPoint = checkbreakIsBreak(p->checkbreak, dc);
		ReturnErrIf(*breakPoint < 0);
	}

	return 0;
}
