int MqttClient_Disconnect_ex(MqttClient *client, MqttDisconnect *disconnect)
{
    int rc, len;


    if (client == NULL) {
        return MQTT_CODE_ERROR_BAD_ARG;
    }

#ifdef WOLFMQTT_V5
    if (disconnect != NULL) {

        disconnect->protocol_level = client->protocol_level;
    }
#endif

#ifdef WOLFMQTT_MULTITHREAD

    rc = wm_SemLock(&client->lockSend);
    if (rc != 0) {
        return rc;
    }
#endif


    rc = MqttEncode_Disconnect(client->tx_buf, client->tx_buf_len, disconnect);
#ifdef WOLFMQTT_DEBUG_CLIENT
    PRINTF("MqttClient_EncodePacket: Len %d, Type %s (%d), ID %d, QoS %d",
        rc, MqttPacket_TypeDesc(MQTT_PACKET_TYPE_DISCONNECT),
        MQTT_PACKET_TYPE_DISCONNECT, 0, 0);
#endif
    if (rc <= 0) {
    #ifdef WOLFMQTT_MULTITHREAD
        wm_SemUnlock(&client->lockSend);
    #endif
        return rc;
    }
    len = rc;


    rc = MqttPacket_Write(client, client->tx_buf, len);
#ifdef WOLFMQTT_MULTITHREAD
    wm_SemUnlock(&client->lockSend);
#endif
    if (rc != len) {
        return rc;
    }


    return MQTT_CODE_SUCCESS;
}
