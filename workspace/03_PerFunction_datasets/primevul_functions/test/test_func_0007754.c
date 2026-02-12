enum DecodeResult decode_substream(thread_context* tctx,
                                   bool block_wpp,
                                   bool first_independent_substream)
{
  const pic_parameter_set& pps = tctx->img->get_pps();
  const seq_parameter_set& sps = tctx->img->get_sps();

  const int ctbW = sps.PicWidthInCtbsY;


  const int startCtbY = tctx->CtbY;


  if ((!first_independent_substream || tctx->CtbY != startCtbY) &&
      pps.entropy_coding_sync_enabled_flag &&
      tctx->CtbY>=1 && tctx->CtbX==0)
    {
      if (sps.PicWidthInCtbsY>1) {
        if ((tctx->CtbY-1) >= tctx->imgunit->ctx_models.size()) {
          return Decode_Error;
        }


        tctx->img->wait_for_progress(tctx->task, 1,tctx->CtbY-1,CTB_PROGRESS_PREFILTER);


        tctx->ctx_model = tctx->imgunit->ctx_models[(tctx->CtbY-1)];
        tctx->imgunit->ctx_models[(tctx->CtbY-1)].release();
      }
      else {
        tctx->img->wait_for_progress(tctx->task, 0,tctx->CtbY-1,CTB_PROGRESS_PREFILTER);
        initialize_CABAC_models(tctx);
      }
    }


  do {
    const int ctbx = tctx->CtbX;
    const int ctby = tctx->CtbY;

    if (ctbx+ctby*ctbW >= pps.CtbAddrRStoTS.size()) {
        return Decode_Error;
    }

    if (ctbx >= sps.PicWidthInCtbsY ||
        ctby >= sps.PicHeightInCtbsY) {
        return Decode_Error;
    }

    if (block_wpp && ctby>0 && ctbx < ctbW-1) {


      tctx->img->wait_for_progress(tctx->task, ctbx+1,ctby-1, CTB_PROGRESS_PREFILTER);
    }


    if (tctx->ctx_model.empty() == false) {
      return Decode_Error;
    }

    read_coding_tree_unit(tctx);


    if (pps.entropy_coding_sync_enabled_flag &&
        ctbx == 1 &&
        ctby < sps.PicHeightInCtbsY-1)
      {

        if (tctx->imgunit->ctx_models.size() <= ctby) {
          return Decode_Error;
        }

        tctx->imgunit->ctx_models[ctby] = tctx->ctx_model;
        tctx->imgunit->ctx_models[ctby].decouple();
      }


    int end_of_slice_segment_flag = decode_CABAC_term_bit(&tctx->cabac_decoder);


    if (end_of_slice_segment_flag) {


      if (pps.dependent_slice_segments_enabled_flag) {
        tctx->shdr->ctx_model_storage = tctx->ctx_model;
        tctx->shdr->ctx_model_storage.decouple();

        tctx->shdr->ctx_model_storage_defined = true;
      }
    }

    tctx->img->ctb_progress[ctbx+ctby*ctbW].set_progress(CTB_PROGRESS_PREFILTER);


    logtrace(LogSlice,"read CTB %d -> end=%d\n", tctx->CtbAddrInRS, end_of_slice_segment_flag);


    const int lastCtbY = tctx->CtbY;

    bool endOfPicture = advanceCtbAddr(tctx);

    if (endOfPicture &&
        end_of_slice_segment_flag == false)
      {
        tctx->decctx->add_warning(DE265_WARNING_CTB_OUTSIDE_IMAGE_AREA, false);
        tctx->img->integrity = INTEGRITY_DECODING_ERRORS;
        return Decode_Error;
      }


    if (end_of_slice_segment_flag) {


      return Decode_EndOfSliceSegment;
    }


    if (!end_of_slice_segment_flag) {
      bool end_of_sub_stream = false;
      end_of_sub_stream |= (pps.tiles_enabled_flag &&
                            pps.TileId[tctx->CtbAddrInTS] != pps.TileId[tctx->CtbAddrInTS-1]);
      end_of_sub_stream |= (pps.entropy_coding_sync_enabled_flag &&
                            lastCtbY != tctx->CtbY);

      if (end_of_sub_stream) {
        int end_of_sub_stream_one_bit = decode_CABAC_term_bit(&tctx->cabac_decoder);
        if (!end_of_sub_stream_one_bit) {
          tctx->decctx->add_warning(DE265_WARNING_EOSS_BIT_NOT_SET, false);
          tctx->img->integrity = INTEGRITY_DECODING_ERRORS;
          return Decode_Error;
        }

        init_CABAC_decoder_2(&tctx->cabac_decoder);
        return Decode_EndOfSubstream;
      }
    }

  } while (true);
}
