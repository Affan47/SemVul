thread_grabbing(TThreadParam &p)
{
	try
	{
		CFileGZOutputStream f_out_rawlog;
		if (arg_out_rawlog.isSet()) {
			if (!f_out_rawlog.open(arg_out_rawlog.getValue()))
				THROW_EXCEPTION_CUSTOM_MSG1("Error creating output rawlog file: %s", arg_out_rawlog.getValue().c_str())
		}

		mrpt::hwdrivers::CVelodyneScanner velodyne;

		if (arg_verbose.isSet())
			velodyne.enableVerbose(true);


		velodyne.setModelName( mrpt::utils::TEnumType<mrpt::hwdrivers::CVelodyneScanner::model_t>::name2value( arg_model.getValue() ) );
		if (arg_ip_filter.isSet())  velodyne.setDeviceIP( arg_ip_filter.getValue() );
		if (arg_in_pcap.isSet())    velodyne.setPCAPInputFile(arg_in_pcap.getValue());
		if (arg_out_pcap.isSet())   velodyne.setPCAPOutputFile(arg_out_pcap.getValue());


		if (arg_calib_file.isSet())
		{
			mrpt::obs::VelodyneCalibration calib;
			if (!calib.loadFromXMLFile(arg_calib_file.getValue()))
				throw std::runtime_error("Aborting: error loading calibration file.");
			velodyne.setCalibration(calib);
		}


		cout << "Calling CVelodyneScanner::initialize()...";
		velodyne.initialize();
		cout << "OK\n";

		cout << "Waiting for first data packets (Press CTRL+C to abort)...\n";

		CTicTac tictac;
		int nScans = 0;
		bool hard_error=false;

		while (!hard_error && !p.quit)
		{

			CObservationVelodyneScanPtr  obs;
			CObservationGPSPtr           obs_gps;

			hard_error = !velodyne.getNextObservation(obs,obs_gps);


			if (f_out_rawlog.fileOpenCorrectly())
			{
				if (obs) f_out_rawlog << *obs;
				if (obs_gps) f_out_rawlog << *obs_gps;
			}

			if (obs)      {p.new_obs.set(obs); nScans++;}
			if (obs_gps)  p.new_obs_gps.set(obs_gps);

			if (p.pushed_key!=0)
			{
				switch (p.pushed_key)
				{
					case 27:
						p.quit = true;
						break;
				}


				p.pushed_key = 0;
			}

			if (nScans>5)
			{
				p.Hz = nScans / tictac.Tac();
				nScans=0;
				tictac.Tic();
			}
		}
	}
	catch(std::exception &e)
	{
		cout << "Exception in Velodyne thread: " << e.what() << endl;
		p.quit = true;
	}
}
