NCR_InitiateSampleBurst(NCR_Instance inst, int n_good_samples, int n_total_samples)
{

  if (inst->mode == MODE_CLIENT) {


    switch (inst->opmode) {
      case MD_BURST_WAS_OFFLINE:
      case MD_BURST_WAS_ONLINE:

        break;

      case MD_ONLINE:
      case MD_OFFLINE:
        inst->opmode = inst->opmode == MD_ONLINE ?
          MD_BURST_WAS_ONLINE : MD_BURST_WAS_OFFLINE;
        inst->burst_good_samples_to_go = n_good_samples;
        inst->burst_total_samples_to_go = n_total_samples;
        start_initial_timeout(inst);
        break;
      default:
        assert(0);
        break;
    }
  }

}
