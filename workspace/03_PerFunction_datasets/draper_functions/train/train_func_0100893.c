Remove(Interactor* i) {
    i->parent = nil;
    if (i->insert_window != nil) {
	delete i->insert_window;
	i->insert_window = nil;
	i->managed_window = nil;
    }
    if (i->window != nil) {

	i->window->unbind();
	i->Deactivate();
    }
}
