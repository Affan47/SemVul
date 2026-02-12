void bgp_generate_updgrp_packets(struct thread *thread)
{
	struct peer *peer = THREAD_ARG(thread);

	struct stream *s;
	struct peer_af *paf;
	struct bpacket *next_pkt;
	uint32_t wpq;
	uint32_t generated = 0;
	afi_t afi;
	safi_t safi;

	wpq = atomic_load_explicit(&peer->bgp->wpkt_quanta,
				   memory_order_relaxed);


	if (!peer_established(peer))
		return;

	if ((peer->bgp->main_peers_update_hold)
	    || bgp_update_delay_active(peer->bgp))
		return;

	if (peer->t_routeadv)
		return;

	do {
		enum bgp_af_index index;

		s = NULL;
		for (index = BGP_AF_START; index < BGP_AF_MAX; index++) {
			paf = peer->peer_af_array[index];
			if (!paf || !PAF_SUBGRP(paf))
				continue;

			afi = paf->afi;
			safi = paf->safi;
			next_pkt = paf->next_pkt_to_send;


			if (!next_pkt || !next_pkt->buffer) {
				next_pkt = subgroup_withdraw_packet(
					PAF_SUBGRP(paf));
				if (!next_pkt || !next_pkt->buffer)
					subgroup_update_packet(PAF_SUBGRP(paf));
				next_pkt = paf->next_pkt_to_send;
			}


			if (!next_pkt || !next_pkt->buffer) {
				if (!paf->t_announce_route) {


					UNSET_FLAG(paf->subgroup->sflags,
						   SUBGRP_STATUS_FORCE_UPDATES);


					if (CHECK_FLAG(
						    peer->af_sflags[afi][safi],
						    PEER_STATUS_BORR_SEND)) {
						bgp_route_refresh_send(
							peer, afi, safi, 0, 0,
							0,
							BGP_ROUTE_REFRESH_EORR);

						SET_FLAG(peer->af_sflags[afi]
									[safi],
							 PEER_STATUS_EORR_SEND);
						UNSET_FLAG(
							peer->af_sflags[afi]
								       [safi],
							PEER_STATUS_BORR_SEND);

						if (bgp_debug_neighbor_events(
							    peer))
							zlog_debug(
								"%pBP sending route-refresh (EoRR) for %s/%s",
								peer,
								afi2str(afi),
								safi2str(safi));
					}
				}

				if (CHECK_FLAG(peer->cap,
					       PEER_CAP_RESTART_RCV)) {
					if (!(PAF_SUBGRP(paf))->t_coalesce
					    && peer->afc_nego[afi][safi]
					    && peer->synctime
					    && !CHECK_FLAG(
						    peer->af_sflags[afi][safi],
						    PEER_STATUS_EOR_SEND)) {


						if (BGP_SEND_EOR(peer->bgp, afi,
								 safi)) {
							SET_FLAG(
								peer->af_sflags
									[afi]
									[safi],
								PEER_STATUS_EOR_SEND);


							peer->eor_stime[afi]
								       [safi] =
								monotime(NULL);

							BGP_UPDATE_EOR_PKT(
								peer, afi, safi,
								s);
						}
					}
				}
				continue;
			}


			peer->pkt_stime[afi][safi] = monotime(NULL);


			s = bpacket_reformat_for_peer(next_pkt, paf);
			bgp_packet_add(peer, s);
			bpacket_queue_advance_peer(paf);
		}
	} while (s && (++generated < wpq));

	if (generated)
		bgp_writes_on(peer);

	bgp_write_proceed_actions(peer);
}
