TEST_F(RenameCollectionTest, LongIndexNameAllowedForTemporaryCollectionForRenameAcrossDatabase) {
    ASSERT_GREATER_THAN(_targetNssDifferentDb.size(), _sourceNss.size());
    std::size_t longestIndexNameAllowedForTarget =
        NamespaceString::MaxNsLen - 2U  - _targetNssDifferentDb.size();
    ASSERT_OK(_sourceNss.checkLengthForRename(longestIndexNameAllowedForTarget));
    ASSERT_OK(_targetNssDifferentDb.checkLengthForRename(longestIndexNameAllowedForTarget));


    const NamespaceString tempNss(_targetNssDifferentDb.getSisterNS("tmpXXXXX.renameCollection"));
    ASSERT_EQUALS(ErrorCodes::InvalidLength,
                  tempNss.checkLengthForRename(longestIndexNameAllowedForTarget));

    _createCollection(_opCtx.get(), _sourceNss);
    const std::string indexName(longestIndexNameAllowedForTarget, 'a');
    _createIndexOnEmptyCollection(_opCtx.get(), _sourceNss, indexName);
    ASSERT_OK(renameCollection(_opCtx.get(), _sourceNss, _targetNssDifferentDb, {}));
}
