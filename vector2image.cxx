#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCommand.h"
#include "itkSimpleFilterWatcher.h"

#include "itkVectorImage.h"
#include "itkVectorImageToImageFilter.h"


int main(int, char * argv[])
{
  const int dim = 2;

  typedef unsigned char PType;
  typedef itk::VectorImage< PType, dim > VIType;
  typedef itk::Image< PType, dim > IType;

  typedef itk::ImageFileReader< VIType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  typedef itk::VectorImageToImageFilter< IType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetExtractComponentIndex( atoi(argv[3]) );

  itk::SimpleFilterWatcher watcher(filter, "filter");

  typedef itk::ImageFileWriter< IType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( argv[2] );
  writer->Update();

  return 0;
}

