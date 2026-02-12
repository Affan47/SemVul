socket_close(int code, Datum arg)
{

	if (MyProcPort != NULL)
	{
#ifdef ENABLE_GSS


		if (MyProcPort->gss)
		{
			OM_uint32	min_s;

			if (MyProcPort->gss->ctx != GSS_C_NO_CONTEXT)
				gss_delete_sec_context(&min_s, &MyProcPort->gss->ctx, NULL);

			if (MyProcPort->gss->cred != GSS_C_NO_CREDENTIAL)
				gss_release_cred(&min_s, &MyProcPort->gss->cred);
		}
#endif


		secure_close(MyProcPort);


		MyProcPort->sock = PGINVALID_SOCKET;
	}
}
