#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCommand.h"
#include "itkSimpleFilterWatcher.h"

#include "itkVectorImage.h"
#include "itkImageToVectorImageFilter.h"


int main(int len, char * argv[])
{
  const int dim = 2;
  
  typedef unsigned char PType;
  typedef itk::VectorImage< PType, dim > VIType;
  typedef itk::Image< PType, dim > IType;

  typedef itk::ImageFileReader< IType > ReaderType;
  std::vector< ReaderType::Pointer > readerList;

  typedef itk::ImageToVectorImageFilter< IType, VIType > FilterType;
  FilterType::Pointer filter = FilterType::New();

  for(int i=1; i<len-1; i++)
    {
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( argv[i] );
    filter->SetInput( i-1, reader->GetOutput() );
    readerList.push_back( reader );
    }

  itk::SimpleFilterWatcher watcher(filter, "filter");

  typedef itk::ImageFileWriter< VIType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( argv[len-1] );
  writer->Update();

  return 0;
}

