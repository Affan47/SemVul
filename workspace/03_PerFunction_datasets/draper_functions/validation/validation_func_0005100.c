CreateControls()
{

    CWelcomePage* itemWizardPage2 = this;

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage2->SetSizer(itemBoxSizer3);

    m_pTitleStaticCtrl = new wxStaticText;
    m_pTitleStaticCtrl->Create( itemWizardPage2, wxID_STATIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_pTitleStaticCtrl->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, FALSE, _T("Verdana")));
    itemBoxSizer3->Add(m_pTitleStaticCtrl, 0, wxALIGN_LEFT|wxALL, 5);

    m_pDescriptionStaticCtrl = new wxStaticText;
    m_pDescriptionStaticCtrl->Create( itemWizardPage2, wxID_STATIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(m_pDescriptionStaticCtrl, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer3->Add(5, 5, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer62 = new wxFlexGridSizer(2, 1, 0, 0);
    itemFlexGridSizer62->AddGrowableCol(1);
    itemBoxSizer3->Add(itemFlexGridSizer62, 0, wxGROW|wxALL, 5);

    m_pChangeApplicationsCtrl = new wxRadioButton;
    m_pChangeApplicationsCtrl->Create(itemWizardPage2, ID_WELCOMECHANGEAPPS, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    if ( isWCGClient() ) {
        m_pChangeApplicationsCtrl->SetValue(TRUE);
    } else {
        m_pChangeApplicationsCtrl->SetValue(FALSE);
    }
    itemFlexGridSizer62->Add(m_pChangeApplicationsCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAttachToProjectCtrl = new wxRadioButton;
    m_pAttachToProjectCtrl->Create( itemWizardPage2, ID_WELCOMESELECTWIZARDPROJECT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    if ( isWCGClient() ) {
        m_pAttachToProjectCtrl->SetValue(FALSE);
    } else {
        m_pAttachToProjectCtrl->SetValue(TRUE);
    }
    itemFlexGridSizer62->Add(m_pAttachToProjectCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAttachToAccountManagerCtrl = new wxRadioButton;
    m_pAttachToAccountManagerCtrl->Create( itemWizardPage2, ID_WELCOMESELECTWIZARDACCOUNTMGR, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_pAttachToAccountManagerCtrl->SetValue(FALSE);
    itemFlexGridSizer62->Add(m_pAttachToAccountManagerCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pDirectionsStaticCtrl = new wxStaticText;
    m_pDirectionsStaticCtrl->Create( itemWizardPage2, wxID_STATIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(m_pDirectionsStaticCtrl, 0, wxALIGN_LEFT|wxALL, 5);

    itemWizardPage2->SetSizer(itemBoxSizer3);

#ifdef __WXMAC__

    HIViewRef buttonView = (HIViewRef)m_pAttachToProjectCtrl->GetHandle();
    HIObjectRef   theObject = (HIObjectRef)HIViewGetSuperview(buttonView);
    HIObjectSetAccessibilityIgnored(theObject, true);
#endif

}
