get_spaceship_descr(struct player_spaceship *pship)
{
  struct player_spaceship ship;
  static struct astring str = ASTRING_INIT;

  astr_clear(&str);

  if (!pship) {
    pship = &ship;
    memset(&ship, 0, sizeof(ship));
  }


  astr_add_line(&str, _("Population:      %5d"), pship->population);


  astr_add_line(&str, _("Support:         %5d %%"),
		(int) (pship->support_rate * 100.0));


  astr_add_line(&str, _("Energy:          %5d %%"),
		(int) (pship->energy_rate * 100.0));


  astr_add_line(&str, PL_("Mass:            %5d ton",
			  "Mass:            %5d tons",
			  pship->mass), pship->mass);

  if (pship->propulsion > 0) {

    astr_add_line(&str, _("Travel time:     %5.1f years"),
		  (float) (0.1 * ((int) (pship->travel_time * 10.0))));
  } else {

    astr_add_line(&str, "%s", _("Travel time:        N/A     "));
  }


  astr_add_line(&str, _("Success prob.:   %5d %%"),
		(int) (pship->success_rate * 100.0));


  astr_add_line(&str, _("Year of arrival: %8s"),
		(pship->state == SSHIP_LAUNCHED)
		? textyear((int) (pship->launch_year +
				  (int) pship->travel_time))
		: "-   ");

  return astr_str(&str);
}
