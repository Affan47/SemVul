Status FindCommonUnaryOpChain(const NodeDef& root_node, int* prefix_length,
                                ChainLinkSet* tails,
                                std::set<string>* ctrl_inputs) const {
    *prefix_length = 0;


    ChainLinkSet cur_tails;
    TF_RETURN_IF_ERROR(InitializeChains(root_node, &cur_tails));
    if (cur_tails.size() < 2) {
      return Status::OK();
    }
    ctrl_inputs->clear();
    bool stop = false;
    while (!stop && !cur_tails.empty() &&
           OpsAreSafeToHoist(root_node, cur_tails)) {

      ++(*prefix_length);
      tails->swap(cur_tails);
      GatherControlInputs(ctrl_inputs, *tails);


      TF_RETURN_IF_ERROR(AdvanceTails(*tails, &cur_tails, &stop));
    }
    return Status::OK();
  }
