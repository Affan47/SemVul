reset_body_particulars(BODY_PARTICULARS_S *bp, struct mail_bodystruct *body)
{
    body->type     = bp->type;
    body->encoding = bp->encoding;
    if(body->subtype)
      fs_give((void **)&body->subtype);

    body->subtype  = bp->subtype ? cpystr(bp->subtype) : NULL;

    if(bp->parameter){
	PARAMETER *pm, *pm_prev = NULL;

	for(pm = body->parameter;
	    pm && strucmp(pm->attribute, "charset") != 0;
	    pm = pm->next)
	  pm_prev = pm;

	if(pm){
	    if(bp->had_csp){
		if(pm->value)
		  fs_give((void **)&pm->value);

		pm->value = bp->charset ? cpystr(bp->charset) : NULL;
	    }
	    else{
		if(pm_prev)
		  pm_prev->next = pm->next;
		else
		  body->parameter = pm->next;

		mail_free_body_parameter(&pm);
	    }
	}
	else{
	    if(bp->had_csp){


		q_status_message(SM_ORDER | SM_DING, 5, 5,
"Programmer error: saved charset but no current charset param in pine_send");
	    }


	}
    }
    else{
	if(body->parameter)
	  mail_free_body_parameter(&body->parameter);

	body->parameter = NULL;
    }
}
