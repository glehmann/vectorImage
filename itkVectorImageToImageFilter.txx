/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkVectorImageToImageFilter.txx,v $
  Language:  C++
  Date:      $Date: 2005/06/15 16:13:48 $
  Version:   $Revision: 1.10 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkVectorImageToImageFilter_txx
#define _itkVectorImageToImageFilter_txx

#include "itkVectorImageToImageFilter.h"

namespace itk
{

/**
 *
 */
template <class TInputImage, class TOutputImage>
VectorImageToImageFilter<TInputImage, TOutputImage>
::VectorImageToImageFilter()
{
  m_ExtractComponentIndex = 0;
}

template <class TInputImage, class TOutputImage>
void
VectorImageToImageFilter<TInputImage, TOutputImage>
::BeforeThreadedGenerateData()
{
  unsigned int vl = this->GetInput()->GetVectorLength();
  if( m_ExtractComponentIndex >= vl )
    {itkExceptionMacro(<< "ExtractComponentIndex must be smaller than the image VectorLength.");}
  this->GetFunctor().SetExtractComponentIndex(m_ExtractComponentIndex);
}

/**
 *
 */
template <class TInputImage, class TOutputImage>
void 
VectorImageToImageFilter<TInputImage, TOutputImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "ExtractComponentIndex: "
     << static_cast<typename NumericTraits<unsigned int>::PrintType>(m_ExtractComponentIndex)
     << std::endl;
}


} // end namespace itk

#endif
