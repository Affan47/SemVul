cmsBool OptimizeMatrixShaper(cmsPipeline** Lut, cmsUInt32Number Intent, cmsUInt32Number* InputFormat, cmsUInt32Number* OutputFormat, cmsUInt32Number* dwFlags)
{
       cmsStage* Curve1, *Curve2;
       cmsStage* Matrix1, *Matrix2;
       cmsMAT3 res;
       cmsBool IdentityMat;
       cmsPipeline* Dest, *Src;
       cmsFloat64Number* Offset;


       if (T_CHANNELS(*InputFormat) != 3 || T_CHANNELS(*OutputFormat) != 3) return FALSE;


       if (!_cmsFormatterIs8bit(*InputFormat)) return FALSE;


       Src = *Lut;


       IdentityMat = FALSE;
       if (cmsPipelineCheckAndRetreiveStages(Src, 4,
              cmsSigCurveSetElemType, cmsSigMatrixElemType, cmsSigMatrixElemType, cmsSigCurveSetElemType,
              &Curve1, &Matrix1, &Matrix2, &Curve2)) {


              _cmsStageMatrixData* Data1 = (_cmsStageMatrixData*)cmsStageData(Matrix1);
              _cmsStageMatrixData* Data2 = (_cmsStageMatrixData*)cmsStageData(Matrix2);


              if (Data1->Offset != NULL) return FALSE;


              _cmsMAT3per(&res, (cmsMAT3*)Data2->Double, (cmsMAT3*)Data1->Double);


              Offset = Data2->Offset;


              if (_cmsMAT3isIdentity(&res) && Offset == NULL) {


                     IdentityMat = TRUE;
              }

       }
       else {

              if (cmsPipelineCheckAndRetreiveStages(Src, 3,
                     cmsSigCurveSetElemType, cmsSigMatrixElemType, cmsSigCurveSetElemType,
                     &Curve1, &Matrix1, &Curve2)) {

                     _cmsStageMatrixData* Data = (_cmsStageMatrixData*)cmsStageData(Matrix1);


                     memcpy(&res, Data->Double, sizeof(res));


                     Offset = Data->Offset;

                     if (_cmsMAT3isIdentity(&res) && Offset == NULL) {


                            IdentityMat = TRUE;
                     }
              }
              else
                     return FALSE;

       }


    Dest =  cmsPipelineAlloc(Src ->ContextID, Src ->InputChannels, Src ->OutputChannels);
    if (!Dest) return FALSE;


    if (!cmsPipelineInsertStage(Dest, cmsAT_BEGIN, cmsStageDup(Curve1)))
        goto Error;

    if (!IdentityMat) {

           if (!cmsPipelineInsertStage(Dest, cmsAT_END, cmsStageAllocMatrix(Dest->ContextID, 3, 3, (const cmsFloat64Number*)&res, Offset)))
                  goto Error;
    }

    if (!cmsPipelineInsertStage(Dest, cmsAT_END, cmsStageDup(Curve2)))
        goto Error;


    if (IdentityMat) {

        OptimizeByJoiningCurves(&Dest, Intent, InputFormat, OutputFormat, dwFlags);
    }
    else {
        _cmsStageToneCurvesData* mpeC1 = (_cmsStageToneCurvesData*) cmsStageData(Curve1);
        _cmsStageToneCurvesData* mpeC2 = (_cmsStageToneCurvesData*) cmsStageData(Curve2);


        *dwFlags |= cmsFLAGS_NOCACHE;


        SetMatShaper(Dest, mpeC1 ->TheCurves, &res, (cmsVEC3*) Offset, mpeC2->TheCurves, OutputFormat);
    }

    cmsPipelineFree(Src);
    *Lut = Dest;
    return TRUE;
Error:

    cmsPipelineFree(Dest);
    return FALSE;
}
