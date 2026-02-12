TEST_F(RenameCollectionTest, CollectionPointerRemainsValidThroughRename) {
    _createCollection(_opCtx.get(), _sourceNss);
    Lock::GlobalWrite globalWrite(_opCtx.get());


    Collection* sourceColl = _getCollection_inlock(_opCtx.get(), _sourceNss);
    ASSERT(sourceColl);

    ASSERT_OK(renameCollection(_opCtx.get(), _sourceNss, _targetNss, {}));


    Collection* targetColl = _getCollection_inlock(_opCtx.get(), _targetNss);
    ASSERT(targetColl);
    ASSERT_EQ(targetColl, sourceColl);


    ASSERT_EQ(targetColl->ns(), _targetNss);
}
