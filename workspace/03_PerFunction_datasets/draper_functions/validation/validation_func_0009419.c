PopulateOrExchange(ShuttleGui & S)
{
   wxTextValidator vld(wxFILTER_NUMERIC);

   S.AddSpace(0, 5);


   S.StartMultiColumn(2, wxCENTER);
   {
      mAmpT = S.Id(ID_AMP_TEXT).AddTextBox(_("Amplification (dB):"),
                                           wxT(""),
                                           12);
      mAmpT->SetValidator(vld);
   }
   S.EndMultiColumn();


   S.StartHorizontalLay(wxEXPAND);
   {
      S.SetStyle(wxSL_HORIZONTAL);
      mAmpS = S.Id(ID_AMP_SLIDER).AddSlider(wxT(""),
                                            0,
                                            AMP_MAX,
                                            AMP_MIN);
      mAmpS->SetName(_("Amplification dB"));
   }
   S.EndHorizontalLay();


   S.StartMultiColumn(2, wxCENTER);
   {
      mPeakT = S.Id(ID_PEAK_TEXT).AddTextBox(_("New Peak Amplitude (dB):"),
                                             wxT(""),
                                             12);
      mPeakT->SetValidator(vld);
   }
   S.EndMultiColumn();


   S.StartHorizontalLay(wxCENTER);
   {
      mClip = S.Id(ID_CLIP_CHECKBOX).AddCheckBox(_("Allow clipping"),
                                                 wxT("false"));
   }
   S.EndHorizontalLay();

   return;
}
