Status LoadSavedModel(const SessionOptions& session_options,
                      const RunOptions& run_options, const string& export_dir,
                      const std::unordered_set<string>& tags,
                      SavedModelBundleLite* const bundle) {
  SavedModelBundle legacy_bundle;
  SessionOptions rewritten_options(session_options);


  rewritten_options.config.mutable_experimental()
      ->set_optimize_for_static_graph(true);


  rewritten_options.config.mutable_experimental()
      ->set_disable_output_partition_graphs(true);


  TF_RETURN_IF_ERROR(LoadSavedModel(rewritten_options, run_options, export_dir,
                                    tags, &legacy_bundle));
  *bundle = SavedModelBundleLite(
      absl::make_unique<LiteSessionWrapper>(std::move(legacy_bundle.session)),
      std::move(*legacy_bundle.meta_graph_def.mutable_signature_def()));
  return Status::OK();
}
