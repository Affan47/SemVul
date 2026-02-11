declareArguments(nor_utils::Args& args)
	{
		BaseLearner::declareArguments(args);

		args.declareArgument("baselearnertype",
			"The name of the learner that serves as a basis for the product\n"
			"  and the number of base learners to be multiplied\n"
			"  Don't forget to add its parameters\n",
			2, "<baseLearnerType> <numBaseLearners>");

		args.declareArgument("updaterule",
			"The update weights in the UCT can be the 1-sqrt( 1- edge^2 ) [edge]\n"
			"  or the alpha [alphas]\n"
			"  or edgesquare [edgesquare]\n"
			"  Default is the first one\n",
			1, "<type>");

	}
