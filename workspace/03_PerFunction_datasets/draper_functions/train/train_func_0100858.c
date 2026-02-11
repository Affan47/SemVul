libconf_parse(char *c, off_t len) {
	off_t			off=0;
	char			tb[256];
	int			te, line=1;
	struct lc_centry	*config=NULL,
				*cce=NULL,
				*lce=NULL;

	cce=calloc(1, sizeof(struct lc_centry));
	config=cce;

	while(1) {
		te=gettoken(c, len, tb, &off);

		switch(te) {
			case(TOKEN_NEWLINE):
				line++;
				break;
			case(TOKEN_OBRACKET):
				lce=cce;
				cce=calloc(1, sizeof(struct lc_centry));
				cce->parent=lce;
				lce->child=cce;
				break;
			case(TOKEN_CBRACKET):
				if (!cce->parent) {
					fprintf(stderr, "To many closing brackets in line %d\n", line);
					return NULL;
				}

				if (!cce->token && !cce->value && cce->parent) {

					cce=cce->parent;
					free(cce->child);
					cce->child=NULL;


					break;
				}

				if (!cce->closed) {
					fprintf(stderr, "Token not finished e.g. missing ; in line %d\n", line);
					return NULL;
				}

				cce=cce->parent;
				break;
			case(TOKEN_COLON):

				cce->closed=1;
				break;
			case(TOKEN_STRING):

				if (cce->closed) {
					lce=cce;
					cce=calloc(1, sizeof(struct lc_centry));
					cce->prev=lce;
					lce->next=cce;
					cce->parent=lce->parent;
				}
				if (!cce->token) {
					cce->token=strdup(tb);
					cce->tline=line;
				} else if (!cce->value) {
					cce->value=strdup(tb);
					cce->vline=line;
				} else {
					fprintf(stderr, "Double value for token in line %d\n", line);
					return NULL;
				}
				break;
			case(TOKEN_QSTRING):
				if (!cce || !cce->token) {
					fprintf(stderr, "Quoted token in line %d\n", line);
					return NULL;
				} else if (!cce->value) {
					cce->value=strdup(tb);
					cce->vline=line;
				} else {
					fprintf(stderr, "Double value for token in line %d\n", line);
					return NULL;
				}
				break;
			case(TOKEN_EOF):
				return config;
			default:
				fprintf(stderr, "failed reading config %d\n", te);
				return NULL;
		}
	}


	return NULL;
}
