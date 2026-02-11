labviewer_change_ship(Tree *caller)
{

	if ( !Lab_in_mission ) {
		return;
	}

	Lab_selected_index = (int)(caller->GetSelectedItem()->GetData());

	labviewer_update_desc_window();
	labviewer_update_flags_window();
	labviewer_update_variables_window();
}
