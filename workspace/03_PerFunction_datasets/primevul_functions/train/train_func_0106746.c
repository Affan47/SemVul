TEST_F(RenameCollectionTest, CollectionCatalogEntryPointerRemainsValidThroughRename) {
    _createCollection(_opCtx.get(), _sourceNss);
    Lock::GlobalWrite globalWrite(_opCtx.get());


    Collection* sourceColl = _getCollection_inlock(_opCtx.get(), _sourceNss);
    ASSERT(sourceColl);
    auto* sourceCatalogEntry = sourceColl->getCatalogEntry();
    ASSERT(sourceCatalogEntry);
    ASSERT_EQ(sourceCatalogEntry->ns(), _sourceNss);

    ASSERT_OK(renameCollection(_opCtx.get(), _sourceNss, _targetNss, {}));


    ASSERT_EQ(sourceCatalogEntry->ns(), _targetNss);
}
