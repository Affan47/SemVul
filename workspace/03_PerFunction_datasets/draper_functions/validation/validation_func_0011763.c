AddListControlReportMode()
{
   UseUpId();
   if( mShuttleMode != eIsCreating )
      return wxDynamicCast(wxWindow::FindWindowById( miId, mpDlg), wxListCtrl);
   wxListCtrl * pListCtrl;
   SetProportions( 1 );
   mpWind = pListCtrl = new wxListCtrl(mpParent, miId,
      wxDefaultPosition, wxSize(230,120),
      Style( wxLC_REPORT | wxLC_HRULES | wxLC_VRULES | wxSUNKEN_BORDER ));

   UpdateSizers();
   return pListCtrl;
}
