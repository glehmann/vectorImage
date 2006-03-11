/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkVectorImageToImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2004/11/29 22:18:43 $
  Version:   $Revision: 1.11 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkVectorImageToImageFilter_h
#define __itkVectorImageToImageFilter_h
#include "itkVectorImage.h"

#include "itkUnaryFunctorImageFilter.h"

namespace itk
{

namespace Functor {  
 
template< typename TInput >
class VectorImageToImageFunctor
{
public:
  VectorImageToImageFunctor() {}
  ~VectorImageToImageFunctor() {}

  void SetExtractComponentIndex( unsigned int idx )
    { m_ExtractComponentIndex = idx; }

  inline typename TInput::ValueType operator()( const typename TInput::PixelType & x )
    { return x[m_ExtractComponentIndex]; }

  bool operator != (const VectorImageToImageFunctor & l) const
    { return l.m_ExtractComponentIndex == m_ExtractComponentIndex; }

private:
  unsigned int  m_ExtractComponentIndex;
}; 

}  // end namespace functor


/** \class VectorImageToImageFilter
 * \brief Invert intensity of an image 
 *
 * VectorImageToImageFilter invert intensity of pixels by subtracting pixel value
 * to a maximum value. The maximum value can be set with SetExtractComponentIndex and defaults
 * the maximum of input pixel type.
 * This filter can be used to invert, for example, a binary image, a distance map, etc.
 *
 * \author Gaëtan Lehmann. Biologie du Développement et de la Reproduction, INRA de Jouy-en-Josas, France.
 *
 * \sa IntensityWindowingImageFilter ShiftScaleImageFilter
 * \ingroup IntensityImageFilters  Multithreaded
 *
 */
template <typename TOutputImage>
class ITK_EXPORT VectorImageToImageFilter :
    public
UnaryFunctorImageFilter< VectorImage< typename TOutputImage::PixelType, TOutputImage::ImageDimension>, TOutputImage, 
                        typename Functor::VectorImageToImageFunctor< VectorImage< typename TOutputImage::PixelType, TOutputImage::ImageDimension > > >
{
public:
  /** Standard class typedefs. */
  typedef VectorImageToImageFilter  Self;
  typedef UnaryFunctorImageFilter< VectorImage< typename TOutputImage::PixelType, TOutputImage::ImageDimension>, TOutputImage, 
                        typename Functor::VectorImageToImageFunctor< VectorImage< typename TOutputImage::PixelType, TOutputImage::ImageDimension > > >  Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  typedef typename TOutputImage::PixelType OutputPixelType;

  /** Runtime information support. */
  itkTypeMacro(VectorImageToImageFilter, UnaryFunctorImageFilter);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);
  
  itkSetMacro( ExtractComponentIndex, unsigned int );
  itkGetConstReferenceMacro( ExtractComponentIndex, unsigned int );

  /** Print internal ivars */
  void PrintSelf(std::ostream& os, Indent indent) const;
  
  /** Process to execute before entering the multithreaded section */
  void BeforeThreadedGenerateData(void);

protected:
  VectorImageToImageFilter();
  virtual ~VectorImageToImageFilter() {};

private:
  VectorImageToImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  unsigned int        m_ExtractComponentIndex;
};


  
} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkVectorImageToImageFilter.txx"
#endif
  
#endif
