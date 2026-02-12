void *
Perl_regdupe_internal(pTHX_ REGEXP * const rx, CLONE_PARAMS *param)
{
    dVAR;
    struct regexp *const r = ReANY(rx);
    regexp_internal *reti;
    int len;
    RXi_GET_DECL(r, ri);

    PERL_ARGS_ASSERT_REGDUPE_INTERNAL;

    len = ProgLen(ri);

    Newxc(reti, sizeof(regexp_internal) + len*sizeof(regnode),
          char, regexp_internal);
    Copy(ri->program, reti->program, len+1, regnode);


    if (ri->code_blocks) {
	int n;
	Newx(reti->code_blocks, 1, struct reg_code_blocks);
	Newx(reti->code_blocks->cb, ri->code_blocks->count,
                    struct reg_code_block);
	Copy(ri->code_blocks->cb, reti->code_blocks->cb,
             ri->code_blocks->count, struct reg_code_block);
	for (n = 0; n < ri->code_blocks->count; n++)
	     reti->code_blocks->cb[n].src_regex = (REGEXP*)
		    sv_dup_inc((SV*)(ri->code_blocks->cb[n].src_regex), param);
        reti->code_blocks->count = ri->code_blocks->count;
        reti->code_blocks->refcnt = 1;
    }
    else
	reti->code_blocks = NULL;

    reti->regstclass = NULL;

    if (ri->data) {
	struct reg_data *d;
        const int count = ri->data->count;
	int i;

	Newxc(d, sizeof(struct reg_data) + count*sizeof(void *),
		char, struct reg_data);
	Newx(d->what, count, U8);

	d->count = count;
	for (i = 0; i < count; i++) {
	    d->what[i] = ri->data->what[i];
	    switch (d->what[i]) {

            case 'a':

            case 'r':
            case 's':


            case 'S':
            case 'u':

		d->data[i] = sv_dup_inc((const SV *)ri->data->data[i], param);
		break;
	    case 'f':


		Newx(d->data[i], 1, regnode_ssc);
		StructCopy(ri->data->data[i], d->data[i], regnode_ssc);
		reti->regstclass = (regnode*)d->data[i];
		break;
	    case 'T':


		reti->regstclass= ri->regstclass;

	    case 't':

		OP_REFCNT_LOCK;
		((reg_trie_data*)ri->data->data[i])->refcount++;
		OP_REFCNT_UNLOCK;

            case 'l':
            case 'L':

		d->data[i] = ri->data->data[i];
		break;
            default:
                Perl_croak(aTHX_ "panic: re_dup_guts unknown data code '%c'",
                                                           ri->data->what[i]);
	    }
	}

	reti->data = d;
    }
    else
	reti->data = NULL;

    reti->name_list_idx = ri->name_list_idx;

#ifdef RE_TRACK_PATTERN_OFFSETS
    if (ri->u.offsets) {
        Newx(reti->u.offsets, 2*len+1, U32);
        Copy(ri->u.offsets, reti->u.offsets, 2*len+1, U32);
    }
#else
    SetProgLen(reti, len);
#endif

    return (void*)reti;
}
