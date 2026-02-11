RegisterOptions(SmartPtr<RegisteredOptions> roptions)
  {
    roptions->AddBoundedNumberOption(
      "required_infeasibility_reduction",
      "Required reduction of infeasibility before leaving restoration phase.",
      0.0, false, 1.0, true,
      0.9,
      "The restoration phase algorithm is performed, until a point is found "
      "that is acceptable to the filter and the infeasibility has been "
      "reduced by at least the fraction given by this option.");
    roptions->AddLowerBoundedIntegerOption(
      "max_resto_iter",
      "Maximum number of successive iterations in restoration phase.",
      0, 3000000,
      "The algorithm terminates with an error message if the number of "
      "iterations successively taken in the restoration phase exceeds this "
      "number.");
  }
