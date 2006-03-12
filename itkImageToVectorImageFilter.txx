/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkImageToVectorImageFilter.txx,v $
  Language:  C++
  Date:      $Date: 2006/03/05 13:15:39 $
  Version:   $Revision: 1.14 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkImageToVectorImageFilter_txx
#define _itkImageToVectorImageFilter_txx
#include "itkImageToVectorImageFilter.h"

#include "itkExceptionObject.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkImageRegionIterator.h"
#include "itkImageLinearConstIteratorWithIndex.h"
#include "itkPasteImageFilter.h"
#include "itkImportImageContainer.h"
#include "itkNumericTraitsRGBPixel.h"

namespace itk {

template<class TInputImage, class TOutputImage>
ImageToVectorImageFilter<TInputImage, TOutputImage>
::ImageToVectorImageFilter()
{
  this->SetNumberOfRequiredInputs( 1 );
}

template<class TInputImage, class TOutputImage>
void
ImageToVectorImageFilter<TInputImage, TOutputImage>
::AllocateOutputs()
{
  OutputImagePointer outputPtr;

  // Allocate the output memory
  for (unsigned int i=0; i < this->GetNumberOfOutputs(); i++)
    {
    outputPtr = this->GetOutput(i);
    outputPtr->SetBufferedRegion(outputPtr->GetRequestedRegion());
    outputPtr->SetVectorLength( this->GetNumberOfInputs() );
    outputPtr->Allocate();
    }
}

template<class TInputImage, class TOutputImage>
void
ImageToVectorImageFilter<TInputImage, TOutputImage>
:: BeforeThreadedGenerateData()
{
  for( int i=1; i<this->GetNumberOfInputs(); i++)
    {
    if ( this->GetInput(0)->GetRequestedRegion().GetSize() != this->GetInput(i)->GetRequestedRegion().GetSize() )
      { itkExceptionMacro( << "All the input images must have the same size." ); }
    }
}

template<class TInputImage, class TOutputImage>
void
ImageToVectorImageFilter<TInputImage, TOutputImage>
:: ThreadedGenerateData(const OutputImageRegionType& outputRegionForThread, int threadId )
{
  const unsigned int numberOfInputImages = 
    static_cast< unsigned int >( this->GetNumberOfInputs() );
  
  OutputImagePointer outputPtr = this->GetOutput();
  ImageRegionIterator<TOutputImage> outputIt(outputPtr, outputRegionForThread);


  typedef ImageRegionConstIterator<TInputImage> ImageRegionConstIteratorType;
  std::vector< ImageRegionConstIteratorType * > inputItrVector;
  inputItrVector.reserve(numberOfInputImages);
  
  for (unsigned int i=0; i < numberOfInputImages; ++i)
    {
    InputImagePointer inputPtr =
      dynamic_cast<TInputImage*>( ProcessObject::GetInput( i ) );

    ImageRegionConstIteratorType *inputIt = new ImageRegionConstIteratorType(inputPtr,outputRegionForThread);
    inputItrVector[i] = reinterpret_cast< ImageRegionConstIteratorType * >( inputIt );
    inputItrVector[i]->GoToBegin();
    }
  ProgressReporter progress(this, threadId, outputRegionForThread.GetNumberOfPixels());
     
  outputIt.GoToBegin();
  
  while( !inputItrVector[0]->IsAtEnd())  
    {
    OutputPixelType p( numberOfInputImages );
    for (unsigned int i=0; i < numberOfInputImages; i++)
      {
      p[i] = inputItrVector[i]->Get();
      ++(*inputItrVector[i]);
      }
    outputIt.Set(p );
    ++outputIt;
    progress.CompletedPixel();
    }
  
  for (unsigned int i=0; i < numberOfInputImages; ++i)
    { delete inputItrVector[i]; }
}


}// end namespace itk
#endif
