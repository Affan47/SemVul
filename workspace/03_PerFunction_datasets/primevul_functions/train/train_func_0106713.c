TEST_F(RenameCollectionTest,
       RenameCollectionForApplyOpsDropTargetByUUIDTargetExistsButRealDropTargetDoesNotExist) {
    const auto& collA = NamespaceString("test.A");
    const auto& collB = NamespaceString("test.B");
    auto dbName = collA.db().toString();
    auto collAUUID = _createCollectionWithUUID(_opCtx.get(), collA);
    auto collBUUID = _createCollectionWithUUID(_opCtx.get(), collB);
    auto collCUUID = UUID::gen();
    auto uuidDoc = BSON("ui" << collAUUID);


    auto cmd =
        BSON("renameCollection" << collA.ns() << "to" << collB.ns() << "dropTarget" << collCUUID);
    ASSERT_OK(renameCollectionForApplyOps(_opCtx.get(), dbName, uuidDoc["ui"], cmd, {}));

    ASSERT_FALSE(_collectionExists(_opCtx.get(), collA));

    ASSERT_TRUE(_collectionExists(_opCtx.get(), collB));

    const auto& tmpB = UUIDCatalog::get(_opCtx.get()).lookupNSSByUUID(collBUUID);
    ASSERT_FALSE(tmpB.isEmpty());
    ASSERT_TRUE(tmpB != collB);
    ASSERT_TRUE(tmpB.coll().startsWith("tmp"));
}
