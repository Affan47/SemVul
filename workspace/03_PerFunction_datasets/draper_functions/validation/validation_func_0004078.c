AddPrompt(const wxString &Prompt)
{
   if( Prompt.IsEmpty() )
      return;
   if( mShuttleMode != eIsCreating )
      return;
   miProp=1;
   mpWind = new wxStaticText(mpParent, -1, Prompt, wxDefaultPosition, wxDefaultSize,
      Style( wxALIGN_RIGHT ));
   mpWind->SetName(wxStripMenuCodes(Prompt));
   UpdateSizersCore( false, wxALL | wxALIGN_RIGHT | wxALIGN_CENTRE_VERTICAL );
}
