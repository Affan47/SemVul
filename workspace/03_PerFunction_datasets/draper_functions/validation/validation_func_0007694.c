class_end (CT_ClassDef *cd) {
  enter ();
  assert (cd);

  CClassInfo *ci = (CClassInfo*)cd->Object ()->DefObject ();
  ErrorStream &err = ci->SemDB ()->Project ()->err ();


  Token *inspos = cd->Members ()->end_token ();
  const WeavePos &pos = _code_weaver.weave_pos (inspos, WeavePos::WP_BEFORE);


  insert_introspection_code (cd);


  JPP_Class *jp_plan = plan_lookup (ci);
  if (!jp_plan) {
    leave ();
    return;
  }


  list<Unit*> units;
  LineDirectiveMgr &lmgr = _code_weaver.line_directive_mgr ();
  jp_plan->gen_intros (units, err, ci, lmgr, _conf.introduction_depth ());
  if (units.size () > 0) {

    CTree *tree = parse (units, &CCSyntax::member_spec, CT_MembList::NodeId (), err);
    if (tree) {

	  CT_MembList *memb_list = (CT_MembList*)tree;
	  for (int e = 0; e < memb_list->Entries (); e++) {
	    CTree *entry = memb_list->Entry (e);
	    cd->Members ()->InsertSon (cd->Members ()->Sons () - 1, entry);
  	  }
	  delete memb_list;


	  for (list<Unit*>::iterator ui = units.begin ();
	    ui != units.end (); ++ui)
	    _code_weaver.paste (pos, *ui);
    }
    else {
	  err << sev_error << inspos->location()
		  << "class member introduction into '" << ci->QualName() << "' failed"
		  << endMessage;


	  for (list<Unit*>::iterator ui = units.begin (); ui != units.end (); ++ui)
	    delete *ui;
    }
  }

  leave ();
}
