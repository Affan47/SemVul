TEST_F(RenameCollectionTest, RenameCollectionForApplyOpsDropTargetByUUIDTargetDoesNotExist) {
    const auto& collA = NamespaceString("test.A");
    const auto& collB = NamespaceString("test.B");
    const auto& collC = NamespaceString("test.C");
    auto dbName = collA.db().toString();
    auto collAUUID = _createCollectionWithUUID(_opCtx.get(), collA);
    auto collCUUID = _createCollectionWithUUID(_opCtx.get(), collC);
    auto uuidDoc = BSON("ui" << collAUUID);

    auto cmd =
        BSON("renameCollection" << collA.ns() << "to" << collB.ns() << "dropTarget" << collCUUID);
    ASSERT_OK(renameCollectionForApplyOps(_opCtx.get(), dbName, uuidDoc["ui"], cmd, {}));

    ASSERT_FALSE(_collectionExists(_opCtx.get(), collA));
    ASSERT_FALSE(_collectionExists(_opCtx.get(), collC));

    ASSERT_TRUE(_collectionExists(_opCtx.get(), collB));

    auto newCollNS = _getCollectionNssFromUUID(_opCtx.get(), collAUUID);
    ASSERT_TRUE(newCollNS.isValid());
    ASSERT_EQUALS(newCollNS, collB);
}
