godfrey_test_string (int ci, int order, PRN *prn)
{
    pputc(prn, '\n');

    if (ci == IVREG) {
	if (order > 1) {
	    pprintf(prn, A_("Godfrey (1994) test for autocorrelation up to order %d"),
		    order);
	} else {
	    pputs(prn, A_("Godfrey (1994) test for first-order autocorrelation"));
	}
    } else {
	if (order > 1) {
	    pprintf(prn, A_("Breusch-Godfrey test for autocorrelation up to order %d"),
		    order);
	} else {
	    pputs(prn, A_("Breusch-Godfrey test for first-order autocorrelation"));
	}
    }

    pputc(prn, '\n');
}
