ex_write(exarg_T *eap)
{
    if (eap->cmdidx == CMD_saveas)
    {

	eap->line1 = 1;
	eap->line2 = curbuf->b_ml.ml_line_count;
    }

    if (eap->usefilter)
	do_bang(1, eap, FALSE, TRUE, FALSE);
    else
	(void)do_write(eap);
}
