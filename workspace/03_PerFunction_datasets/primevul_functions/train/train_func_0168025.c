get_poll_adj(NCR_Instance inst, double error_in_estimate, double peer_distance)
{
  double poll_adj;

  if (error_in_estimate > peer_distance) {
    int shift = 0;
    unsigned long temp = (int)(error_in_estimate / peer_distance);
    do {
      shift++;
      temp>>=1;
    } while (temp);

    poll_adj = -shift - inst->poll_score + 0.5;

  } else {
    int samples = SRC_Samples(inst->source);


    poll_adj = ((double)samples / inst->poll_target - 1.0) / inst->poll_target;


    if (samples < inst->poll_target) {
      poll_adj *= 2.0;
    }
  }

  return poll_adj;
}
