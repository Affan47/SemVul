render_geometry_radio_action (GtkAction *action)
{


	gint value = gtk_radio_action_get_current_value (GTK_RADIO_ACTION (action));


	switch(value)
	{
		case GEOMETRY_STICK :
			TypeGeom = GABEDIT_TYPEGEOM_STICK;
			RebuildGeom = TRUE;
			glarea_rafresh(GLArea);
			break;
		case GEOMETRY_BALLSTICK :
			TypeGeom = GABEDIT_TYPEGEOM_BALLSTICK;
			RebuildGeom = TRUE;
			glarea_rafresh(GLArea);
			break;
		case GEOMETRY_WIREFRAME :
			TypeGeom = GABEDIT_TYPEGEOM_WIREFRAME;
			RebuildGeom = TRUE;
			glarea_rafresh(GLArea);
			break;
		case GEOMETRY_SPACEFILL :
			TypeGeom = GABEDIT_TYPEGEOM_SPACE;
			RebuildGeom = TRUE;
			glarea_rafresh(GLArea);
			break;
		case GEOMETRY_NO :
			TypeGeom = GABEDIT_TYPEGEOM_NO;
			glarea_rafresh(GLArea);
			break;
	}
}
