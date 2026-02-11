_cb_icon_sel(void *data, void *data2)
{
   E_Config_Dialog_Data *cfdata;
   E_Config_Dialog *cfd;
   E_Dialog *dia;
   Evas_Object *o;
   Evas_Coord w, h;

   cfdata = data;
   if (!cfdata) return;
   if (cfdata->gui.fsel) return;

   cfd = data2;
   if (!cfd) return;

   dia = e_dialog_new(cfd->con, "E", "_mime_icon_select_dialog");
   if (!dia) return;
   if (cfdata->type == EDJ)
     e_dialog_title_set(dia, _("Select an Edje file"));
   else if (cfdata->type == IMG)
     e_dialog_title_set(dia, _("Select an image"));

   e_dialog_resizable_set(dia, 1);

   dia->data = cfdata;
   e_object_del_attach_func_set(E_OBJECT(dia), _dia_del);
   o = e_widget_fsel_add(dia->win->evas, "~/", "/", NULL, NULL,
			 _cb_fsel_sel, cfdata, NULL, cfdata, 1);

   cfdata->gui.fsel_wid = o;
   evas_object_show(o);
   e_widget_size_min_get(o, &w, &h);
   e_dialog_content_set(dia, o, w, h);

   e_dialog_button_add(dia, _("OK"), NULL, _cb_fsel_ok, cfdata);
   e_dialog_button_add(dia, _("Cancel"), NULL, _cb_fsel_cancel, cfdata);
   e_win_centered_set(dia->win, 1);
   e_dialog_show(dia);
   e_dialog_border_icon_set(dia, "enlightenment/file_icons");

   cfdata->gui.fsel = dia;
}
