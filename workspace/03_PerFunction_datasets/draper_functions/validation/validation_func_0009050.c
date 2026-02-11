xover_resp_item_new(uint32_t article,
		    char * subject,
		    char * author,
		    char * date,
		    char * message_id,
		    char * references,
		    size_t size,
		    uint32_t line_count,
		    clist * others)
{
  struct newsnntp_xover_resp_item * n;

  n = malloc(sizeof(* n));
  if (n == NULL)
    return NULL;

  n->ovr_subject = strdup(subject);
  if (n->ovr_subject == NULL) {
    free(n);
    return NULL;
  }

  n->ovr_author = strdup(author);
  if (n->ovr_author == NULL) {
    free(n->ovr_subject);
    free(n);
    return NULL;
  }

  n->ovr_date = strdup(date);
  if (n->ovr_date == NULL) {
    free(n->ovr_subject);
    free(n->ovr_author);
    free(n);
    return NULL;
  }

  n->ovr_message_id = strdup(message_id);
  if (n->ovr_message_id == NULL) {
    free(n->ovr_subject);
    free(n->ovr_author);
    free(n->ovr_date);
    free(n);
    return NULL;
  }

  n->ovr_references = strdup(references);
  if (n->ovr_references == NULL) {
    free(n->ovr_subject);
    free(n->ovr_author);
    free(n->ovr_date);
    free(n->ovr_message_id);
    free(n);
    return NULL;
  }

  n->ovr_article = article;
  n->ovr_size = size;
  n->ovr_line_count = line_count;
  n->ovr_others = others;

  return n;
}
