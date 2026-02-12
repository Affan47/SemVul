Status renameCollectionForRollback(OperationContext* opCtx,
                                   const NamespaceString& target,
                                   const UUID& uuid) {

    auto source = getNamespaceFromUUID(opCtx, uuid);
    invariant(source.db() == target.db(),
              str::stream() << "renameCollectionForRollback: source and target namespaces must "
                               "have the same database. source: "
                            << source.toString()
                            << ". target: "
                            << target.toString());

    RenameCollectionOptions options;
    invariant(!options.dropTarget);

    log() << "renameCollectionForRollback: rename " << source << " (" << uuid << ") to " << target
          << ".";

    return renameCollectionCommon(opCtx, source, target, uuid, {}, options);
}
