update_common_traits(const waypoint* wpt)
{


  traits.trait_geocaches |= (wpt->gc_data->diff && wpt->gc_data->terr);
  traits.trait_heartrate |= wpt->heartrate > 0;
  traits.trait_cadence |= wpt->cadence > 0;
  traits.trait_power |= wpt->power > 0;
  traits.trait_depth |= WAYPT_HAS(wpt, depth);
  traits.trait_temperature |= WAYPT_HAS(wpt, temperature);
}
