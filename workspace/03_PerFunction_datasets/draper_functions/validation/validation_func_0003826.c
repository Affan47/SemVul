integratorNew(integrator_ *r, control_ *control, double *ydtdx,
		char units)
{
	ReturnNULLIf(r != NULL);
	ReturnNULLIf(control == NULL);
	ReturnNULLIf(ydtdx == NULL);
	ReturnNULLIf((units != 'A') && (units != 'V') && (units != 'F'));

	r = calloc(1, sizeof(integrator_));
	ReturnNULLIf(r == NULL);

	Debug("Creating NI %p", r);

	r->control = control;
	r->units = units;

	ReturnNULLAndFreeIf(r, integratorInitialize(r, 0.0, ydtdx));

	return r;
}
