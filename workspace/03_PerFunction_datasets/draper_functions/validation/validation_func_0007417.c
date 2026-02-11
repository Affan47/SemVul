getAdjustedInput(Real input)
    {
        Real adjusted = ControllerFunction<Real>::getAdjustedInput(input);


        if (!mDeltaInput)
        {
            adjusted += mPhase;
        }

        return adjusted;
    }
