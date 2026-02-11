RequestInformation(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** vtkNotUsed(inputVector),
  vtkInformationVector* outputVector )
{
  int newMetadata = 0;
  vtkInformation* outInfo = outputVector->GetInformationObject(0);


  if ( this->GetMetadataMTime() < this->FileNameMTime )
    {
    if ( this->Metadata->OpenFile( this->FileName ) )
      {


      if ( this->FindXMLFile() )
        {
        vtkExodusIIReaderParser *parser = vtkExodusIIReaderParser::New();
        this->Metadata->SetParser(parser);

        parser->Go(this->XMLFileName);
        parser->Delete();
        }

      this->Metadata->RequestInformation();


      if(this->Metadata->Parser && !this->Metadata->IsXMLMetadataValid())
        {
        this->Metadata->Parser->Delete();
        this->Metadata->Parser = 0;


        int numBlocks = this->Metadata->GetNumberOfObjectsOfType(vtkExodusIIReader::ELEM_BLOCK);
        for (int cc=0; cc < numBlocks; cc++)
          {
          vtkExodusIIReaderPrivate::BlockInfoType* binfop =
            static_cast<vtkExodusIIReaderPrivate::BlockInfoType*>(
              this->Metadata->GetSortedObjectInfo(vtkExodusIIReader::ELEM_BLOCK, cc));
          binfop->Name = binfop->OriginalName;
          }
        }


      this->Metadata->BuildSIL();
      this->SILUpdateStamp++;

      this->Metadata->CloseFile();
      newMetadata = 1;
      }
    else
      {
      vtkErrorMacro( "Unable to open file \"" << (this->FileName ? this->FileName : "(null)") << "\" to read metadata" );
      return 0;
      }
    }

  this->AdvertiseTimeSteps( outInfo );


  outInfo->Set(vtkDataObject::SIL(), this->Metadata->GetSIL());

  if ( newMetadata )
    {

    }

  return 1;
}
