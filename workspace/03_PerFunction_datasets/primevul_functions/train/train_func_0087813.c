bool decoder_context::process_slice_segment_header(slice_segment_header* hdr,
                                                   de265_error* err, de265_PTS pts,
                                                   nal_header* nal_hdr,
                                                   void* user_data)
{
  *err = DE265_OK;

  flush_reorder_buffer_at_this_frame = false;


  int pps_id = hdr->slice_pic_parameter_set_id;
  if (pps[pps_id]->pps_read==false) {
    logerror(LogHeaders, "PPS %d has not been read\n", pps_id);
    assert(false);
  }

  current_pps = pps[pps_id];
  current_sps = sps[ (int)current_pps->seq_parameter_set_id ];
  current_vps = vps[ (int)current_sps->video_parameter_set_id ];

  calc_tid_and_framerate_ratio();


  if (hdr->first_slice_segment_in_pic_flag) {


    current_image_poc_lsb = hdr->slice_pic_order_cnt_lsb;


    seq_parameter_set* sps = current_sps.get();


    int image_buffer_idx;
    bool isOutputImage = (!sps->sample_adaptive_offset_enabled_flag || param_disable_sao);
    image_buffer_idx = dpb.new_image(current_sps, this, pts, user_data, isOutputImage);
    if (image_buffer_idx == -1) {
      *err = DE265_ERROR_IMAGE_BUFFER_FULL;
      return false;
    }

     img = dpb.get_image(image_buffer_idx);
    img->nal_hdr = *nal_hdr;


    img->set_headers(current_vps, current_sps, current_pps);

    img->decctx = this;

    img->clear_metadata();


    if (isIRAP(nal_unit_type)) {
      if (isIDR(nal_unit_type) ||
          isBLA(nal_unit_type) ||
          first_decoded_picture ||
          FirstAfterEndOfSequenceNAL)
        {
          NoRaslOutputFlag = true;
          FirstAfterEndOfSequenceNAL = false;
        }
      else if (0)
        {
        }
      else
        {
          NoRaslOutputFlag   = false;
          HandleCraAsBlaFlag = false;
        }
    }


    if (isRASL(nal_unit_type) &&
        NoRaslOutputFlag)
      {
        img->PicOutputFlag = false;
      }
    else
      {
        img->PicOutputFlag = !!hdr->pic_output_flag;
      }

    process_picture_order_count(hdr);

    if (hdr->first_slice_segment_in_pic_flag) {

      img->PicState = UsedForShortTermReference;

      process_reference_picture_set(hdr);
    }

    img->PicState = UsedForShortTermReference;

    log_set_current_POC(img->PicOrderCntVal);


    first_decoded_picture = false;
  }
  else {


    if (img == NULL) {
      return false;
    }
  }

  if (hdr->slice_type == SLICE_TYPE_B ||
      hdr->slice_type == SLICE_TYPE_P)
    {
      bool success = construct_reference_picture_lists(hdr);
      if (!success) {
        return false;
      }
    }


  loginfo(LogHeaders,"end of process-slice-header\n");
  dpb.log_dpb_content();


  if (hdr->dependent_slice_segment_flag==0) {
    hdr->SliceAddrRS = hdr->slice_segment_address;
  } else {
    hdr->SliceAddrRS = previous_slice_header->SliceAddrRS;
  }

  previous_slice_header = hdr;


  loginfo(LogHeaders,"SliceAddrRS = %d\n",hdr->SliceAddrRS);

  return true;
}
