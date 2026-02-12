cmsBool _MultiplyMatrix(cmsPipeline* Lut)
{
       cmsStage** pt1;
       cmsStage** pt2;
       cmsStage*  chain;
       cmsBool AnyOpt = FALSE;

       pt1 = &Lut->Elements;
       if (*pt1 == NULL) return AnyOpt;

       while (*pt1 != NULL) {

              pt2 = &((*pt1)->Next);
              if (*pt2 == NULL) return AnyOpt;

              if ((*pt1)->Implements == cmsSigMatrixElemType && (*pt2)->Implements == cmsSigMatrixElemType) {


                     _cmsStageMatrixData* m1 = (_cmsStageMatrixData*) cmsStageData(*pt1);
                     _cmsStageMatrixData* m2 = (_cmsStageMatrixData*) cmsStageData(*pt2);
                     cmsMAT3 res;


                     if (m1->Offset != NULL || m2 ->Offset != NULL ||
                            cmsStageInputChannels(*pt1) != 3 || cmsStageOutputChannels(*pt1) != 3 ||
                            cmsStageInputChannels(*pt2) != 3 || cmsStageOutputChannels(*pt2) != 3)
                            return FALSE;


                     _cmsMAT3per(&res, (cmsMAT3*)m2->Double, (cmsMAT3*)m1->Double);


                     chain = (*pt2)->Next;


                     _RemoveElement(pt2);
                     _RemoveElement(pt1);


                     if (!isFloatMatrixIdentity(&res)) {


                            cmsStage* Multmat = cmsStageAllocMatrix(Lut->ContextID, 3, 3, (const cmsFloat64Number*) &res, NULL);
                            if (Multmat == NULL) return FALSE;


                            Multmat->Next = chain;
                            *pt1 = Multmat;
                     }

                     AnyOpt = TRUE;
              }
              else
                     pt1 = &((*pt1)->Next);
       }

       return AnyOpt;
}
