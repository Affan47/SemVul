EXPORTED int http_allow_noauth_get(struct transaction_t *txn)
{

    switch (txn->meth) {
    case METH_GET:
    case METH_HEAD:

        return 0;
    default:
        return 1;
    }
}
