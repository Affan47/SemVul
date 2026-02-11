OnNewWindow(wxCommandEvent& event)
{
	SpectSeq *spectseq;
	wxString leaf;
	wxString pathload;
	int width, height;

	if(event.GetId() == MENU_SPECTRUM)
		pathload = path_spectload;
	else
		pathload = path_spectload2;

	wxString filename = wxFileSelector(_T("Read spectrum or praat data"),pathload,
		_T(""),_T(""),_T("*"),wxOPEN);
	if(filename.IsEmpty())
	{
		return;
	}


	spectseq = new SpectSeq;
	if(spectseq == NULL)
	{
		wxLogError(_T("Failed to create SpectSeq"));
		return;
	}

	wxFileInputStream stream(filename);
	if(stream.Ok() == FALSE)
	{
		wxLogError(_T("Failed to open '%s'"),filename.c_str());
		return;
	}
	wxFileName path = wxFileName(filename);
   leaf = path.GetName();

	setlocale(LC_NUMERIC,"C");
	spectseq->Load(stream);
	spectseq->name = leaf;
	spectseq->MakePitchenv(spectseq->pitchenv,0,spectseq->numframes-1);

	if(event.GetId() == MENU_SPECTRUM)
		path_spectload = path.GetPath();
	else
		path_spectload2 = path.GetPath();


	GetClientSize(&width, &height);
	MyChild *subframe = new MyChild(myframe, _T("Spectrum"),
                                      wxPoint(10, 0), wxSize(500, height),
                                      wxDEFAULT_FRAME_STYLE |
                                      wxNO_FULL_REPAINT_ON_RESIZE);

	subframe->SetTitle(leaf);


	subframe->CreateStatusBar();

	subframe->GetClientSize(&width, &height);
	SpectDisplay *canvas = new SpectDisplay(subframe, wxPoint(0, 0), wxSize(width, height), spectseq);
	canvas->savepath = filename;
   currentcanvas = canvas;


	subframe->SetMenuBar(MakeMenu(1,translator->dictionary_name));
	subframe->canvas = canvas;
	subframe->Show(TRUE);

}
