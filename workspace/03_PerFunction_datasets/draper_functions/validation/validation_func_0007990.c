imap_body_parameter_to_content(struct mailimap_body_fld_param *
			       body_parameter,
			       char * subtype,
			       struct mailmime_type * mime_type,
			       struct mailmime_content ** result)
{
  clist * parameters;
  char * new_subtype;
  struct mailmime_content * content;
  int r;
  int res;

  new_subtype = strdup(subtype);
  if (new_subtype == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto err;
  }

  parameters = clist_new();
  if (parameters == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto free_subtype;
  }

  if (body_parameter != NULL) {
    clistiter * cur;

    for(cur = clist_begin(body_parameter->pa_list) ; cur != NULL ;
	cur = clist_next(cur)) {
      struct mailimap_single_body_fld_param * imap_param;
      struct mailmime_parameter * param;
      char * name;
      char * value;

      imap_param = clist_content(cur);
      name = strdup(imap_param->pa_name);
      if (name == NULL) {
	res = MAIL_ERROR_MEMORY;
	goto free_parameters;
      }

      value = strdup(imap_param->pa_value);
      if (value == NULL) {
	free(name);
	res = MAIL_ERROR_MEMORY;
	goto free_parameters;
      }

      param = mailmime_parameter_new(name, value);
      if (param == NULL) {
	free(value);
	free(name);
	res = MAIL_ERROR_MEMORY;
	goto free_parameters;
      }

      r = clist_append(parameters, param);
      if (r != 0) {
	mailmime_parameter_free(param);
	res = MAIL_ERROR_MEMORY;
	goto free_parameters;
      }
    }
  }

  content = mailmime_content_new(mime_type, new_subtype, parameters);
  if (content == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto free_parameters;
  }

  * result = content;

  return MAIL_NO_ERROR;

 free_parameters:
  clist_foreach(parameters, (clist_func) mailmime_parameter_free, NULL);
  clist_free(parameters);
 free_subtype:
  free(new_subtype);
 err:
  return res;
}
