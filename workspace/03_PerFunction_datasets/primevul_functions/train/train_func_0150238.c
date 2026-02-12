void MonClient::schedule_tick()
{
  auto do_tick = make_lambda_context([this]() { tick(); });
  if (!is_connected()) {

    const auto hunt_interval = (cct->_conf->mon_client_hunt_interval *
				reopen_interval_multiplier);
    timer.add_event_after(hunt_interval, do_tick);
  } else {

    timer.add_event_after(cct->_conf->mon_client_ping_interval, do_tick);
  }
}
