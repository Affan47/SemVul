request_unit_unload(struct unit *pcargo)
{
  struct unit *ptrans = unit_transport_get(pcargo);

  if (can_client_issue_orders()
      && ptrans
      && can_unit_unload(pcargo, ptrans)
      && can_unit_survive_at_tile(pcargo, unit_tile(pcargo))) {
    dsend_packet_unit_unload(&client.conn, pcargo->id, ptrans->id);

    if (unit_owner(pcargo) == client.conn.playing
        && pcargo->activity == ACTIVITY_SENTRY) {

      dsend_packet_unit_change_activity(&client.conn, pcargo->id,
                                        ACTIVITY_IDLE, S_LAST, BASE_NONE);
    }
  }
}
