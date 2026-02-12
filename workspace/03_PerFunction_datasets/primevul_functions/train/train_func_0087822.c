void decoder_context::process_reference_picture_set(slice_segment_header* hdr)
{
  std::vector<int> removeReferencesList;

  const int currentID = img->get_ID();


  if (isIRAP(nal_unit_type) && NoRaslOutputFlag) {

    int currentPOC = img->PicOrderCntVal;


    for (int i=0;i<dpb.size();i++) {
      de265_image* img = dpb.get_image(i);

      if (img->PicState != UnusedForReference &&
          img->PicOrderCntVal < currentPOC &&
          img->removed_at_picture_id > img->get_ID()) {

        removeReferencesList.push_back(img->get_ID());
        img->removed_at_picture_id = img->get_ID();


      }
    }
  }


  if (isIDR(nal_unit_type)) {


    NumPocStCurrBefore = 0;
    NumPocStCurrAfter = 0;
    NumPocStFoll = 0;
    NumPocLtCurr = 0;
    NumPocLtFoll = 0;
  }
  else {
    const ref_pic_set* rps = &hdr->CurrRps;


    int i,j,k;


    for (i=0, j=0, k=0;
         i<rps->NumNegativePics;
         i++)
      {
        if (rps->UsedByCurrPicS0[i]) {
          PocStCurrBefore[j++] = img->PicOrderCntVal + rps->DeltaPocS0[i];

        }
        else {
          PocStFoll[k++] = img->PicOrderCntVal + rps->DeltaPocS0[i];
        }
      }

    NumPocStCurrBefore = j;


    for (i=0, j=0;
         i<rps->NumPositivePics;
         i++)
      {
        if (rps->UsedByCurrPicS1[i]) {
          PocStCurrAfter[j++] = img->PicOrderCntVal + rps->DeltaPocS1[i];

        }
        else {
          PocStFoll[k++] = img->PicOrderCntVal + rps->DeltaPocS1[i];
        }
      }

    NumPocStCurrAfter = j;
    NumPocStFoll = k;


    for (i=0, j=0, k=0;

         i<hdr->num_long_term_sps + hdr->num_long_term_pics;
         i++)
      {
        int pocLt = PocLsbLt[i];

        if (hdr->delta_poc_msb_present_flag[i]) {
          int currentPictureMSB = img->PicOrderCntVal - hdr->slice_pic_order_cnt_lsb;
          pocLt += currentPictureMSB
            - DeltaPocMsbCycleLt[i] * current_sps->MaxPicOrderCntLsb;
        }

        if (UsedByCurrPicLt[i]) {
          PocLtCurr[j] = pocLt;
          CurrDeltaPocMsbPresentFlag[j] = hdr->delta_poc_msb_present_flag[i];
          j++;
        }
        else {
          PocLtFoll[k] = pocLt;
          FollDeltaPocMsbPresentFlag[k] = hdr->delta_poc_msb_present_flag[i];
          k++;
        }
      }

    NumPocLtCurr = j;
    NumPocLtFoll = k;
  }


  std::vector<char> picInAnyList(dpb.size(), false);


  dpb.log_dpb_content();

  for (int i=0;i<NumPocLtCurr;i++) {
    int k;
    if (!CurrDeltaPocMsbPresentFlag[i]) {
      k = dpb.DPB_index_of_picture_with_LSB(PocLtCurr[i], currentID, true);
    }
    else {
      k = dpb.DPB_index_of_picture_with_POC(PocLtCurr[i], currentID, true);
    }

    RefPicSetLtCurr[i] = k;
    if (k>=0) picInAnyList[k]=true;
    else {


      int concealedPicture = generate_unavailable_reference_picture(current_sps.get(),
                                                                    PocLtCurr[i], true);
      picInAnyList.resize(dpb.size(), false);

      RefPicSetLtCurr[i] = k = concealedPicture;
      picInAnyList[concealedPicture]=true;
    }

    if (dpb.get_image(k)->integrity != INTEGRITY_CORRECT) {
      img->integrity = INTEGRITY_DERIVED_FROM_FAULTY_REFERENCE;
    }
  }


  for (int i=0;i<NumPocLtFoll;i++) {
    int k;
    if (!FollDeltaPocMsbPresentFlag[i]) {
      k = dpb.DPB_index_of_picture_with_LSB(PocLtFoll[i], currentID, true);
    }
    else {
      k = dpb.DPB_index_of_picture_with_POC(PocLtFoll[i], currentID, true);
    }

    RefPicSetLtFoll[i] = k;
    if (k>=0) picInAnyList[k]=true;
    else {
      int concealedPicture = k = generate_unavailable_reference_picture(current_sps.get(),
                                                                        PocLtFoll[i], true);
      picInAnyList.resize(dpb.size(), false);

      RefPicSetLtFoll[i] = concealedPicture;
      picInAnyList[concealedPicture]=true;
    }
  }


  for (int i=0;i<NumPocLtCurr;i++) {
    dpb.get_image(RefPicSetLtCurr[i])->PicState = UsedForLongTermReference;
  }

  for (int i=0;i<NumPocLtFoll;i++) {
    dpb.get_image(RefPicSetLtFoll[i])->PicState = UsedForLongTermReference;
  }


  for (int i=0;i<NumPocStCurrBefore;i++) {
    int k = dpb.DPB_index_of_picture_with_POC(PocStCurrBefore[i], currentID);


    RefPicSetStCurrBefore[i] = k;
    if (k>=0) picInAnyList[k]=true;
    else {
      int concealedPicture = generate_unavailable_reference_picture(current_sps.get(),
                                                                    PocStCurrBefore[i], false);
      RefPicSetStCurrBefore[i] = k = concealedPicture;

      picInAnyList.resize(dpb.size(), false);
      picInAnyList[concealedPicture] = true;


    }

    if (dpb.get_image(k)->integrity != INTEGRITY_CORRECT) {
      img->integrity = INTEGRITY_DERIVED_FROM_FAULTY_REFERENCE;
    }
  }

  for (int i=0;i<NumPocStCurrAfter;i++) {
    int k = dpb.DPB_index_of_picture_with_POC(PocStCurrAfter[i], currentID);


    RefPicSetStCurrAfter[i] = k;
    if (k>=0) picInAnyList[k]=true;
    else {
      int concealedPicture = generate_unavailable_reference_picture(current_sps.get(),
                                                                    PocStCurrAfter[i], false);
      RefPicSetStCurrAfter[i] = k = concealedPicture;


      picInAnyList.resize(dpb.size(), false);
      picInAnyList[concealedPicture]=true;


    }

    if (dpb.get_image(k)->integrity != INTEGRITY_CORRECT) {
      img->integrity = INTEGRITY_DERIVED_FROM_FAULTY_REFERENCE;
    }
  }

  for (int i=0;i<NumPocStFoll;i++) {
    int k = dpb.DPB_index_of_picture_with_POC(PocStFoll[i], currentID);


    RefPicSetStFoll[i] = k;
    if (k>=0) picInAnyList[k]=true;
  }


  for (int i=0;i<dpb.size();i++)
    if (i>=picInAnyList.size() || !picInAnyList[i])
      {
        de265_image* dpbimg = dpb.get_image(i);
        if (dpbimg != img &&
            dpbimg->removed_at_picture_id > img->get_ID())
          {
            if (dpbimg->PicState != UnusedForReference) {
              removeReferencesList.push_back(dpbimg->get_ID());


              dpbimg->removed_at_picture_id = img->get_ID();
            }
          }
      }

  hdr->RemoveReferencesList = removeReferencesList;


}
