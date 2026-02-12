Eigen::VectorXd ompl::geometric::VFRRT::getNewDirection(const base::State *qnear, const base::State *qrand)
{

    Eigen::VectorXd vrand(vfdim_);
    for (unsigned int i = 0; i < vfdim_; i++)
        vrand[i] = *si_->getStateSpace()->getValueAddressAtIndex(qrand, i) -
                   *si_->getStateSpace()->getValueAddressAtIndex(qnear, i);
    vrand /= si_->distance(qnear, qrand);


    Eigen::VectorXd vfield = vf_(qnear);
    const double lambdaScale = vfield.norm();


    if (lambdaScale < std::numeric_limits<float>::epsilon())
        return vrand;
    vfield /= lambdaScale;

    const double omega = biasedSampling(vrand, vfield, lambdaScale);

    return computeAlphaBeta(omega, vrand, vfield);
}
