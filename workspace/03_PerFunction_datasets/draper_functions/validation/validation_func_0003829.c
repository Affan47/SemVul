mpeg4_sensor_deleted(GF_Node *node, GF_SensorHandler *hdl)
{
	GF_Compositor *compositor = gf_sc_get_compositor(node);
	if (compositor) {
		GF_VisualManager *visual;
		u32 i=0;
		gf_list_del_item(compositor->sensors, hdl);
		gf_list_del_item(compositor->previous_sensors, hdl);
		if (compositor->interaction_sensors) compositor->interaction_sensors--;
		while ( (visual=gf_list_enum(compositor->visuals, &i)) ) {
			if (visual->offscreen)
				compositor_compositetexture_sensor_delete(visual->offscreen, hdl);
		}

#ifndef GPAC_DISABLE_SVG
		gf_sg_unregister_event_type(gf_node_get_graph(node), GF_DOM_EVENT_MOUSE|GF_DOM_EVENT_KEY);
#endif
	}
}
