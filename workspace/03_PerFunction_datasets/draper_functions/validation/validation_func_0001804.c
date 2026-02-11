_disco_items_result(module_t mod, disco_t d) {
    pkt_t pkt;
    int ns;
    service_t svc;
    union xhashv xhv;

    pkt = pkt_create(mod->mm->sm, "iq", "result", NULL, NULL);
    ns = nad_add_namespace(pkt->nad, uri_DISCO_ITEMS, NULL);
    nad_append_elem(pkt->nad, ns, "query", 2);

    if(xhash_iter_first(d->un))
        do {
            xhv.svc_val = &svc;
            xhash_iter_get(d->un, NULL, NULL, xhv.val);

            nad_append_elem(pkt->nad, ns, "item", 3);
            nad_append_attr(pkt->nad, -1, "jid", jid_full(svc->jid));

            if(svc->name[0] != '\0')
                nad_append_attr(pkt->nad, -1, "name", svc->name);
        } while(xhash_iter_next(d->un));

    return pkt;
}
