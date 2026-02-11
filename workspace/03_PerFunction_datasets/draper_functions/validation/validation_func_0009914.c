parseLogEntry(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur,
	               struct log_entry_struct *log)
{
  int return_status = REG_SUCCESS;

  if(!log) return REG_FAILURE;

  cur = cur->xmlChildrenNode;
  while (cur != NULL) {

    if( !xmlStrcmp(cur->name, (const xmlChar *)"Key") ){


      log->key = xmlNodeListGetString(doc,
				      cur->xmlChildrenNode, 1);
    }
    else if( !xmlStrcmp(cur->name, (const xmlChar *)"Chk_log_entry") ){

      if(!log->first_chk_log){

	log->first_chk_log = New_chk_log_entry_struct();
	log->chk_log = log->first_chk_log;
      }
      else{
	log->chk_log->next = New_chk_log_entry_struct();
	log->chk_log = log->chk_log->next;
      }
#ifdef REG_DEBUG
      fprintf(stderr, "STEER: parseLogEntry: calling parseChkLogEntry\n");
#endif
      return_status = parseChkLogEntry(doc, ns, cur, log->chk_log);
    }
    else if( !xmlStrcmp(cur->name, (const xmlChar *)"Param") ){

      if(!log->first_param_log){

	log->first_param_log = New_param_struct();
	log->param_log = log->first_param_log;
      }
      else{
	log->param_log->next = New_param_struct();
	log->param_log = log->param_log->next;
      }

#ifdef REG_DEBUG
      fprintf(stderr, "STEER: parseLogEntry: calling parseParam\n");
#endif
      return_status = parseParam(doc, ns, cur, log->param_log);
    }

    cur = cur->next;
  }
  return return_status;
}
