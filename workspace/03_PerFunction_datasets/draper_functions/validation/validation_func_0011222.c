extcon_set_cable_state(struct extcon_dev *edev,
			const char *cable_name, bool cable_state)
{
	int id;

	id = find_cable_id_by_name(edev, cable_name);
	if (id < 0)
		return id;

	return extcon_set_cable_state_(edev, id, cable_state);
}
