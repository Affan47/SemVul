Status TryImport() {
    TF_RETURN_IF_ERROR(EnsureNoNameCollisions());
    TF_RETURN_IF_ERROR(ValidateInputMapAndControlDependencies());
    TF_RETURN_IF_ERROR(BuildNodeIndex());
    TF_RETURN_IF_ERROR(InitFromEdges());


    TF_RETURN_IF_ERROR(Convert());

    TF_RETURN_IF_ERROR(AddBackEdges());
    TF_RETURN_IF_ERROR(UpdateVersionDef());
    TF_RETURN_IF_ERROR(PopulateReturnTensors());
    TF_RETURN_IF_ERROR(PopulateReturnNodes());
    TF_RETURN_IF_ERROR(PopulateMissingUnusedInputMapKeys());
    UpdateUniquifiedColocationNames();
    FixupSourceAndSinkEdges(g_);
    return Status::OK();
  }
