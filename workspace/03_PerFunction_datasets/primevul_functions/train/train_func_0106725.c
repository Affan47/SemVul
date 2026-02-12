TEST_F(RenameCollectionTest, RenameAcrossDatabasesDoesNotPreserveCatalogPointers) {
    _createCollection(_opCtx.get(), _sourceNss);
    Lock::GlobalWrite globalWrite(_opCtx.get());


    Collection* sourceColl = _getCollection_inlock(_opCtx.get(), _sourceNss);
    ASSERT(sourceColl);
    auto* sourceCatalogEntry = sourceColl->getCatalogEntry();
    ASSERT(sourceCatalogEntry);

    ASSERT_OK(renameCollection(_opCtx.get(), _sourceNss, _targetNssDifferentDb, {}));


    Collection* targetColl = _getCollection_inlock(_opCtx.get(), _targetNssDifferentDb);
    ASSERT(targetColl);
    ASSERT_NE(targetColl, sourceColl);
    auto* targetCatalogEntry = targetColl->getCatalogEntry();
    ASSERT(targetCatalogEntry);
    ASSERT_NE(targetCatalogEntry, sourceCatalogEntry);
}
