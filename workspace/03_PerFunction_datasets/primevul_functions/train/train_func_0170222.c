static int asn1_item_embed_d2i(ASN1_VALUE **pval, const unsigned char **in,
                               long len, const ASN1_ITEM *it,
                               int tag, int aclass, char opt, ASN1_TLC *ctx,
                               int depth)
{
    const ASN1_TEMPLATE *tt, *errtt = NULL;
    const ASN1_EXTERN_FUNCS *ef;
    const ASN1_AUX *aux = it->funcs;
    ASN1_aux_cb *asn1_cb;
    const unsigned char *p = NULL, *q;
    unsigned char oclass;
    char seq_eoc, seq_nolen, cst, isopt;
    long tmplen;
    int i;
    int otag;
    int ret = 0;
    ASN1_VALUE **pchptr;

    if (pval == NULL)
        return 0;
    if (aux && aux->asn1_cb)
        asn1_cb = aux->asn1_cb;
    else
        asn1_cb = 0;

    if (++depth > ASN1_MAX_CONSTRUCTED_NEST) {
        ERR_raise(ERR_LIB_ASN1, ASN1_R_NESTED_TOO_DEEP);
        goto err;
    }

    switch (it->itype) {
    case ASN1_ITYPE_PRIMITIVE:
        if (it->templates) {


            if ((tag != -1) || opt) {
                ERR_raise(ERR_LIB_ASN1,
                          ASN1_R_ILLEGAL_OPTIONS_ON_ITEM_TEMPLATE);
                goto err;
            }
            return asn1_template_ex_d2i(pval, in, len,
                                        it->templates, opt, ctx, depth);
        }
        return asn1_d2i_ex_primitive(pval, in, len, it,
                                     tag, aclass, opt, ctx);

    case ASN1_ITYPE_MSTRING:


        if (tag != -1) {
            ERR_raise(ERR_LIB_ASN1, ASN1_R_BAD_TEMPLATE);
            goto err;
        }

        p = *in;

        ret = asn1_check_tlen(NULL, &otag, &oclass, NULL, NULL,
                              &p, len, -1, 0, 1, ctx);
        if (!ret) {
            ERR_raise(ERR_LIB_ASN1, ERR_R_NESTED_ASN1_ERROR);
            goto err;
        }


        if (oclass != V_ASN1_UNIVERSAL) {

            if (opt)
                return -1;
            ERR_raise(ERR_LIB_ASN1, ASN1_R_MSTRING_NOT_UNIVERSAL);
            goto err;
        }


        if (!(ASN1_tag2bit(otag) & it->utype)) {

            if (opt)
                return -1;
            ERR_raise(ERR_LIB_ASN1, ASN1_R_MSTRING_WRONG_TAG);
            goto err;
        }
        return asn1_d2i_ex_primitive(pval, in, len, it, otag, 0, 0, ctx);

    case ASN1_ITYPE_EXTERN:

        ef = it->funcs;
        return ef->asn1_ex_d2i(pval, in, len, it, tag, aclass, opt, ctx);

    case ASN1_ITYPE_CHOICE:


        if (tag != -1) {
            ERR_raise(ERR_LIB_ASN1, ASN1_R_BAD_TEMPLATE);
            goto err;
        }

        if (asn1_cb && !asn1_cb(ASN1_OP_D2I_PRE, pval, it, NULL))
            goto auxerr;
        if (*pval) {

            i = asn1_get_choice_selector(pval, it);
            if ((i >= 0) && (i < it->tcount)) {
                tt = it->templates + i;
                pchptr = asn1_get_field_ptr(pval, tt);
                asn1_template_free(pchptr, tt);
                asn1_set_choice_selector(pval, -1, it);
            }
        } else if (!ASN1_item_ex_new(pval, it)) {
            ERR_raise(ERR_LIB_ASN1, ERR_R_NESTED_ASN1_ERROR);
            goto err;
        }

        p = *in;
        for (i = 0, tt = it->templates; i < it->tcount; i++, tt++) {
            pchptr = asn1_get_field_ptr(pval, tt);


            ret = asn1_template_ex_d2i(pchptr, &p, len, tt, 1, ctx, depth);

            if (ret == -1)
                continue;

            if (ret > 0)
                break;


            asn1_template_free(pchptr, tt);
            errtt = tt;
            ERR_raise(ERR_LIB_ASN1, ERR_R_NESTED_ASN1_ERROR);
            goto err;
        }


        if (i == it->tcount) {

            if (opt) {

                ASN1_item_ex_free(pval, it);
                return -1;
            }
            ERR_raise(ERR_LIB_ASN1, ASN1_R_NO_MATCHING_CHOICE_TYPE);
            goto err;
        }

        asn1_set_choice_selector(pval, i, it);

        if (asn1_cb && !asn1_cb(ASN1_OP_D2I_POST, pval, it, NULL))
            goto auxerr;
        *in = p;
        return 1;

    case ASN1_ITYPE_NDEF_SEQUENCE:
    case ASN1_ITYPE_SEQUENCE:
        p = *in;
        tmplen = len;


        if (tag == -1) {
            tag = V_ASN1_SEQUENCE;
            aclass = V_ASN1_UNIVERSAL;
        }

        ret = asn1_check_tlen(&len, NULL, NULL, &seq_eoc, &cst,
                              &p, len, tag, aclass, opt, ctx);
        if (!ret) {
            ERR_raise(ERR_LIB_ASN1, ERR_R_NESTED_ASN1_ERROR);
            goto err;
        } else if (ret == -1)
            return -1;
        if (aux && (aux->flags & ASN1_AFLG_BROKEN)) {
            len = tmplen - (p - *in);
            seq_nolen = 1;
        }

        else
            seq_nolen = seq_eoc;
        if (!cst) {
            ERR_raise(ERR_LIB_ASN1, ASN1_R_SEQUENCE_NOT_CONSTRUCTED);
            goto err;
        }

        if (*pval == NULL && !ASN1_item_ex_new(pval, it)) {
            ERR_raise(ERR_LIB_ASN1, ERR_R_NESTED_ASN1_ERROR);
            goto err;
        }

        if (asn1_cb && !asn1_cb(ASN1_OP_D2I_PRE, pval, it, NULL))
            goto auxerr;


        for (i = 0, tt = it->templates; i < it->tcount; i++, tt++) {
            if (tt->flags & ASN1_TFLG_ADB_MASK) {
                const ASN1_TEMPLATE *seqtt;
                ASN1_VALUE **pseqval;
                seqtt = asn1_do_adb(*pval, tt, 0);
                if (seqtt == NULL)
                    continue;
                pseqval = asn1_get_field_ptr(pval, seqtt);
                asn1_template_free(pseqval, seqtt);
            }
        }


        for (i = 0, tt = it->templates; i < it->tcount; i++, tt++) {
            const ASN1_TEMPLATE *seqtt;
            ASN1_VALUE **pseqval;
            seqtt = asn1_do_adb(*pval, tt, 1);
            if (seqtt == NULL)
                goto err;
            pseqval = asn1_get_field_ptr(pval, seqtt);

            if (!len)
                break;
            q = p;
            if (asn1_check_eoc(&p, len)) {
                if (!seq_eoc) {
                    ERR_raise(ERR_LIB_ASN1, ASN1_R_UNEXPECTED_EOC);
                    goto err;
                }
                len -= p - q;
                seq_eoc = 0;
                break;
            }


            if (i == (it->tcount - 1))
                isopt = 0;
            else
                isopt = (char)(seqtt->flags & ASN1_TFLG_OPTIONAL);


            ret = asn1_template_ex_d2i(pseqval, &p, len, seqtt, isopt, ctx,
                                       depth);
            if (!ret) {
                errtt = seqtt;
                goto err;
            } else if (ret == -1) {


                asn1_template_free(pseqval, seqtt);
                continue;
            }

            len -= p - q;
        }


        if (seq_eoc && !asn1_check_eoc(&p, len)) {
            ERR_raise(ERR_LIB_ASN1, ASN1_R_MISSING_EOC);
            goto err;
        }

        if (!seq_nolen && len) {
            ERR_raise(ERR_LIB_ASN1, ASN1_R_SEQUENCE_LENGTH_MISMATCH);
            goto err;
        }


        for (; i < it->tcount; tt++, i++) {
            const ASN1_TEMPLATE *seqtt;
            seqtt = asn1_do_adb(*pval, tt, 1);
            if (seqtt == NULL)
                goto err;
            if (seqtt->flags & ASN1_TFLG_OPTIONAL) {
                ASN1_VALUE **pseqval;
                pseqval = asn1_get_field_ptr(pval, seqtt);
                asn1_template_free(pseqval, seqtt);
            } else {
                errtt = seqtt;
                ERR_raise(ERR_LIB_ASN1, ASN1_R_FIELD_MISSING);
                goto err;
            }
        }

        if (!asn1_enc_save(pval, *in, p - *in, it))
            goto auxerr;
        if (asn1_cb && !asn1_cb(ASN1_OP_D2I_POST, pval, it, NULL))
            goto auxerr;
        *in = p;
        return 1;

    default:
        return 0;
    }
 auxerr:
    ERR_raise(ERR_LIB_ASN1, ASN1_R_AUX_ERROR);
 err:
    if (errtt)
        ERR_add_error_data(4, "Field=", errtt->field_name,
                           ", Type=", it->sname);
    else
        ERR_add_error_data(2, "Type=", it->sname);
    return 0;
}
