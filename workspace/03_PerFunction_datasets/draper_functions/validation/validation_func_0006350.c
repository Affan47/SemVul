DeallocatePacket( Packet *packet )
{
	if ( packet == 0 )
		return;

	if (packet->deleteData)
	{
		rakFree_Ex(packet->data, _FILE_AND_LINE_ );
		packet->~Packet();
		packetAllocationPoolMutex.Lock();
		packetAllocationPool.Release(packet,_FILE_AND_LINE_);
		packetAllocationPoolMutex.Unlock();
	}
	else
	{
		rakFree_Ex(packet, _FILE_AND_LINE_ );
	}
}
