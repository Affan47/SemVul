rend_mid_introduce(or_circuit_t *circ, const uint8_t *request,
                   size_t request_len)
{
  or_circuit_t *intro_circ;
  char serviceid[REND_SERVICE_ID_LEN_BASE32+1];
  char nak_body[1];

  log_info(LD_REND, "Received an INTRODUCE1 request on circuit %d",
           circ->p_circ_id);

  if (circ->_base.purpose != CIRCUIT_PURPOSE_OR || circ->_base.n_conn) {
    log_warn(LD_PROTOCOL,
             "Rejecting INTRODUCE1 on non-OR or non-edge circuit %d.",
             circ->p_circ_id);
    goto err;
  }


  if (request_len < (DIGEST_LEN+(MAX_NICKNAME_LEN+1)+REND_COOKIE_LEN+
                     DH_KEY_LEN+CIPHER_KEY_LEN+PKCS1_OAEP_PADDING_OVERHEAD)) {
    log_warn(LD_PROTOCOL, "Impossibly short INTRODUCE1 cell on circuit %d; "
             "responding with nack.",
             circ->p_circ_id);
    goto err;
  }

  base32_encode(serviceid, REND_SERVICE_ID_LEN_BASE32+1,
                (char*)request, REND_SERVICE_ID_LEN);


  intro_circ = circuit_get_intro_point((char*)request);
  if (!intro_circ) {
    log_info(LD_REND,
             "No intro circ found for INTRODUCE1 cell (%s) from circuit %d; "
             "responding with nack.",
             safe_str(serviceid), circ->p_circ_id);
    goto err;
  }

  log_info(LD_REND,
           "Sending introduction request for service %s "
           "from circ %d to circ %d",
           safe_str(serviceid), circ->p_circ_id,
           intro_circ->p_circ_id);


  if (relay_send_command_from_edge(0, TO_CIRCUIT(intro_circ),
                                   RELAY_COMMAND_INTRODUCE2,
                                   (char*)request, request_len, NULL)) {
    log_warn(LD_GENERAL,
             "Unable to send INTRODUCE2 cell to Tor client.");
    goto err;
  }

  if (relay_send_command_from_edge(0,TO_CIRCUIT(circ),
                                   RELAY_COMMAND_INTRODUCE_ACK,
                                   NULL,0,NULL)) {
    log_warn(LD_GENERAL, "Unable to send INTRODUCE_ACK cell to Tor client.");
    circuit_mark_for_close(TO_CIRCUIT(circ), END_CIRC_REASON_INTERNAL);
    return -1;
  }

  return 0;
 err:

  nak_body[0] = 1;
  if (relay_send_command_from_edge(0,TO_CIRCUIT(circ),
                                   RELAY_COMMAND_INTRODUCE_ACK,
                                   nak_body, 1, NULL)) {
    log_warn(LD_GENERAL, "Unable to send NAK to Tor client.");

    circuit_mark_for_close(TO_CIRCUIT(circ), END_CIRC_REASON_INTERNAL);
  }
  return -1;
}
