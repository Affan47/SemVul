P_PlayerInSpecialSector(player_t * player)
{
    sector_t *sector;
    static int pushTab[3] = {
        2048 * 5,
        2048 * 10,
        2048 * 25
    };

    sector = player->mo->subsector->sector;
    if (player->mo->z != sector->floorheight)
    {
        return;
    }
    switch (sector->special)
    {
        case 9:
            player->secretcount++;
            sector->special = 0;
            break;

        case 201:
        case 202:
        case 203:
            P_Thrust(player, ANG90, pushTab[sector->special - 201]);
            break;
        case 204:
        case 205:
        case 206:
            P_Thrust(player, 0, pushTab[sector->special - 204]);
            break;
        case 207:
        case 208:
        case 209:
            P_Thrust(player, ANG270, pushTab[sector->special - 207]);
            break;
        case 210:
        case 211:
        case 212:
            P_Thrust(player, ANG180, pushTab[sector->special - 210]);
            break;
        case 213:
        case 214:
        case 215:
            P_Thrust(player, ANG90 + ANG45, pushTab[sector->special - 213]);
            break;
        case 216:
        case 217:
        case 218:
            P_Thrust(player, ANG45, pushTab[sector->special - 216]);
            break;
        case 219:
        case 220:
        case 221:
            P_Thrust(player, ANG270 + ANG45, pushTab[sector->special - 219]);
            break;
        case 222:
        case 223:
        case 224:
            P_Thrust(player, ANG180 + ANG45, pushTab[sector->special - 222]);
            break;

        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:

            break;

        case 26:
        case 27:

            break;

        case 198:
        case 199:
        case 200:

            break;
        default:
            I_Error("P_PlayerInSpecialSector: "
                    "unknown special %i", sector->special);
    }
}
