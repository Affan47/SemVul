Status ImportGraphDef(const ImportGraphDefOptions& opts, const GraphDef& gdef,
                      Graph* g, ShapeRefiner* refiner,
                      ImportGraphDefResults* results) {
  if (!opts.return_tensors.empty()) {
    if (results == nullptr) {
      return errors::InvalidArgument(
          "results argument to ImportGraphDef() must be non-null if "
          "opts.return_tensors is non-empty");
    }
  }

  if (!opts.return_nodes.empty()) {
    if (opts.skip_mapped_nodes) {
      return errors::InvalidArgument(
          "Requesting return_nodes with skip_mapped_nodes set is not currently "
          "supported");
    }
    if (results == nullptr) {
      return errors::InvalidArgument(
          "results argument to ImportGraphDef() must be non-null if "
          "opts.return_nodes is non-empty");
    }
  }

  if (results != nullptr) {
    if (!results->return_tensors.empty() || !results->return_nodes.empty() ||
        !results->missing_unused_input_map_keys.empty()) {
      return errors::InvalidArgument(
          "All fields in results argument to ImportGraphDef() must be empty.");
    }
  }

  ShapeRefiner default_refiner(gdef.versions().producer(), g->op_registry());
  if (refiner == nullptr) {
    refiner = &default_refiner;
  } else {


    if (gdef.versions().producer() > 0 &&
        gdef.versions().producer() < refiner->graph_def_version() &&
        g->num_nodes() > 2) {
      LOG(WARNING) << "Importing a graph with a lower producer version "
                   << gdef.versions().producer()
                   << " into an existing graph with producer version "
                   << refiner->graph_def_version() << ". Shape inference will "
                   << "have run different parts of the graph with different "
                   << "producer versions.";
    }
  }


  refiner->set_graph_def_version(
      std::min(refiner->graph_def_version(), gdef.versions().producer()));

  if (results == nullptr) {
    return GraphConstructor::Construct(opts, gdef.node(), &gdef.versions(),
                                       &gdef.library(), g, refiner, nullptr,
                                       nullptr, nullptr);
  } else {
    return GraphConstructor::Construct(
        opts, gdef.node(), &gdef.versions(), &gdef.library(), g, refiner,
        &results->return_tensors, &results->return_nodes,
        &results->missing_unused_input_map_keys);
  }
}
