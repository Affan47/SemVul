projectProperties()
{

	const Cscope::ManagedProject* project
		= dynamic_cast<const Cscope::ManagedProject*>
			(ProjectManager::project());
	if (project == NULL)
		return;


	ProjectDialog dlg(this);
	dlg.setParamsForProject(project);
	if (dlg.exec() == QDialog::Rejected)
		return;


	Core::ProjectBase::Params params;
	dlg.getParams<Cscope::ManagedProject>(params);

	bool rebuild = false;
	try {

		ProjectManager::updateConfig(params);


		if (ProjectManager::engine().status() == Core::Engine::Rebuild)
			rebuild = true;
	}
	catch (Core::Exception* e) {
		e->showMessage();
		delete e;
	}


	if (rebuild) {
		QString msg = tr("This project needs to be rebuilt.\nWould you like to"
		                 " build it now?");
		if (QMessageBox::question(this, tr("Rebuild Prject"), msg,
		                          QMessageBox::Yes | QMessageBox::No)
		    == QMessageBox::Yes) {
			buildProject();
		}
	}
}
