save_combos
	(
	)
	{

	Shape_file_info *combos = files->create("combos.flx");
	try {
		if (combos)
			combos->flush();
	} catch (const exult_exception& e) {
		EStudio::Alert(e.what());
	}
	}
