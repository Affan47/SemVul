Execute() {
    FrameEditor* ed = (FrameEditor*) GetEditor();
    FrameIdrawComp *comp = ((FrameIdrawComp*)ed->GetComponent());
    ed->GetViewer()->GetSelection()->Clear();
    FramesView* fv = (FramesView*)ed->GetViewer()->GetGraphicView();
    Iterator frameptr;
    fv->SetView(ed->GetFrame(), frameptr);
    OverlaysView* prev = ed->GetFrame();
    _actualmotion = 0;
    FrameNumberState* fnumstate = ed->framenumstate();
    int ofnum = fnumstate->framenumber();
    if (!_allowbg && ofnum + _requestmotion <= 0)
      _plannedmotion = -ofnum + 1;
    else
      _plannedmotion = _requestmotion;
    for (int i = 0; i < Math::abs(_plannedmotion); i++) {
	if (!fv->Done(frameptr)) {
	    if (_plannedmotion > 0)
		fv->Next(frameptr);
	    else
		fv->Prev(frameptr);
	    _actualmotion++;
	}
    }
    if (fv->Done(frameptr)) {
	if (plannedmotion() > 0)
	    fv->Prev(frameptr);
	else
	    fv->Next(frameptr);
	_actualmotion--;
	if (wraparound()) {
	  if (requestmotion() > 0) {
	    fv->First(frameptr);
	    fv->Next(frameptr);
	  } else
	    fv->Last(frameptr);
	}
    }
    ed->SetFrame((FrameView*)fv->GetView(frameptr));
    if (ed->GetFrame() && prev != ed->GetFrame()) {
	Damage* damage = ed->GetViewer()->GetDamage();
	damage->Incur(prev->GetGraphic());
	damage->Incur(ed->GetFrame()->GetGraphic());
    }
    ed->UpdateFrame(true);
    int fnum = fv->Index(frameptr);
    fnumstate->framenumber(fnum);
    ComTerpServ* comterp = ed->GetComTerp();
    const char* funcformat = MoveFuncFormat();
    if (funcformat && comterp) {
      char buf[BUFSIZ];
      sprintf(buf, funcformat, _requestmotion);
      ComValue retval(comterp->run(buf));
    }
    unidraw->Update();
}
