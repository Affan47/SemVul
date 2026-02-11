tok_list(t)
struct token *t;
{
    register struct token *list = tok_alloc();
    char   *filename;
    int     lineno;


    filename = t->path;
    lineno = t->line;

    list->tokno = TOK_LIST;
    list->head = list->tail = t;
    list->path = t->path;
    list->line = t->line;
#ifdef DEBUG
    strcpy(list->vstr->str, "LIST");
#endif


    while (t = tok_class()) {
	switch (t->tokno) {
	case ')':
	    tok_list_append(list, t);
	    return (list);
	case '{':
	    tok_list_struct(list->tail, t);
	    break;
	case TOK_WSPACE:
	    tok_space_append(list->tail->tail, t);
	    break;
	case '\n':
	    tok_free(t);
	    break;
	case ',':
	    tok_list_append(list, t);
	    break;
	default:
	    tok_list_append(list->tail, t);
	    break;
	}
    }
    error_where(filename, lineno, "unmatched '('");
    return (list);
}
