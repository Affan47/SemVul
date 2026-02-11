project_edit_callback ( GtkAction *act )
{
  int st = get_selected_task ();
  Project *p;

  if ( st < 0 || ! num_visible_tasks ) {
    create_confirm_window ( CONFIRM_ERROR,
      gettext("Error"),
      gettext("You have not selected\na task."),
      gettext("Ok"), NULL, NULL,
      NULL, NULL, NULL,
      NULL );
  } else {
    if ( visible_tasks[st]->task->project_id < 0 ) {
      create_confirm_window ( CONFIRM_ERROR,
        gettext("Error"),
        gettext("The selected task does not\nhave a project."),
        gettext("Ok"), NULL, NULL,
        NULL, NULL, NULL,
        NULL );
    } else {
      p = projectGet ( visible_tasks[st]->task->project_id );
      create_project_edit_window ( p );
    }
  }
}
