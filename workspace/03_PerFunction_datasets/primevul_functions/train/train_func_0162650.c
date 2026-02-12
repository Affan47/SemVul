xmlFAComputesDeterminism(xmlRegParserCtxtPtr ctxt) {
    int statenr, transnr;
    xmlRegStatePtr state;
    xmlRegTransPtr t1, t2, last;
    int i;
    int ret = 1;
    int deep = 1;

#ifdef DEBUG_REGEXP_GRAPH
    printf("xmlFAComputesDeterminism\n");
    xmlRegPrintCtxt(stdout, ctxt);
#endif
    if (ctxt->determinist != -1)
	return(ctxt->determinist);

    if (ctxt->flags & AM_AUTOMATA_RNG)
        deep = 0;


    for (statenr = 0;statenr < ctxt->nbStates;statenr++) {
	state = ctxt->states[statenr];
	if (state == NULL)
	    continue;
	if (state->nbTrans < 2)
	    continue;
	for (transnr = 0;transnr < state->nbTrans;transnr++) {
	    t1 = &(state->trans[transnr]);


	    if (t1->atom == NULL) {

		continue;
	    }
	    if (t1->to == -1)
		continue;
	    for (i = 0;i < transnr;i++) {
		t2 = &(state->trans[i]);
		if (t2->to == -1)
		    continue;
		if (t2->atom != NULL) {
		    if (t1->to == t2->to) {


			if (xmlFAEqualAtoms(t1->atom, t2->atom, deep) &&
                            (t1->counter == t2->counter) &&
                            (t1->count == t2->count))
			    t2->to = -1;
		    }
		}
	    }
	}
    }


    for (statenr = 0;statenr < ctxt->nbStates;statenr++) {
	state = ctxt->states[statenr];
	if (state == NULL)
	    continue;
	if (state->nbTrans < 2)
	    continue;
	last = NULL;
	for (transnr = 0;transnr < state->nbTrans;transnr++) {
	    t1 = &(state->trans[transnr]);


	    if (t1->atom == NULL) {
		continue;
	    }
	    if (t1->to == -1)
		continue;
	    for (i = 0;i < transnr;i++) {
		t2 = &(state->trans[i]);
		if (t2->to == -1)
		    continue;
		if (t2->atom != NULL) {


		    if (xmlFACompareAtoms(t1->atom, t2->atom, 1)) {
			ret = 0;

			t1->nd = 1;
			t2->nd = 1;
			last = t1;
		    }
		} else if (t1->to != -1) {


		    ret = xmlFARecurseDeterminism(ctxt, ctxt->states[t1->to],
						   t2->to, t2->atom);


		    if (ret == 0) {
			t1->nd = 1;

			last = t1;
		    }
		}
	    }


	}


	if (last != NULL) {
	    last->nd = 2;
	}


    }

    ctxt->determinist = ret;
    return(ret);
}
