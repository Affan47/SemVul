tree_subj_time_comp(struct mailmessage_tree ** ptree1,
			       struct mailmessage_tree ** ptree2)
{
  char * subj1;
  char * subj2;
  time_t date1;
  time_t date2;
  int r;

  subj1 = (* ptree1)->node_base_subject;
  subj2 = (* ptree2)->node_base_subject;

  if ((subj1 != NULL) && (subj2 != NULL))
    r = strcmp(subj1, subj2);
  else {
    if ((subj1 == NULL) && (subj2 == NULL))
      r = 0;
    else if (subj1 == NULL)
      r = -1;
    else
      r = 1;
  }

  if (r != 0)
    return r;

  date1 = (* ptree1)->node_date;
  date2 = (* ptree2)->node_date;

  if ((date1 == (time_t) -1) || (date2 == (time_t) -1))
    return ((int32_t) (* ptree1)->node_msg->msg_index) -
      ((int32_t) (* ptree2)->node_msg->msg_index);

  return (int) ((long) date1 - (long) date2);
}
