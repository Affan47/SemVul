Euclidean2DFromCorrespondences2PointRobust(
    const Mat &x1,
    const Mat &x2,
    double max_error,
    Mat3 *H,
    vector<int> *inliers,
    double outliers_probability)
{

  double threshold = 2 * Square(max_error);
  double best_score = HUGE_VAL;
  typedef euclidean::euclidean2D::kernel::Kernel KernelH;
  KernelH kernel(x1, x2);
  *H = Estimate(kernel, MLEScorer<KernelH>(threshold), inliers,
                &best_score, outliers_probability);
  if (best_score == HUGE_VAL)
    return HUGE_VAL;
  else
    return std::sqrt(best_score / 2.0);
}
