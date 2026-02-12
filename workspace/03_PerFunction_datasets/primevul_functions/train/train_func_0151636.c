RFX_CONTEXT* rfx_context_new(BOOL encoder)
{
	HKEY hKey;
	LONG status;
	DWORD dwType;
	DWORD dwSize;
	DWORD dwValue;
	SYSTEM_INFO sysinfo;
	RFX_CONTEXT* context;
	wObject* pool;
	RFX_CONTEXT_PRIV* priv;
	context = (RFX_CONTEXT*)calloc(1, sizeof(RFX_CONTEXT));

	if (!context)
		return NULL;

	context->encoder = encoder;
	context->currentMessage.freeArray = TRUE;
	context->priv = priv = (RFX_CONTEXT_PRIV*)calloc(1, sizeof(RFX_CONTEXT_PRIV));

	if (!priv)
		goto error_priv;

	priv->log = WLog_Get("com.freerdp.codec.rfx");
	WLog_OpenAppender(priv->log);
#ifdef WITH_DEBUG_RFX
	WLog_SetLogLevel(priv->log, WLOG_DEBUG);
#endif
	priv->TilePool = ObjectPool_New(TRUE);

	if (!priv->TilePool)
		goto error_tilePool;

	pool = ObjectPool_Object(priv->TilePool);
	pool->fnObjectInit = rfx_tile_init;

	if (context->encoder)
	{
		pool->fnObjectNew = rfx_encoder_tile_new;
		pool->fnObjectFree = rfx_encoder_tile_free;
	}
	else
	{
		pool->fnObjectNew = rfx_decoder_tile_new;
		pool->fnObjectFree = rfx_decoder_tile_free;
	}


	priv->BufferPool = BufferPool_New(TRUE, (8192 + 32) * 3, 16);

	if (!priv->BufferPool)
		goto error_BufferPool;

#ifdef _WIN32
	{
		BOOL isVistaOrLater;
		OSVERSIONINFOA verinfo;
		ZeroMemory(&verinfo, sizeof(OSVERSIONINFOA));
		verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
		GetVersionExA(&verinfo);
		isVistaOrLater =
		    ((verinfo.dwMajorVersion >= 6) && (verinfo.dwMinorVersion >= 0)) ? TRUE : FALSE;
		priv->UseThreads = isVistaOrLater;
	}
#else
	priv->UseThreads = TRUE;
#endif
	GetNativeSystemInfo(&sysinfo);
	priv->MinThreadCount = sysinfo.dwNumberOfProcessors;
	priv->MaxThreadCount = 0;
	status = RegOpenKeyExA(HKEY_LOCAL_MACHINE, RFX_KEY, 0, KEY_READ | KEY_WOW64_64KEY, &hKey);

	if (status == ERROR_SUCCESS)
	{
		dwSize = sizeof(dwValue);

		if (RegQueryValueEx(hKey, _T("UseThreads"), NULL, &dwType, (BYTE*)&dwValue, &dwSize) ==
		    ERROR_SUCCESS)
			priv->UseThreads = dwValue ? 1 : 0;

		if (RegQueryValueEx(hKey, _T("MinThreadCount"), NULL, &dwType, (BYTE*)&dwValue, &dwSize) ==
		    ERROR_SUCCESS)
			priv->MinThreadCount = dwValue;

		if (RegQueryValueEx(hKey, _T("MaxThreadCount"), NULL, &dwType, (BYTE*)&dwValue, &dwSize) ==
		    ERROR_SUCCESS)
			priv->MaxThreadCount = dwValue;

		RegCloseKey(hKey);
	}

	if (priv->UseThreads)
	{


		primitives_get();
		priv->ThreadPool = CreateThreadpool(NULL);

		if (!priv->ThreadPool)
			goto error_threadPool;

		InitializeThreadpoolEnvironment(&priv->ThreadPoolEnv);
		SetThreadpoolCallbackPool(&priv->ThreadPoolEnv, priv->ThreadPool);

		if (priv->MinThreadCount)
			if (!SetThreadpoolThreadMinimum(priv->ThreadPool, priv->MinThreadCount))
				goto error_threadPool_minimum;

		if (priv->MaxThreadCount)
			SetThreadpoolThreadMaximum(priv->ThreadPool, priv->MaxThreadCount);
	}


	rfx_context_set_pixel_format(context, PIXEL_FORMAT_BGRX32);

	rfx_profiler_create(context);

	context->quantization_decode = rfx_quantization_decode;
	context->quantization_encode = rfx_quantization_encode;
	context->dwt_2d_decode = rfx_dwt_2d_decode;
	context->dwt_2d_encode = rfx_dwt_2d_encode;
	context->rlgr_decode = rfx_rlgr_decode;
	context->rlgr_encode = rfx_rlgr_encode;
	RFX_INIT_SIMD(context);
	context->state = RFX_STATE_SEND_HEADERS;
	context->expectedDataBlockType = WBT_FRAME_BEGIN;
	return context;
error_threadPool_minimum:
	CloseThreadpool(priv->ThreadPool);
error_threadPool:
	BufferPool_Free(priv->BufferPool);
error_BufferPool:
	ObjectPool_Free(priv->TilePool);
error_tilePool:
	free(priv);
error_priv:
	free(context);
	return NULL;
}
