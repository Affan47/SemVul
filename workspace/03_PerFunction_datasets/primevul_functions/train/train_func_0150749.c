void CClient::Run()
{
	m_LocalStartTime = time_get();
	m_SnapshotParts = 0;


	{
		if(SDL_Init(0) < 0)
		{
			dbg_msg("client", "unable to init SDL base: %s", SDL_GetError());
			return;
		}

		atexit(SDL_Quit);
	}


	{
		if(g_Config.m_GfxThreaded)
			m_pGraphics = CreateEngineGraphicsThreaded();
		else
			m_pGraphics = CreateEngineGraphics();

		bool RegisterFail = false;
		RegisterFail = RegisterFail || !Kernel()->RegisterInterface(static_cast<IEngineGraphics*>(m_pGraphics));
		RegisterFail = RegisterFail || !Kernel()->RegisterInterface(static_cast<IGraphics*>(m_pGraphics));

		if(RegisterFail || m_pGraphics->Init() != 0)
		{
			dbg_msg("client", "couldn't init graphics");
			return;
		}
	}


	m_SoundInitFailed = Sound()->Init() != 0;


	{
		NETADDR BindAddr;
		if(g_Config.m_Bindaddr[0] && net_host_lookup(g_Config.m_Bindaddr, &BindAddr, NETTYPE_ALL) == 0)
		{

			BindAddr.type = NETTYPE_ALL;
		}
		else
		{
			mem_zero(&BindAddr, sizeof(BindAddr));
			BindAddr.type = NETTYPE_ALL;
		}
		if(!m_NetClient.Open(BindAddr, BindAddr.port ? 0 : NETCREATE_FLAG_RANDOMPORT))
		{
			dbg_msg("client", "couldn't open socket(net)");
			return;
		}
		BindAddr.port = 0;
		if(!m_ContactClient.Open(BindAddr, 0))
		{
			dbg_msg("client", "couldn't open socket(contact)");
			return;
		}
	}


	Kernel()->RequestInterface<IEngineTextRender>()->Init();


	Input()->Init();


	MasterServer()->RefreshAddresses(m_ContactClient.NetType());


	m_pEditor->Init();


	if(!LoadData())
		return;

	GameClient()->OnInit();

	char aBuf[256];
	str_format(aBuf, sizeof(aBuf), "version %s", GameClient()->NetVersion());
	m_pConsole->Print(IConsole::OUTPUT_LEVEL_STANDARD, "client", aBuf);


	m_FpsGraph.Init(0.0f, 200.0f);


	g_Config.m_ClEditor = 0;

	Input()->MouseModeRelative();


	m_pConsole->StoreCommands(false);

	while (1)
	{

		VersionUpdate();


		if(m_aCmdConnect[0])
		{
			str_copy(g_Config.m_UiServerAddress, m_aCmdConnect, sizeof(g_Config.m_UiServerAddress));
			Connect(m_aCmdConnect);
			m_aCmdConnect[0] = 0;
		}


		if(Input()->Update())
			break;


		Sound()->Update();


		if(!m_pGraphics->WindowActive())
		{
			if(m_WindowMustRefocus == 0)
				Input()->MouseModeAbsolute();
			m_WindowMustRefocus = 1;
		}
		else if (g_Config.m_DbgFocus && Input()->KeyPressed(KEY_ESCAPE))
		{
			Input()->MouseModeAbsolute();
			m_WindowMustRefocus = 1;
		}


		if(m_WindowMustRefocus && m_pGraphics->WindowActive())
		{
			if(m_WindowMustRefocus < 3)
			{
				Input()->MouseModeAbsolute();
				m_WindowMustRefocus++;
			}

			if(m_WindowMustRefocus >= 3 || Input()->KeyPressed(KEY_MOUSE_1))
			{
				Input()->MouseModeRelative();
				m_WindowMustRefocus = 0;
			}
		}


		if(Input()->KeyPressed(KEY_LCTRL) && Input()->KeyPressed(KEY_LSHIFT) && Input()->KeyPressed('q'))
		{
			Quit();
			break;
		}

		if(Input()->KeyPressed(KEY_LCTRL) && Input()->KeyPressed(KEY_LSHIFT) && Input()->KeyDown('d'))
			g_Config.m_Debug ^= 1;

		if(Input()->KeyPressed(KEY_LCTRL) && Input()->KeyPressed(KEY_LSHIFT) && Input()->KeyDown('g'))
			g_Config.m_DbgGraphs ^= 1;

		if(Input()->KeyPressed(KEY_LCTRL) && Input()->KeyPressed(KEY_LSHIFT) && Input()->KeyDown('e'))
		{
			g_Config.m_ClEditor = g_Config.m_ClEditor^1;
			Input()->MouseModeRelative();
		}


		{
			if(g_Config.m_ClEditor)
			{
				if(!m_EditorActive)
				{
					GameClient()->OnActivateEditor();
					m_EditorActive = true;
				}
			}
			else if(m_EditorActive)
				m_EditorActive = false;

			Update();

			if(!g_Config.m_GfxAsyncRender || m_pGraphics->IsIdle())
			{
				m_RenderFrames++;


				int64 Now = time_get();
				m_RenderFrameTime = (Now - m_LastRenderTime) / (float)time_freq();
				if(m_RenderFrameTime < m_RenderFrameTimeLow)
					m_RenderFrameTimeLow = m_RenderFrameTime;
				if(m_RenderFrameTime > m_RenderFrameTimeHigh)
					m_RenderFrameTimeHigh = m_RenderFrameTime;
				m_FpsGraph.Add(1.0f/m_RenderFrameTime, 1,1,1);

				m_LastRenderTime = Now;

				if(g_Config.m_DbgStress)
				{
					if((m_RenderFrames%10) == 0)
					{
						if(!m_EditorActive)
							Render();
						else
						{
							m_pEditor->UpdateAndRender();
							DebugRender();
						}
						m_pGraphics->Swap();
					}
				}
				else
				{
					if(!m_EditorActive)
						Render();
					else
					{
						m_pEditor->UpdateAndRender();
						DebugRender();
					}
					m_pGraphics->Swap();
				}
			}
		}

		AutoScreenshot_Cleanup();


		if(State() == IClient::STATE_QUITING)
			break;


		if(g_Config.m_ClCpuThrottle)
			thread_sleep(g_Config.m_ClCpuThrottle);
		else if(g_Config.m_DbgStress || !m_pGraphics->WindowActive())
			thread_sleep(5);

		if(g_Config.m_DbgHitch)
		{
			thread_sleep(g_Config.m_DbgHitch);
			g_Config.m_DbgHitch = 0;
		}


		m_LocalTime = (time_get()-m_LocalStartTime)/(float)time_freq();
	}

	GameClient()->OnShutdown();
	Disconnect();

	m_pGraphics->Shutdown();
	m_pSound->Shutdown();


	{
		SDL_Quit();
	}
}
