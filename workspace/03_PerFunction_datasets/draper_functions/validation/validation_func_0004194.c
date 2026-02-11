spni_energy(const FunDensProp* dp, const struct vwn_params* para,
            const struct vwn_params* ferro)
{
    real ep_p[2], ep_f[2], ep_i[2], zeta, f_zeta, delta;
    real rhoa = dp->rhoa, rhob = dp->rhob, rho;

    if(rhoa<VWN_ZERO) rhoa = 1e-40;
    if(rhob<VWN_ZERO) rhob = 1e-40;
    rho = rhoa + rhob;
    vwn_en_pot(ep_p, rho, 0, para);

    if( FABS(dp->rhoa - dp->rhob)<VWN_ZERO) return ep_p[0]*rho;
    vwn_en_pot(ep_f, rho, 0, ferro);
    vwn_en_pot(ep_i, rho, 0, &vwn_interp);

    zeta   = (dp->rhoa-dp->rhob)/rho;
    f_zeta = SPINPOLF*(POW(1+zeta,FOURTHREE)+POW(1-zeta,FOURTHREE)-2.0);
    delta  = f_zeta*(ep_f[0]-ep_p[0]);

    return (ep_p[0]+ delta)*rho;
}
