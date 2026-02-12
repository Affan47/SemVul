Status renameCollectionCommon(OperationContext* opCtx,
                              const NamespaceString& source,
                              const NamespaceString& target,
                              OptionalCollectionUUID targetUUID,
                              repl::OpTime renameOpTimeFromApplyOps,
                              const RenameCollectionOptions& options) {

    if (!renameOpTimeFromApplyOps.isNull() && opCtx->writesAreReplicated()) {
        return Status(
            ErrorCodes::BadValue,
            "renameCollection() cannot accept a rename optime when writes are replicated.");
    }

    DisableDocumentValidation validationDisabler(opCtx);

    boost::optional<Lock::GlobalWrite> globalWriteLock;
    boost::optional<Lock::DBLock> dbWriteLock;


    auto lockState = opCtx->lockState();
    if (source.db() == target.db())
        dbWriteLock.emplace(opCtx, source.db(), MODE_X);
    else if (!lockState->isW())
        globalWriteLock.emplace(opCtx);


    boost::optional<OldClientContext> ctx;
    const bool shardVersionCheck = true;
    ctx.emplace(opCtx, source.ns(), shardVersionCheck);

    auto replCoord = repl::ReplicationCoordinator::get(opCtx);
    bool userInitiatedWritesAndNotPrimary =
        opCtx->writesAreReplicated() && !replCoord->canAcceptWritesFor(opCtx, source);

    if (userInitiatedWritesAndNotPrimary) {
        return Status(ErrorCodes::NotMaster,
                      str::stream() << "Not primary while renaming collection " << source << " to "
                                    << target);
    }

    auto databaseHolder = DatabaseHolder::get(opCtx);
    auto sourceDB = databaseHolder->getDb(opCtx, source.db());
    if (sourceDB) {
        auto& dss = DatabaseShardingState::get(sourceDB);
        auto dssLock = DatabaseShardingState::DSSLock::lock(opCtx, &dss);
        dss.checkDbVersion(opCtx, dssLock);
    }
    Collection* const sourceColl = sourceDB ? sourceDB->getCollection(opCtx, source) : nullptr;
    if (!sourceColl) {
        if (sourceDB && sourceDB->getViewCatalog()->lookup(opCtx, source.ns()))
            return Status(ErrorCodes::CommandNotSupportedOnView,
                          str::stream() << "cannot rename view: " << source);
        return Status(ErrorCodes::NamespaceNotFound, "source namespace does not exist");
    }


    {
        auto* const css = CollectionShardingState::get(opCtx, source);
        const auto metadata = css->getCurrentMetadata();
        if (metadata->isSharded())
            return {ErrorCodes::IllegalOperation, "source namespace cannot be sharded"};
    }


    auto sourceIsUnreplicated = replCoord->isOplogDisabledFor(opCtx, source);
    auto targetIsUnreplicated = replCoord->isOplogDisabledFor(opCtx, target);
    if (sourceIsUnreplicated != targetIsUnreplicated) {
        return {ErrorCodes::IllegalOperation,
                "Cannot rename collections between a replicated and an unreplicated database"};
    }


    const auto checkIndexNamespace =
        serverGlobalParams.featureCompatibility.isVersionInitialized() &&
        serverGlobalParams.featureCompatibility.getVersion() !=
            ServerGlobalParams::FeatureCompatibility::Version::kFullyUpgradedTo42;
    std::string::size_type longestIndexNameLength =
        checkIndexNamespace ? sourceColl->getIndexCatalog()->getLongestIndexNameLength(opCtx) : 0;
    auto status = target.checkLengthForRename(longestIndexNameLength);
    if (!status.isOK()) {
        return status;
    }

    BackgroundOperation::assertNoBgOpInProgForNs(source.ns());

    auto targetDB = databaseHolder->openDb(opCtx, target.db());


    Collection* targetColl = targetDB->getCollection(opCtx, target);
    if (targetColl) {


        if (targetUUID && targetUUID == targetColl->uuid()) {
            invariant(source == target);
            return Status::OK();
        }

        {
            auto* const css = CollectionShardingState::get(opCtx, target);
            const auto metadata = css->getCurrentMetadata();
            if (metadata->isSharded())
                return {ErrorCodes::IllegalOperation, "cannot rename to a sharded collection"};
        }

        if (!options.dropTarget) {
            return Status(ErrorCodes::NamespaceExists, "target namespace exists");
        }


        if (options.dropTargetUUID && options.dropTargetUUID != targetColl->uuid()) {
            auto dropTargetNssFromUUID = getNamespaceFromUUID(opCtx, options.dropTargetUUID.get());

            auto status = renameTargetCollectionToTmp(
                opCtx, source, targetUUID.get(), targetDB, target, targetColl->uuid().get());
            if (!status.isOK())
                return status;
            targetColl = nullptr;
        }
    } else if (targetDB->getViewCatalog()->lookup(opCtx, target.ns())) {
        return Status(ErrorCodes::NamespaceExists,
                      str::stream() << "a view already exists with that name: " << target);
    }


    if (!targetColl && options.dropTargetUUID) {
        invariant(options.dropTarget);
        auto dropTargetNssFromUUID = getNamespaceFromUUID(opCtx, options.dropTargetUUID.get());
        if (!dropTargetNssFromUUID.isEmpty() && !dropTargetNssFromUUID.isDropPendingNamespace()) {
            invariant(dropTargetNssFromUUID.db() == target.db());
            targetColl = targetDB->getCollection(opCtx, dropTargetNssFromUUID);
        }
    }

    auto opObserver = opCtx->getServiceContext()->getOpObserver();

    auto sourceUUID = sourceColl->uuid();

    if (sourceDB == targetDB) {
        return writeConflictRetry(opCtx, "renameCollection", target.ns(), [&] {
            WriteUnitOfWork wunit(opCtx);
            if (!targetColl) {

                auto stayTemp = options.stayTemp;
                {

                    repl::UnreplicatedWritesBlock uwb(opCtx);
                    status = targetDB->renameCollection(opCtx, source.ns(), target.ns(), stayTemp);
                    if (!status.isOK()) {
                        return status;
                    }
                }


                UninterruptibleLockGuard noInterrupt(opCtx->lockState());


                opObserver->onRenameCollection(opCtx, source, target, sourceUUID, {}, 0U, stayTemp);
                wunit.commit();
                return Status::OK();
            }


            invariant(options.dropTarget);
            auto dropTargetUUID = targetColl->uuid();
            invariant(dropTargetUUID);


            auto isOplogDisabledForNamespace = replCoord->isOplogDisabledFor(opCtx, target);
            if (!isOplogDisabledForNamespace) {
                invariant(opCtx->writesAreReplicated());
                invariant(renameOpTimeFromApplyOps.isNull());


                std::vector<const IndexDescriptor*> indexesToDrop;
                auto indexIter = targetColl->getIndexCatalog()->getIndexIterator(opCtx, true);


                auto longDpns = target.makeDropPendingNamespace(repl::OpTime::max());
                while (indexIter->more()) {
                    auto index = indexIter->next()->descriptor();
                    auto status = longDpns.checkLengthForRename(index->indexName().size());
                    if (!status.isOK()) {
                        indexesToDrop.push_back(index);
                    }
                }


                auto sourceUuidString = sourceUUID ? sourceUUID.get().toString() : "no UUID";
                auto dropTargetUuidString =
                    dropTargetUUID ? dropTargetUUID.get().toString() : "no UUID";
                for (auto&& index : indexesToDrop) {
                    log() << "renameCollection: renaming collection " << sourceUuidString
                          << " from " << source << " to " << target << " (" << dropTargetUuidString
                          << ") - target collection contains an index namespace '"
                          << index->indexNamespace()
                          << "' that would be too long after drop-pending rename. Dropping index "
                             "immediately.";
                    fassert(50941, targetColl->getIndexCatalog()->dropIndex(opCtx, index));
                    opObserver->onDropIndex(
                        opCtx, target, targetColl->uuid(), index->indexName(), index->infoObj());
                }
            }

            auto numRecords = targetColl->numRecords(opCtx);
            auto renameOpTime = opObserver->preRenameCollection(
                opCtx, source, target, sourceUUID, dropTargetUUID, numRecords, options.stayTemp);

            if (!renameOpTimeFromApplyOps.isNull()) {


                if (!renameOpTime.isNull()) {
                    severe() << "renameCollection: " << source << " to " << target
                             << " (with dropTarget=true) - unexpected renameCollection oplog entry"
                             << " written to the oplog with optime " << renameOpTime;
                    fassertFailed(40616);
                }
                renameOpTime = renameOpTimeFromApplyOps;
            }


            repl::UnreplicatedWritesBlock uwb(opCtx);

            status = targetDB->dropCollection(opCtx, targetColl->ns().ns(), renameOpTime);
            if (!status.isOK()) {
                return status;
            }

            status = targetDB->renameCollection(opCtx, source.ns(), target.ns(), options.stayTemp);
            if (!status.isOK()) {
                return status;
            }

            opObserver->postRenameCollection(
                opCtx, source, target, sourceUUID, dropTargetUUID, options.stayTemp);
            wunit.commit();
            return Status::OK();
        });
    }


    auto tmpNameResult =
        targetDB->makeUniqueCollectionNamespace(opCtx, "tmp%%%%%.renameCollection");
    if (!tmpNameResult.isOK()) {
        return tmpNameResult.getStatus().withContext(
            str::stream() << "Cannot generate temporary collection name to rename " << source
                          << " to "
                          << target);
    }
    const auto& tmpName = tmpNameResult.getValue();


    status = tmpName.checkLengthForRename(longestIndexNameLength);
    if (!status.isOK()) {
        return status;
    }

    Collection* tmpColl = nullptr;
    OptionalCollectionUUID newUUID;
    {
        auto collectionOptions = sourceColl->getCatalogEntry()->getCollectionOptions(opCtx);


        if (targetUUID)
            newUUID = targetUUID;
        else if (collectionOptions.uuid)
            newUUID = UUID::gen();

        collectionOptions.uuid = newUUID;

        writeConflictRetry(opCtx, "renameCollection", tmpName.ns(), [&] {
            WriteUnitOfWork wunit(opCtx);
            tmpColl = targetDB->createCollection(opCtx, tmpName.ns(), collectionOptions);
            wunit.commit();
        });
    }


    auto tmpCollectionDropper = makeGuard([&] {
        BSONObjBuilder unusedResult;
        Status status = Status::OK();
        try {
            status =
                dropCollection(opCtx,
                               tmpName,
                               unusedResult,
                               renameOpTimeFromApplyOps,
                               DropCollectionSystemCollectionMode::kAllowSystemCollectionDrops);
        } catch (...) {
            status = exceptionToStatus();
        }
        if (!status.isOK()) {


            log() << "Unable to drop temporary collection " << tmpName << " while renaming from "
                  << source << " to " << target << ": " << status;
        }
    });


    {
        std::vector<BSONObj> indexesToCopy;
        std::unique_ptr<IndexCatalog::IndexIterator> sourceIndIt =
            sourceColl->getIndexCatalog()->getIndexIterator(opCtx, true);
        while (sourceIndIt->more()) {
            auto descriptor = sourceIndIt->next()->descriptor();
            if (descriptor->isIdIndex()) {
                continue;
            }

            const BSONObj currIndex = descriptor->infoObj();


            BSONObjBuilder newIndex;
            for (auto&& elem : currIndex) {
                if (elem.fieldNameStringData() == "ns") {
                    newIndex.append("ns", tmpName.ns());
                } else {
                    newIndex.append(elem);
                }
            }
            indexesToCopy.push_back(newIndex.obj());
        }


        status = writeConflictRetry(opCtx, "renameCollection", tmpName.ns(), [&] {
            WriteUnitOfWork wunit(opCtx);
            auto tmpIndexCatalog = tmpColl->getIndexCatalog();
            for (const auto& indexToCopy : indexesToCopy) {
                opObserver->onCreateIndex(opCtx,
                                          tmpName,
                                          *(tmpColl->uuid()),
                                          indexToCopy,
                                          false
                                          );
                auto indexResult =
                    tmpIndexCatalog->createIndexOnEmptyCollection(opCtx, indexToCopy);
                if (!indexResult.isOK()) {
                    return indexResult.getStatus();
                }
            };
            wunit.commit();
            return Status::OK();
        });
        if (!status.isOK()) {
            return status;
        }
    }

    {


        AutoGetCollectionForRead autoSourceColl(opCtx, source);
        AutoGetCollection autoTmpColl(opCtx, tmpName, MODE_IX);
        ctx.reset();

        if (opCtx->getServiceContext()->getStorageEngine()->supportsDBLocking()) {
            if (globalWriteLock) {
                const ResourceId globalLockResourceId(RESOURCE_GLOBAL,
                                                      ResourceId::SINGLETON_GLOBAL);
                lockState->downgrade(globalLockResourceId, MODE_IX);
                invariant(!lockState->isW());
            } else {
                invariant(lockState->isW());
            }
        }

        auto cursor = sourceColl->getCursor(opCtx);
        auto record = cursor->next();
        while (record) {
            opCtx->checkForInterrupt();

            auto beginBatchId = record->id;
            status = writeConflictRetry(opCtx, "renameCollection", tmpName.ns(), [&] {
                WriteUnitOfWork wunit(opCtx);

                if (!record || (beginBatchId != record->id)) {
                    record = cursor->seekExact(beginBatchId);
                }
                for (int i = 0; record && (i < internalInsertMaxBatchSize.load()); i++) {
                    const InsertStatement stmt(record->data.releaseToBson());
                    OpDebug* const opDebug = nullptr;
                    auto status = tmpColl->insertDocument(opCtx, stmt, opDebug, true);
                    if (!status.isOK()) {
                        return status;
                    }
                    record = cursor->next();
                }
                cursor->save();

                ON_BLOCK_EXIT([ opCtx, ns = tmpName.ns(), &cursor ]() {
                    writeConflictRetry(
                        opCtx, "retryRestoreCursor", ns, [&cursor] { cursor->restore(); });
                });

                if (MONGO_FAIL_POINT(writeConfilctInRenameCollCopyToTmp)) {
                    throw WriteConflictException();
                }
                wunit.commit();
                return Status::OK();
            });
            if (!status.isOK()) {
                return status;
            }
        }
    }
    globalWriteLock.reset();


    invariant(tmpName.db() == target.db());
    status = renameCollectionCommon(
        opCtx, tmpName, target, targetUUID, renameOpTimeFromApplyOps, options);
    if (!status.isOK()) {
        return status;
    }
    tmpCollectionDropper.dismiss();

    BSONObjBuilder unusedResult;
    return dropCollection(opCtx,
                          source,
                          unusedResult,
                          renameOpTimeFromApplyOps,
                          DropCollectionSystemCollectionMode::kAllowSystemCollectionDrops);
}
