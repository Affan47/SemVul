diplomat_escape(struct player *pplayer, struct unit *pdiplomat,
                            const struct city *pcity)
{
  struct tile *ptile;
  int escapechance;
  struct city *spyhome;


  {
    const struct veteran_level
      *vunit = utype_veteran_level(unit_type(pdiplomat), pdiplomat->veteran);
    const struct veteran_level
      *vbase = utype_veteran_level(unit_type(pdiplomat), 0);
    escapechance = game.server.diplchance
      + (vunit->power_fact - vbase->power_fact);
  }

  if (pcity) {
    ptile = pcity->tile;
  } else {
    ptile = unit_tile(pdiplomat);
  }


  spyhome = find_closest_city(ptile, NULL, unit_owner(pdiplomat), FALSE,
                              FALSE, FALSE, TRUE, FALSE, NULL);

  if (spyhome
      && unit_has_type_flag(pdiplomat, F_SPY)
      && (unit_has_type_flag(pdiplomat, F_SUPERSPY)
          || fc_rand (100) < escapechance)) {

    notify_player(pplayer, ptile, E_MY_DIPLOMAT_ESCAPE, ftc_server,
                  _("Your %s has successfully completed"
                    " the mission and returned unharmed to %s."),
                  unit_link(pdiplomat),
                  city_link(spyhome));
    if (maybe_make_veteran(pdiplomat)) {
      notify_unit_experience(pdiplomat);
    }


    if (!teleport_unit_to_city (pdiplomat, spyhome, -1, FALSE)) {
      send_unit_info (pplayer, pdiplomat);
      log_error("Bug in diplomat_escape: Spy can't teleport.");
      return;
    }

    return;
  } else {
    if (pcity) {
      notify_player(pplayer, ptile, E_MY_DIPLOMAT_FAILED, ftc_server,
                    _("Your %s was captured after completing"
                      " the mission in %s."),
                    unit_tile_link(pdiplomat),
                    city_link(pcity));
    } else {
      notify_player(pplayer, ptile, E_MY_DIPLOMAT_FAILED, ftc_server,
                    _("Your %s was captured after completing"
                      " the mission."),
                    unit_tile_link(pdiplomat));
    }
  }


  wipe_unit(pdiplomat, ULR_CAUGHT, NULL);
}
