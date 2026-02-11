pkix_pl_CollectionCertStoreContext_Destroy(
        PKIX_PL_Object *object,
        void *plContext)
{
        PKIX_PL_CollectionCertStoreContext *colCertStoreContext = NULL;

        PKIX_ENTER(COLLECTIONCERTSTORECONTEXT,
                    "pkix_pl_CollectionCertStoreContext_Destroy");
        PKIX_NULLCHECK_ONE(object);

        PKIX_CHECK(pkix_CheckType
                    (object, PKIX_COLLECTIONCERTSTORECONTEXT_TYPE, plContext),
                    PKIX_OBJECTNOTCOLLECTIONCERTSTORECONTEXT);

        colCertStoreContext = (PKIX_PL_CollectionCertStoreContext *)object;

        PKIX_DECREF(colCertStoreContext->storeDir);
        PKIX_DECREF(colCertStoreContext->crlList);
        PKIX_DECREF(colCertStoreContext->certList);

cleanup:
        PKIX_RETURN(COLLECTIONCERTSTORECONTEXT);
}
