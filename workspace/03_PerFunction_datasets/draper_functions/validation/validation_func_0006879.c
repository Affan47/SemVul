updateNavigationButton()
{
    d->m_NavigationMenu->clear();

    Core::Command *cmd = actionManager()->command(Core::Constants::A_PATIENT_NEW);
    d->m_NavigationMenu->addAction(cmd->action());
    d->m_NavigationMenu->addSeparator();


    Core::ActionContainer *navMenu = actionManager()->actionContainer(Core::Constants::M_PATIENTS_NAVIGATION);
    if (!navMenu)
        return;
    for(int i = 0; i < navMenu->menu()->actions().count(); ++i) {
        d->m_NavigationMenu->addAction(navMenu->menu()->actions().at(i));
    }
}
