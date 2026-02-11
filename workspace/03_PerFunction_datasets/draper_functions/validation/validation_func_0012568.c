ds1wm_down(struct ds1wm_data *ds1wm_data)
{
	ds1wm_reset(ds1wm_data);


	ds1wm_write_register(ds1wm_data, DS1WM_INT_EN,
		ds1wm_data->int_en_reg_none);

	if (ds1wm_data->cell->disable)
		ds1wm_data->cell->disable(ds1wm_data->pdev);
}
