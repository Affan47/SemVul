sub_write_patterns(long int rflags)
{
    int            err = 0, lineno = 0;
    char         **lvalue = NULL;
    PAT_LINE_S    *patline;

    SET_PATTYPE(rflags);

    if(!(*cur_pat_h)){
	q_status_message(SM_ORDER | SM_DING, 3, 4,
			  "Unknown error saving patterns");
	return(-1);
    }

    if((*cur_pat_h)->dirtypinerc){

	for(patline = (*cur_pat_h)->patlinehead;
	    patline;
	    patline = patline->next)
	  lineno++;

	lvalue = (char **)fs_get((lineno+1)*sizeof(char *));
	memset(lvalue, 0, (lineno+1) * sizeof(char *));
    }

    for(patline = (*cur_pat_h)->patlinehead, lineno = 0;
	!err && patline;
	patline = patline->next, lineno++){
	if(patline->type == File)
	  err = write_pattern_file((*cur_pat_h)->dirtypinerc
				      ? &lvalue[lineno] : NULL, patline);
	else if(patline->type == Literal && (*cur_pat_h)->dirtypinerc)
	  err = write_pattern_lit(&lvalue[lineno], patline);
	else if(patline->type == Inherit)
	  err = write_pattern_inherit((*cur_pat_h)->dirtypinerc
				      ? &lvalue[lineno] : NULL, patline);
    }

    if((*cur_pat_h)->dirtypinerc){
	if(err)
	  free_list_array(&lvalue);
	else{
	    char ***alval;
	    struct variable *var;

	    if(rflags & ROLE_DO_ROLES)
	      var = &ps_global->vars[V_PAT_ROLES];
	    else if(rflags & ROLE_DO_OTHER)
	      var = &ps_global->vars[V_PAT_OTHER];
	    else if(rflags & ROLE_DO_FILTER)
	      var = &ps_global->vars[V_PAT_FILTS];
	    else if(rflags & ROLE_DO_SCORES)
	      var = &ps_global->vars[V_PAT_SCORES];
	    else if(rflags & ROLE_DO_INCOLS)
	      var = &ps_global->vars[V_PAT_INCOLS];
	    else if(rflags & ROLE_DO_SRCH)
	      var = &ps_global->vars[V_PAT_SRCH];

	    alval = (rflags & PAT_USE_CHANGED) ? &(var->changed_val.l)
	      : ALVAL(var, (rflags & PAT_USE_MAIN) ? Main : Post);
	    if(*alval)
	      free_list_array(alval);

	    if(rflags & PAT_USE_CHANGED) var->is_changed_val = 1;

	    *alval = lvalue;

	    if(!(rflags & PAT_USE_CHANGED))
	      set_current_val(var, TRUE, TRUE);
	}
    }

    if(!err)
      (*cur_pat_h)->dirtypinerc = 0;

    return(err);
}
