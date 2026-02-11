Execute() {
    FrameEditor* ed = (FrameEditor*) GetEditor();
    FrameIdrawComp *comp = ((FrameIdrawComp*)ed->GetComponent());
    ed->GetViewer()->GetSelection()->Clear();
    FramesView* fv = (FramesView*)ed->GetViewer()->GetGraphicView();
    Iterator frameptr;
    fv->SetView(ed->GetFrame(), frameptr);
    Damage* damage = ed->GetViewer()->GetDamage();
    damage->Incur(fv->GetView(frameptr)->GetGraphic());
    int before = fv->Index(frameptr);
    fv->Last(frameptr);
    int after = fv->Index(frameptr);
    ed->SetFrame((FrameView*)fv->GetView(frameptr));
    damage->Incur(ed->GetFrame()->GetGraphic());
    ed->UpdateFrame(true);
    FrameNumberState* fnumstate = ed->framenumstate();
    int fnum = fv->Index(frameptr);
    fnumstate->framenumber(fnum);
    _requestmotion = after-before;
    _actualmotion = Math::abs(_requestmotion);
    const char* funcformat = AbsMoveFuncFormat();
    ComTerpServ* comterp = ed->GetComTerp();
    if (funcformat && comterp) {
      char buf[BUFSIZ];
      sprintf(buf, funcformat, fnum);
      ComValue retval(comterp->run(buf));
    }
    unidraw->Update();
}
