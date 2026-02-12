static inline int MqttIsPubRespPacket(int packet_type)
{
    return (packet_type == MQTT_PACKET_TYPE_PUBLISH_ACK  ||
            packet_type == MQTT_PACKET_TYPE_PUBLISH_REC  ||
            packet_type == MQTT_PACKET_TYPE_PUBLISH_REL  ||
            packet_type == MQTT_PACKET_TYPE_PUBLISH_COMP );
}
