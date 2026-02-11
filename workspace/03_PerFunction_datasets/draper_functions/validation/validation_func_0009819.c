consumer(void* param)
	{
		struct __queue_test* pTest=(struct __queue_test *)param;
		UINT32 count=0;
		UINT32 aktSize;
		do
			{
				aktSize=rand();
				aktSize%=0xFFFF;
				if(pTest->pQueue->getOrWait(pTest->buff+count,&aktSize)!=E_SUCCESS)
					THREAD_RETURN_ERROR;
				count+=aktSize;
				pTest->len-=aktSize;
			}while(pTest->len>10);
		THREAD_RETURN_SUCCESS;
	}
