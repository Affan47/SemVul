write_state_to_entry(PRBool newState) {
  if (newState)
	return add_state_entry ();
  else
	return modify_state_entry ();
}
