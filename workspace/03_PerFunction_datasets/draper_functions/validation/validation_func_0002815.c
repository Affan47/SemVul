deviceClassStep(device_ *r, int *breakPoint)
{
	devicePrivate_ *p;
	ReturnErrIf(r == NULL);
	p = r->private;
	ReturnErrIf(p == NULL);

	if(p->time != NULL) {
		Debug("Stepping %s %s %p", r->class->type, r->refdes, r);

		ReturnErrIf(deviceCallbackCalculate(p));
		ReturnErrIf(deviceCallbackLoad(p));


		*breakPoint = checkbreakIsBreak(p->checkbreak, p->Veq);
		ReturnErrIf(*breakPoint < 0);
	}

	return 0;
}
