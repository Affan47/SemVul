decoder_context::decoder_context()
{


  param_sei_check_hash = false;
  param_conceal_stream_errors = true;
  param_suppress_faulty_pictures = false;

  param_disable_deblocking = false;
  param_disable_sao = false;


  param_sps_headers_fd = -1;
  param_vps_headers_fd = -1;
  param_pps_headers_fd = -1;
  param_slice_headers_fd = -1;

  param_image_allocation_functions = de265_image::default_image_allocation;
  param_image_allocation_userdata  = NULL;


  current_vps = NULL;
  current_sps = NULL;
  current_pps = NULL;


  num_worker_threads = 0;


  limit_HighestTid = 6;
  framerate_ratio = 100;

  goal_HighestTid = 6;
  current_HighestTid = 6;
  layer_framerate_ratio = 100;

  compute_framedrop_table();


  current_image_poc_lsb = 0;
  first_decoded_picture = 0;
  NoRaslOutputFlag = 0;
  HandleCraAsBlaFlag = 0;
  FirstAfterEndOfSequenceNAL = 0;
  PicOrderCntMsb = 0;
  prevPicOrderCntLsb = 0;
  prevPicOrderCntMsb = 0;
  img = NULL;


  first_decoded_picture = true;


  current_image_poc_lsb = -1;
}
