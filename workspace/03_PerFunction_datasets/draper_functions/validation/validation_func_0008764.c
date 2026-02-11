slotContextAboutToHide()
{


  KXmlGuiWindow *kmw = qobject_cast<KXmlGuiWindow *>(q->mainWindow());
  if (kmw && kmw->toolBarMenuAction()) {
    if (kmw->toolBarMenuAction()->associatedWidgets().count() > 1) {
      context->removeAction(kmw->toolBarMenuAction());
    }
  }


  QAction *configureAction = 0;
  const char* actionName = KStandardAction::name(KStandardAction::ConfigureToolbars);
  configureAction = findAction(actionName);

  if (!configureAction && kmw) {
    configureAction = kmw->actionCollection()->action(actionName);
  }

  if (configureAction) {
    context->removeAction(configureAction);
  }

  context->removeAction(contextLockAction);
}
