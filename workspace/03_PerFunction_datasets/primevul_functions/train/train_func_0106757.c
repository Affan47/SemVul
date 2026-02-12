TEST_F(RenameCollectionTest, CatalogPointersRenameValidThroughRenameAfterDroppingTarget) {
    _createCollection(_opCtx.get(), _sourceNss);
    _createCollection(_opCtx.get(), _targetNss);
    Lock::GlobalWrite globalWrite(_opCtx.get());

    Collection* sourceColl = _getCollection_inlock(_opCtx.get(), _sourceNss);
    ASSERT(sourceColl);
    auto* sourceCatalogEntry = sourceColl->getCatalogEntry();
    ASSERT(sourceCatalogEntry);

    RenameCollectionOptions options;
    options.dropTarget = true;
    ASSERT_OK(renameCollection(_opCtx.get(), _sourceNss, _targetNss, options));


    ASSERT_EQ(sourceColl->ns(), _targetNss);
    ASSERT_EQ(sourceCatalogEntry->ns(), _targetNss);
}
