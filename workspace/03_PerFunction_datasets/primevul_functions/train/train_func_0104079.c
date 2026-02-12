void Server::handleCommand_Interact(NetworkPacket *pkt)
{


	InteractAction action;
	u16 item_i;

	*pkt >> (u8 &)action;
	*pkt >> item_i;

	std::istringstream tmp_is(pkt->readLongString(), std::ios::binary);
	PointedThing pointed;
	pointed.deSerialize(tmp_is);

	verbosestream << "TOSERVER_INTERACT: action=" << (int)action << ", item="
			<< item_i << ", pointed=" << pointed.dump() << std::endl;

	session_t peer_id = pkt->getPeerId();
	RemotePlayer *player = m_env->getPlayer(peer_id);

	if (player == NULL) {
		errorstream <<
			"Server::ProcessData(): Canceling: No player for peer_id=" <<
			peer_id << " disconnecting peer!" << std::endl;
		DisconnectPeer(peer_id);
		return;
	}

	PlayerSAO *playersao = player->getPlayerSAO();
	if (playersao == NULL) {
		errorstream <<
			"Server::ProcessData(): Canceling: No player object for peer_id=" <<
			peer_id << " disconnecting peer!" << std::endl;
		DisconnectPeer(peer_id);
		return;
	}

	if (playersao->isDead()) {
		actionstream << "Server: " << player->getName()
				<< " tried to interact while dead; ignoring." << std::endl;
		if (pointed.type == POINTEDTHING_NODE) {

			RemoteClient *client = getClient(peer_id);
			v3s16 blockpos = getNodeBlockPos(pointed.node_undersurface);
			client->SetBlockNotSent(blockpos);
		}

		m_script->on_cheat(playersao, "interacted_while_dead");
		return;
	}

	process_PlayerPos(player, playersao, pkt);

	v3f player_pos = playersao->getLastGoodPosition();


	playersao->getPlayer()->setWieldIndex(item_i);


	v3s16 p_under = pointed.node_undersurface;
	v3s16 p_above = pointed.node_abovesurface;


	ServerActiveObject *pointed_object = NULL;
	if (pointed.type == POINTEDTHING_OBJECT) {
		pointed_object = m_env->getActiveObject(pointed.object_id);
		if (pointed_object == NULL) {
			verbosestream << "TOSERVER_INTERACT: "
				"pointed object is NULL" << std::endl;
			return;
		}

	}

	v3f pointed_pos_under = player_pos;
	v3f pointed_pos_above = player_pos;
	if (pointed.type == POINTEDTHING_NODE) {
		pointed_pos_under = intToFloat(p_under, BS);
		pointed_pos_above = intToFloat(p_above, BS);
	}
	else if (pointed.type == POINTEDTHING_OBJECT) {
		pointed_pos_under = pointed_object->getBasePosition();
		pointed_pos_above = pointed_pos_under;
	}


	if (!checkPriv(player->getName(), "interact")) {
		actionstream << player->getName() << " attempted to interact with " <<
				pointed.dump() << " without 'interact' privilege" << std::endl;


		RemoteClient *client = getClient(peer_id);

		if (action == INTERACT_DIGGING_COMPLETED) {
			v3s16 blockpos = getNodeBlockPos(floatToInt(pointed_pos_under, BS));
			client->SetBlockNotSent(blockpos);
		}

		else if (action == INTERACT_PLACE) {
			v3s16 blockpos = getNodeBlockPos(floatToInt(pointed_pos_above, BS));
			client->SetBlockNotSent(blockpos);
		}
		return;
	}


	static thread_local const bool enable_anticheat =
			!g_settings->getBool("disable_anticheat");

	if ((action == INTERACT_START_DIGGING || action == INTERACT_DIGGING_COMPLETED ||
			action == INTERACT_PLACE || action == INTERACT_USE) &&
			enable_anticheat && !isSingleplayer()) {
		float d = playersao->getEyePosition().getDistanceFrom(pointed_pos_under);

		if (!checkInteractDistance(player, d, pointed.dump())) {

			RemoteClient *client = getClient(peer_id);
			v3s16 blockpos = getNodeBlockPos(floatToInt(pointed_pos_under, BS));
			client->SetBlockNotSent(blockpos);
			return;
		}
	}


	RollbackScopeActor rollback_scope(m_rollback,
			std::string("player:")+player->getName());


	if (action == INTERACT_START_DIGGING) {
		if (pointed.type == POINTEDTHING_NODE) {
			MapNode n(CONTENT_IGNORE);
			bool pos_ok;

			n = m_env->getMap().getNode(p_under, &pos_ok);
			if (!pos_ok) {
				infostream << "Server: Not punching: Node not found. "
					"Adding block to emerge queue." << std::endl;
				m_emerge->enqueueBlockEmerge(peer_id, getNodeBlockPos(p_above),
					false);
			}

			if (n.getContent() != CONTENT_IGNORE)
				m_script->node_on_punch(p_under, n, playersao, pointed);


			playersao->noCheatDigStart(p_under);
		}
		else if (pointed.type == POINTEDTHING_OBJECT) {

			if (pointed_object->isGone())
				return;

			ItemStack selected_item, hand_item;
			ItemStack tool_item = playersao->getWieldedItem(&selected_item, &hand_item);
			ToolCapabilities toolcap =
					tool_item.getToolCapabilities(m_itemdef);
			v3f dir = (pointed_object->getBasePosition() -
					(playersao->getBasePosition() + playersao->getEyeOffset())
						).normalize();
			float time_from_last_punch =
				playersao->resetTimeFromLastPunch();

			u16 src_original_hp = pointed_object->getHP();
			u16 dst_origin_hp = playersao->getHP();

			u16 wear = pointed_object->punch(dir, &toolcap, playersao,
					time_from_last_punch);


			playersao->getWieldedItem(&selected_item);
			bool changed = selected_item.addWear(wear, m_itemdef);
			if (changed)
				playersao->setWieldedItem(selected_item);


			if (src_original_hp != pointed_object->getHP() &&
					pointed_object->getType() == ACTIVEOBJECT_TYPE_PLAYER) {
				SendPlayerHPOrDie((PlayerSAO *)pointed_object,
						PlayerHPChangeReason(PlayerHPChangeReason::PLAYER_PUNCH, playersao));
			}


			if (dst_origin_hp != playersao->getHP())
				SendPlayerHPOrDie(playersao,
						PlayerHPChangeReason(PlayerHPChangeReason::PLAYER_PUNCH, pointed_object));
		}

	}


	else if (action == INTERACT_STOP_DIGGING) {
	}


	else if (action == INTERACT_DIGGING_COMPLETED) {

		if (pointed.type == POINTEDTHING_NODE) {
			bool pos_ok;
			MapNode n = m_env->getMap().getNode(p_under, &pos_ok);
			if (!pos_ok) {
				infostream << "Server: Not finishing digging: Node not found. "
					"Adding block to emerge queue." << std::endl;
				m_emerge->enqueueBlockEmerge(peer_id, getNodeBlockPos(p_above),
					false);
			}


			bool is_valid_dig = true;
			if (enable_anticheat && !isSingleplayer()) {
				v3s16 nocheat_p = playersao->getNoCheatDigPos();
				float nocheat_t = playersao->getNoCheatDigTime();
				playersao->noCheatDigEnd();

				if (nocheat_p != p_under) {
					infostream << "Server: " << player->getName()
							<< " started digging "
							<< PP(nocheat_p) << " and completed digging "
							<< PP(p_under) << "; not digging." << std::endl;
					is_valid_dig = false;

					m_script->on_cheat(playersao, "finished_unknown_dig");
				}


				ItemStack selected_item, hand_item;
				playersao->getPlayer()->getWieldedItem(&selected_item, &hand_item);


				DigParams params = getDigParams(m_nodedef->get(n).groups,
						&selected_item.getToolCapabilities(m_itemdef));

				if (!params.diggable) {
					params = getDigParams(m_nodedef->get(n).groups,
						&hand_item.getToolCapabilities(m_itemdef));
				}

				if (!params.diggable) {
					infostream << "Server: " << player->getName()
							<< " completed digging " << PP(p_under)
							<< ", which is not diggable with tool; not digging."
							<< std::endl;
					is_valid_dig = false;

					m_script->on_cheat(playersao, "dug_unbreakable");
				}


				if (!is_valid_dig) {

				}

				else if (params.time > 2.0 && nocheat_t * 1.2 > params.time) {


					playersao->getDigPool().grab(params.time);
				}


				else if (playersao->getDigPool().grab(params.time)) {

				}

				else {
					infostream << "Server: " << player->getName()
							<< " completed digging " << PP(p_under)
							<< "too fast; not digging." << std::endl;
					is_valid_dig = false;

					m_script->on_cheat(playersao, "dug_too_fast");
				}
			}


			if (is_valid_dig && n.getContent() != CONTENT_IGNORE)
				m_script->node_on_dig(p_under, n, playersao);

			v3s16 blockpos = getNodeBlockPos(floatToInt(pointed_pos_under, BS));
			RemoteClient *client = getClient(peer_id);

			if (m_env->getMap().getNode(p_under).getContent() != CONTENT_AIR) {

				client->SetBlockNotSent(blockpos);
			}
			else {
				client->ResendBlockIfOnWire(blockpos);
			}
		}
	}


	else if (action == INTERACT_PLACE) {
		ItemStack selected_item;
		playersao->getWieldedItem(&selected_item, nullptr);


		if (pointed.type == POINTEDTHING_NODE &&
				selected_item.getDefinition(m_itemdef).type == ITEM_NODE)
			getClient(peer_id)->m_time_from_building = 0.0;

		if (pointed.type == POINTEDTHING_OBJECT) {


			if (pointed_object->isGone())
				return;

			actionstream << player->getName() << " right-clicks object "
					<< pointed.object_id << ": "
					<< pointed_object->getDescription() << std::endl;


			if (m_script->item_OnSecondaryUse(
					selected_item, playersao, pointed)) {
				if (playersao->setWieldedItem(selected_item)) {
					SendInventory(playersao, true);
				}
			}

			pointed_object->rightClick(playersao);
		} else if (m_script->item_OnPlace(
				selected_item, playersao, pointed)) {


			if (playersao->setWieldedItem(selected_item)) {
				SendInventory(playersao, true);
			}
		}


		RemoteClient *client = getClient(peer_id);
		v3s16 blockpos = getNodeBlockPos(floatToInt(pointed_pos_above, BS));
		v3s16 blockpos2 = getNodeBlockPos(floatToInt(pointed_pos_under, BS));
		if (!selected_item.getDefinition(m_itemdef).node_placement_prediction.empty()) {
			client->SetBlockNotSent(blockpos);
			if (blockpos2 != blockpos) {
				client->SetBlockNotSent(blockpos2);
			}
		}
		else {
			client->ResendBlockIfOnWire(blockpos);
			if (blockpos2 != blockpos) {
				client->ResendBlockIfOnWire(blockpos2);
			}
		}
	}


	else if (action == INTERACT_USE) {
		ItemStack selected_item;
		playersao->getWieldedItem(&selected_item, nullptr);

		actionstream << player->getName() << " uses " << selected_item.name
				<< ", pointing at " << pointed.dump() << std::endl;

		if (m_script->item_OnUse(
				selected_item, playersao, pointed)) {

			if (playersao->setWieldedItem(selected_item)) {
				SendInventory(playersao, true);
			}
		}

	}


	else if (action == INTERACT_ACTIVATE) {
		ItemStack selected_item;
		playersao->getWieldedItem(&selected_item, nullptr);

		actionstream << player->getName() << " activates "
				<< selected_item.name << std::endl;

		pointed.type = POINTEDTHING_NOTHING;

		if (m_script->item_OnSecondaryUse(
				selected_item, playersao, pointed)) {
			if (playersao->setWieldedItem(selected_item)) {
				SendInventory(playersao, true);
			}
		}
	}


	else {
		warningstream << "Server: Invalid action "
				<< action << std::endl;
	}
}
