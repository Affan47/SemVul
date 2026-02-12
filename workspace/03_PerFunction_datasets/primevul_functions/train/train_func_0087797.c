de265_error decoder_context::decode_slice_unit_parallel(image_unit* imgunit,
                                                        slice_unit* sliceunit)
{
  de265_error err = DE265_OK;

  remove_images_from_dpb(sliceunit->shdr->RemoveReferencesList);


  de265_image* img = imgunit->img;
  const pic_parameter_set& pps = img->get_pps();

  sliceunit->state = slice_unit::InProgress;

  bool use_WPP = (img->decctx->num_worker_threads > 0 &&
                  pps.entropy_coding_sync_enabled_flag);

  bool use_tiles = (img->decctx->num_worker_threads > 0 &&
                    pps.tiles_enabled_flag);


  if (img->decctx->num_worker_threads > 0 &&
      pps.entropy_coding_sync_enabled_flag == false &&
      pps.tiles_enabled_flag == false) {

    img->decctx->add_warning(DE265_WARNING_NO_WPP_CANNOT_USE_MULTITHREADING, true);
  }


  if (imgunit->is_first_slice_segment(sliceunit)) {
    slice_segment_header* shdr = sliceunit->shdr;
    int firstCTB = shdr->slice_segment_address;

    for (int ctb=0;ctb<firstCTB;ctb++) {

      img->ctb_progress[ctb].set_progress(CTB_PROGRESS_PREFILTER);
    }
  }


  slice_unit* prevSlice = imgunit->get_prev_slice_segment(sliceunit);

  if (prevSlice && prevSlice->state == slice_unit::Decoded) {
    mark_whole_slice_as_processed(imgunit,prevSlice,CTB_PROGRESS_PREFILTER);
  }


  if (!use_WPP && !use_tiles) {

    err = decode_slice_unit_sequential(imgunit, sliceunit);
    sliceunit->state = slice_unit::Decoded;
    mark_whole_slice_as_processed(imgunit,sliceunit,CTB_PROGRESS_PREFILTER);
    return err;
  }


  if (use_WPP && use_tiles) {


    return DE265_WARNING_PPS_HEADER_INVALID;
  }


  if (use_WPP) {

    err = decode_slice_unit_WPP(imgunit, sliceunit);
    sliceunit->state = slice_unit::Decoded;
    mark_whole_slice_as_processed(imgunit,sliceunit,CTB_PROGRESS_PREFILTER);
    return err;
  }
  else if (use_tiles) {

    err = decode_slice_unit_tiles(imgunit, sliceunit);
    sliceunit->state = slice_unit::Decoded;
    mark_whole_slice_as_processed(imgunit,sliceunit,CTB_PROGRESS_PREFILTER);
    return err;
  }

  assert(false);
  return err;
}
