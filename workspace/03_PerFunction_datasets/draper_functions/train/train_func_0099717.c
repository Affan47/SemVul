Execute () {
    Editor* ed = GetEditor();

    if (ReadyToClose(ed)) {
        Component* comp = ed->GetComponent();

        if (comp == nil) {
            unidraw->Close(ed);
        } else {
            unidraw->CloseDependents(comp->GetRoot());
        }
        Iterator i;

        for (;;) {
            unidraw->First(i);

            if (unidraw->Done(i)) {
                break;
            }

            ed = unidraw->GetEditor(i);

            if (ReadyToClose(ed)) {
                comp = ed->GetComponent();

                if (comp == nil) {
                    unidraw->Close(ed);
                } else {
                    unidraw->CloseDependents(comp->GetRoot());
                }
            } else {
                return;
            }
        }
        unidraw->Quit();
    }
}
