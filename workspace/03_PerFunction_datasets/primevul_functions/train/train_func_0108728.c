return_padata(krb5_context context, krb5_kdcpreauth_rock rock,
              krb5_data *req_pkt, krb5_kdc_req *request, krb5_kdc_rep *reply,
              krb5_keyblock *encrypting_key, void **padata_context)
{
    krb5_error_code             retval;
    krb5_pa_data **             padata;
    krb5_pa_data **             send_pa_list = NULL;
    krb5_pa_data *              send_pa;
    krb5_pa_data *              pa = 0;
    krb5_pa_data null_item;
    preauth_system *            ap;
    int *                       pa_order = NULL;
    int *                       pa_type;
    int                         size = 0;
    krb5_kdcpreauth_modreq      *modreq_ptr;
    krb5_boolean                key_modified;
    krb5_keyblock               original_key;

    memset(&original_key, 0, sizeof(original_key));

    if ((!*padata_context) &&
        (make_padata_context(context, padata_context) != 0)) {
        return KRB5KRB_ERR_GENERIC;
    }

    for (ap = preauth_systems; ap->type != -1; ap++) {
        if (ap->return_padata)
            size++;
    }

    pa_order = k5calloc(size + 1, sizeof(int), &retval);
    if (pa_order == NULL)
        goto cleanup;
    sort_pa_order(context, request, pa_order);

    retval = krb5_copy_keyblock_contents(context, encrypting_key,
                                         &original_key);
    if (retval)
        goto cleanup;
    key_modified = FALSE;
    null_item.contents = NULL;
    null_item.length = 0;

    for (pa_type = pa_order; *pa_type != -1; pa_type++) {
        ap = &preauth_systems[*pa_type];
        if (key_modified && (ap->flags & PA_REPLACES_KEY))
            continue;
        if (ap->return_padata == 0)
            continue;
        if (find_modreq(ap, *padata_context, &modreq_ptr))
            continue;
        pa = &null_item;
        null_item.pa_type = ap->type;
        if (request->padata) {
            for (padata = request->padata; *padata; padata++) {
                if ((*padata)->pa_type == ap->type) {
                    pa = *padata;
                    break;
                }
            }
        }
        send_pa = NULL;
        retval = ap->return_padata(context, pa, req_pkt, request, reply,
                                   encrypting_key, &send_pa, &callbacks, rock,
                                   ap->moddata, *modreq_ptr);
        if (retval)
            goto cleanup;

        if (send_pa != NULL) {

            retval = add_pa_data_element(&send_pa_list, send_pa);
            if (retval)
                goto cleanup;
        }

        if (!key_modified && !keyblock_equal(&original_key, encrypting_key))
            key_modified = TRUE;
    }


    if (!key_modified) {
        retval = add_etype_info(context, rock, &send_pa_list);
        if (retval)
            goto cleanup;
        retval = add_pw_salt(context, rock, &send_pa_list);
        if (retval)
            goto cleanup;
    }

    if (send_pa_list != NULL) {
        reply->padata = send_pa_list;
        send_pa_list = 0;
    }

cleanup:
    krb5_free_keyblock_contents(context, &original_key);
    free(pa_order);
    krb5_free_pa_data(context, send_pa_list);

    return (retval);
}
