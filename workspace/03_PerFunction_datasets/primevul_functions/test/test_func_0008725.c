static void net_layer_file_report(gerbv_net_t *net,
		gerbv_image_t *img, gerbv_project_t *prj)
{

	if (net->label != NULL)
		g_message (_("    Net label: %s"), net->label->str);


	if (net->layer->name != NULL)
		g_message (_("    Layer name: %s"), net->layer->name);


	for (int i = 0; i <= prj->last_loaded; i++) {
		if (img == prj->file[i]->image)
			g_message (_("    In file: %s"), prj->file[i]->name);
	}
}
