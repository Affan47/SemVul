DrucInitCompiler ()
{
  int      TmpIndexMesure;
  int      IndexLayer;
  CurrentIndexDrucLayer = DRUC_UNDEFINED_LAYER;
  DrucCtmMax            = DRUC_UNDEFINED_CTM;

  for ( IndexLayer  = 0;
        IndexLayer  < RDS_MAX_LAYER;
        IndexLayer ++
      )
  {
    DrucStructRdsLayer [ IndexLayer ].RDS_INDEX  = DRUC_UNDEFINED_LAYER;
    DrucStructRdsLayer [ IndexLayer ].WIDTH      = DRUC_UNDEFINED_WIDTH;
    DrucStructRdsLayer [ IndexLayer ].CTM        = DRUC_UNDEFINED_CTM;
    DrucStructRdsLayer [ IndexLayer ].FLAGS      = DRUC_FLAG_LAYER_INTERDIT;
  }
  DrucStructRdsLayer [ DRUC_USER_LAYER_0 ].FLAGS = DRUC_FLAG_LAYER_LIBRE;
  DrucStructRdsLayer [ DRUC_USER_LAYER_1 ].FLAGS = DRUC_FLAG_LAYER_LIBRE;
  DrucStructRdsLayer [ DRUC_USER_LAYER_2 ].FLAGS = DRUC_FLAG_LAYER_LIBRE;

  DrucStructDefine.LAYER_DEST                    = DRUC_UNDEFINED_LAYER;
  DrucStructDefine.OP_COMPOSE                    = DRUC_UNDEFINED_OP_COMPOSE;
  DrucStructDefine.OP_UNAIRE                     = DRUC_UNDEFINED_OP_COMPOSE;
  DrucStructDefine.LAYER_1                       = DRUC_UNDEFINED_LAYER;
  DrucStructDefine.LAYER_2                       = DRUC_UNDEFINED_LAYER;
  DrucStructDefine.USER_LAYER_0                  = DRUC_UNDEFINED_LAYER;
  DrucStructDefine.USER_LAYER_1                  = DRUC_UNDEFINED_LAYER;
  DrucStructDefine.USER_LAYER_2                  = DRUC_UNDEFINED_LAYER;
  DrucStructDefine.USER_LAYER_NAME_0             = (char *)NULL;
  DrucStructDefine.USER_LAYER_NAME_1             = (char *)NULL;
  DrucStructDefine.USER_LAYER_NAME_2             = (char *)NULL;

  DrucStructRegle.LIST_REGLE_NUM                 = (DataList *)NULL;
  DrucStructRegle.INSTRUCTION                    = DRUC_UNDEFINED_INSTRUCTION;
  DrucStructRegle.LAYER_1                        = DRUC_UNDEFINED_LAYER;
  DrucStructRegle.LAYER_2                        = DRUC_UNDEFINED_LAYER;
  for ( TmpIndexMesure              = 0;
        TmpIndexMesure  < DRUC_MAX_MESURES;
        TmpIndexMesure ++
      )
  {
    DrucStructRegle.RELATION   [TmpIndexMesure ] = DRUC_UNDEFINED_RELATION;
    DrucStructRegle.REGLE_NUM  [TmpIndexMesure ] = DRUC_UNDEFINED_REGLE;
    DrucStructRegle.MESURE     [TmpIndexMesure ] = DRUC_UNDEFINED_MESURE;
    DrucStructRegle.OP_COMPARE [TmpIndexMesure ] = DRUC_UNDEFINED_OPERATEUR;
    DrucStructRegle.VALEUR     [TmpIndexMesure ] = DRUC_UNDEFINED_VALEUR;
  }
}
