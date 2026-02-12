typeset(const char *var, uint32_t set, uint32_t clr, int field, int base)
{
	struct tbl *vp;
	struct tbl *vpbase, *t;
	char *tvar;
	const char *val;
	size_t len;
	bool vappend = false;
	enum namerefflag new_refflag = SRF_NOP;

	if ((set & (ARRAY | ASSOC)) == ASSOC) {
		new_refflag = SRF_ENABLE;
		set &= ~(ARRAY | ASSOC);
	}
	if ((clr & (ARRAY | ASSOC)) == ASSOC) {
		new_refflag = SRF_DISABLE;
		clr &= ~(ARRAY | ASSOC);
	}


	val = skip_varname(var, false);
	if (val == var) {

		return (NULL);
	}
	if (*val == '[') {
		if (new_refflag != SRF_NOP)
			errorf("%s: %s", var,
			    "reference variable can't be an array");
		len = array_ref_len(val);
		if (len == 0)
			return (NULL);


		if (set & IMPORT) {
			size_t i;

			for (i = 1; i < len - 1; i++)
				if (!ksh_isdigit(val[i]))
					return (NULL);
		}
		val += len;
	}
	if (val[0] == '=') {
		strndupx(tvar, var, val - var, ATEMP);
		++val;
	} else if (set & IMPORT) {

		return (NULL);
	} else if (val[0] == '+' && val[1] == '=') {
		strndupx(tvar, var, val - var, ATEMP);
		val += 2;
		vappend = true;
	} else if (val[0] != '\0') {

		return (NULL);
	} else {

		strdupx(tvar, var, ATEMP);
		val = NULL;

		len = strlen(tvar);
		if (len > 3 && tvar[len - 3] == '[' && tvar[len - 2] == '*' &&
		    tvar[len - 1] == ']')
			tvar[len - 3] = '\0';
	}

	if (new_refflag == SRF_ENABLE) {
		const char *qval, *ccp;


		if (vappend)
			errorf("appending not allowed for nameref");

		if ((qval = val) == NULL) {
			varsearch(e->loc, &vp, tvar, hash(tvar));
			if (vp != NULL)
				qval = str_val(vp);
		}

		ccp = skip_varname(qval, false);
		if (ccp == qval) {
			if (ksh_isdigit(qval[0])) {
				int c;

				if (getn(qval, &c))
					goto nameref_rhs_checked;
			} else if (qval[1] == '\0') switch (qval[0]) {
			case '$':
			case '!':
			case '?':
			case '#':
			case '-':
				goto nameref_rhs_checked;
			}
			errorf("%s: %s", var, "empty nameref target");
		}
		len = (*ccp == '[') ? array_ref_len(ccp) : 0;
		if (ccp[len]) {


			errorf("%s: %s", qval,
			    "nameref target not a valid parameter name");
		}
 nameref_rhs_checked:

		while (qval) {
			if (!strcmp(qval, tvar))
				errorf("%s: %s", qval,
				    "expression recurses on parameter");
			varsearch(e->loc, &vp, qval, hash(qval));
			qval = NULL;
			if (vp && ((vp->flag & (ARRAY | ASSOC)) == ASSOC))
				qval = str_val(vp);
		}
	}


	if (Flag(FRESTRICTED) && (strcmp(tvar, "PATH") == 0 ||
	    strcmp(tvar, "ENV") == 0 || strcmp(tvar, "SHELL") == 0))
		errorf("%s: %s", tvar, "restricted");

	innermost_refflag = new_refflag;
	vp = (set & LOCAL) ? local(tvar, tobool(set & LOCAL_COPY)) :
	    global(tvar);
	if (new_refflag == SRF_DISABLE && (vp->flag & (ARRAY|ASSOC)) == ASSOC)
		vp->flag &= ~ASSOC;
	else if (new_refflag == SRF_ENABLE) {
		if (vp->flag & ARRAY) {
			struct tbl *a, *tmp;


			for (a = vp->u.array; a; ) {
				tmp = a;
				a = a->u.array;
				if (tmp->flag & ALLOC)
					afree(tmp->val.s, tmp->areap);
				afree(tmp, tmp->areap);
			}
			vp->u.array = NULL;
			vp->flag &= ~ARRAY;
		}
		vp->flag |= ASSOC;
	}

	set &= ~(LOCAL|LOCAL_COPY);

	vpbase = (vp->flag & ARRAY) ? global(arrayname(tvar)) : vp;


	if ((vpbase->flag & RDONLY) &&
	    (val || clr || (set & ~EXPORT)))

		errorfx(2, "read-only: %s", tvar);
	afree(tvar, ATEMP);


	if (set | clr) {
		bool ok = true;


		for (t = vpbase; t; t = t->u.array) {
			bool fake_assign;
			char *s = NULL;
			char *free_me = NULL;

			fake_assign = (t->flag & ISSET) && (!val || t != vp) &&
			    ((set & (UCASEV_AL|LCASEV|LJUST|RJUST|ZEROFIL)) ||
			    ((t->flag & INTEGER) && (clr & INTEGER)) ||
			    (!(t->flag & INTEGER) && (set & INTEGER)));
			if (fake_assign) {
				if (t->flag & INTEGER) {
					s = str_val(t);
					free_me = NULL;
				} else {
					s = t->val.s + t->type;
					free_me = (t->flag & ALLOC) ? t->val.s :
					    NULL;
				}
				t->flag &= ~ALLOC;
			}
			if (!(t->flag & INTEGER) && (set & INTEGER)) {
				t->type = 0;
				t->flag &= ~ALLOC;
			}
			t->flag = (t->flag | set) & ~clr;


			if ((set & INTEGER) && base > 0 && (!val || t != vp))
				t->type = base;
			if (set & (LJUST|RJUST|ZEROFIL))
				t->u2.field = field;
			if (fake_assign) {
				if (!setstr(t, s, KSH_RETURN_ERROR)) {


					ok = false;
					if (t->flag & INTEGER)
						t->flag &= ~ISSET;
					else {
						if (t->flag & ALLOC)
							afree(t->val.s, t->areap);
						t->flag &= ~(ISSET|ALLOC);
						t->type = 0;
					}
				}
				if (free_me)
					afree(free_me, t->areap);
			}
		}
		if (!ok)
			errorfz();
	}

	if (val != NULL) {
		char *tval;

		if (vappend) {
			tval = shf_smprintf("%s%s", str_val(vp), val);
			val = tval;
		} else
			tval = NULL;

		if (vp->flag&INTEGER) {

			setstr(vp, val, KSH_UNWIND_ERROR | 0x4);

			if (base > 0)
				vp->type = base;
		} else

			setstr(vp, val, KSH_RETURN_ERROR | 0x4);

		if (tval != NULL)
			afree(tval, ATEMP);
	}


	if ((vpbase->flag&EXPORT) && !(vpbase->flag&INTEGER) &&
	    vpbase->type == 0)
		exportprep(vpbase, (vpbase->flag&ISSET) ? vpbase->val.s : null);

	return (vp);
}
