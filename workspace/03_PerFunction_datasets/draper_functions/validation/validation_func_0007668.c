add(CAMuxSocket* pMuxSocket,const UINT8 peerIP[4],CAQueue* pQueueSend)
#else
fmHashTableEntry* CAFirstMixChannelList::add(CAMuxSocket* pMuxSocket,const UINT8 peerIP[4],CAQueue* pQueueSend,UINT8* strDialog)
#endif
	{
		INIT_STACK;
		BEGIN_STACK("CAFirstMixChannelList::add");

		if(pMuxSocket==NULL)
		{
			FINISH_STACK("CAFirstMixChannelList::add (null socket)");
			return NULL;
		}
		SINT32 hashkey=pMuxSocket->getSocket();
		if(hashkey>MAX_HASH_KEY-1||hashkey<0)
		{
			FINISH_STACK("CAFirstMixChannelList::add (invalid hash key)");
			return NULL;
		}
		m_Mutex.lock();
		fmHashTableEntry* pHashTableEntry=m_HashTable[hashkey];
		if(pHashTableEntry->pMuxSocket!=NULL)
		{
			FINISH_STACK("CAFirstMixChannelList::add (socket exists)");
			m_Mutex.unlock();
			return NULL;
		}


		pHashTableEntry->pMuxSocket=pMuxSocket;
		pHashTableEntry->pQueueSend=pQueueSend;
		pHashTableEntry->pControlMessageQueue = new CAQueue();
		pHashTableEntry->pControlChannelDispatcher = new CAControlChannelDispatcher(pHashTableEntry->pControlMessageQueue);
		pHashTableEntry->uAlreadySendPacketSize=-1;
		pHashTableEntry->cNumberOfChannels=0;
#ifdef LOG_TRAFFIC_PER_USER
		pHashTableEntry->trafficIn=0;
		pHashTableEntry->trafficOut=0;
		getcurrentTimeMillis(pHashTableEntry->timeCreated);
#endif
#ifdef LOG_DIALOG
		pHashTableEntry->strDialog=new UINT8[strlen((char*)strDialog)+1];
		strcpy((char*)pHashTableEntry->strDialog,(char*)strDialog);
#endif
		getRandom(&(pHashTableEntry->id));

#ifdef PAYMENT
		pHashTableEntry->pAccountingInfo=NULL;
#endif

		SAVE_STACK("CAFirstMixChannelList::add", "copying peer IP");
		memcpy(pHashTableEntry->peerIP,peerIP,4);
#ifdef DATA_RETENTION_LOG
		pHashTableEntry->peerPort=((CASocket*)pMuxSocket)->getPeerPort();
#endif
#ifdef DELAY_USERS
		m_pMutexDelayChannel->lock();
		pHashTableEntry->delayBucket=m_u32DelayChannelUnlimitTraffic;
		for(UINT32 i=0;i<MAX_POLLFD;i++)
			{
				if(m_pDelayBuckets[i]==NULL)
					{
						pHashTableEntry->delayBucketID=i;
						break;
					}
			}
		m_pDelayBuckets[pHashTableEntry->delayBucketID]=&pHashTableEntry->delayBucket;
		m_pMutexDelayChannel->unlock();
#endif

		SAVE_STACK("CAFirstMixChannelList::add", "inserting in connection list");

		if(m_listHashTableHead==NULL)
		{
			pHashTableEntry->list_HashEntries.next=NULL;
		}
		else
		{
			pHashTableEntry->list_HashEntries.next=m_listHashTableHead;
			m_listHashTableHead->list_HashEntries.prev=pHashTableEntry;
		}
		pHashTableEntry->list_HashEntries.prev=NULL;
		m_listHashTableHead=pHashTableEntry;

		SAVE_STACK("CAFirstMixChannelList::add", "inserting in timout list");

#ifdef PAYMENT
		pHashTableEntry->bRecoverTimeout = true;


#endif
		m_Mutex.unlock();

		FINISH_STACK("CAFirstMixChannelList::add");

		return pHashTableEntry;
	}
