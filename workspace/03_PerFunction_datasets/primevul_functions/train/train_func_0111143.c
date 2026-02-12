int psutil_get_nic_speed(int ifm_active) {


    switch(IFM_TYPE(ifm_active)) {
        case IFM_ETHER:
            switch(IFM_SUBTYPE(ifm_active)) {
#if defined(IFM_HPNA_1) && ((!defined(IFM_10G_LR)) \
    || (IFM_10G_LR != IFM_HPNA_1))

                case(IFM_HPNA_1):
                    return 1;
#endif

                case(IFM_10_T):
                case(IFM_10_2):
                case(IFM_10_5):
                case(IFM_10_STP):
                case(IFM_10_FL):
                    return 10;

                case(IFM_100_TX):
                case(IFM_100_FX):
                case(IFM_100_T4):
                case(IFM_100_VG):
                case(IFM_100_T2):
                    return 100;

                case(IFM_1000_SX):
                case(IFM_1000_LX):
                case(IFM_1000_CX):
#if defined(IFM_1000_TX) && !defined(PSUTIL_OPENBSD)

                case(IFM_1000_TX):
#endif
#ifdef IFM_1000_FX
                case(IFM_1000_FX):
#endif
#ifdef IFM_1000_T
                case(IFM_1000_T):
#endif
                    return 1000;
#if defined(IFM_10G_SR) || defined(IFM_10G_LR) || defined(IFM_10G_CX4) \
         || defined(IFM_10G_T)
#ifdef IFM_10G_SR
                case(IFM_10G_SR):
#endif
#ifdef IFM_10G_LR
                case(IFM_10G_LR):
#endif
#ifdef IFM_10G_CX4
                case(IFM_10G_CX4):
#endif
#ifdef IFM_10G_TWINAX
                case(IFM_10G_TWINAX):
#endif
#ifdef IFM_10G_TWINAX_LONG
                case(IFM_10G_TWINAX_LONG):
#endif
#ifdef IFM_10G_T
                case(IFM_10G_T):
#endif
                    return 10000;
#endif
#if defined(IFM_2500_SX)
#ifdef IFM_2500_SX
                case(IFM_2500_SX):
#endif
                    return 2500;
#endif

                default:
                    return 0;
            }
            break;

#ifdef IFM_TOKEN
        case IFM_TOKEN:
            switch(IFM_SUBTYPE(ifm_active)) {
                case IFM_TOK_STP4:
                case IFM_TOK_UTP4:
                    return 4;
                case IFM_TOK_STP16:
                case IFM_TOK_UTP16:
                    return 16;
#if defined(IFM_TOK_STP100) || defined(IFM_TOK_UTP100)
#ifdef IFM_TOK_STP100
                case IFM_TOK_STP100:
#endif
#ifdef IFM_TOK_UTP100
                case IFM_TOK_UTP100:
#endif
                    return 100;
#endif

                default:
                    return 0;
            }
            break;
#endif

#ifdef IFM_FDDI
        case IFM_FDDI:
            switch(IFM_SUBTYPE(ifm_active)) {

                default:
                    return 0;
            }
            break;
#endif
        case IFM_IEEE80211:
            switch(IFM_SUBTYPE(ifm_active)) {
                case IFM_IEEE80211_FH1:
                case IFM_IEEE80211_DS1:
                    return 1;
                case IFM_IEEE80211_FH2:
                case IFM_IEEE80211_DS2:
                    return 2;
                case IFM_IEEE80211_DS5:
                    return 5;
                case IFM_IEEE80211_DS11:
                    return 11;
                case IFM_IEEE80211_DS22:
                    return 22;

                default:
                    return 0;
            }
            break;

        default:
            return 0;
    }
}
