GPS_Serial_Write_Packet(gpsdevh* fd, GPS_PPacket packet)
{
  size_t ret;
  const char* m1, *m2;
  GPS_Serial_OPacket ser_pkt;
  UC ser_pkt_data[MAX_GPS_PACKET_SIZE * sizeof(UC)];
  US bytes;

  if (packet->type >= 0xff || packet->n >= 0xff) {
    GPS_Error("SEND: Unsupported packet type/size for serial protocol");
    return 0;
  }

  ser_pkt.data = ser_pkt_data;
  bytes = Build_Serial_Packet(packet, &ser_pkt);

  GPS_Diag("Tx Data:");
  Diag(&ser_pkt.dle, 3);
  if ((ret=GPS_Serial_Write(fd,(const void*) &ser_pkt.dle,(size_t)3)) == -1) {
    perror("write");
    GPS_Error("SEND: Write to GPS failed");
    return 0;
  }
  if (ret!=3) {
    GPS_Error("SEND: Incomplete write to GPS");
    return 0;
  }

  Diag(ser_pkt.data, bytes);
  if ((ret=GPS_Serial_Write(fd,(const void*)ser_pkt.data,(size_t)bytes)) == -1) {
    perror("write");
    GPS_Error("SEND: Write to GPS failed");
    return 0;
  }
  if (ret!=bytes) {
    GPS_Error("SEND: Incomplete write to GPS");
    return 0;
  }


  Diag(&ser_pkt.chk, 3);

  GPS_Diag(": ");
  DiagS(ser_pkt.data, bytes);
  DiagS(&ser_pkt.chk, 3);
  m1 = Get_Pkt_Type(ser_pkt.type, ser_pkt.data[0], &m2);
  GPS_Diag("(%-8s%s)\n", m1, m2 ? m2 : "");

  if ((ret=GPS_Serial_Write(fd,(const void*)&ser_pkt.chk,(size_t)3)) == -1) {
    perror("write");
    GPS_Error("SEND: Write to GPS failed");
    return 0;
  }
  if (ret!=3) {
    GPS_Error("SEND: Incomplete write to GPS");
    return 0;
  }


  return 1;
}
