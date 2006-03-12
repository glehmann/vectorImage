/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkImageToVectorImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2004/07/12 15:44:13 $
  Version:   $Revision: 1.2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkImageToVectorImageFilter_h
#define __itkImageToVectorImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkFixedArray.h"

namespace itk {

/** \class ImageToVectorImageFilter 
 * \brief 
 *
 */

template<class TInputImage, class TOutputImage>
class ITK_EXPORT ImageToVectorImageFilter : 
    public ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard Self typedef */
  typedef ImageToVectorImageFilter Self;
  typedef ImageToImageFilter<TInputImage,TOutputImage>  Superclass;
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);  

  /** Runtime information support. */
  itkTypeMacro(ImageToVectorImageFilter, ImageToImageFilter);
  
  /** Image pixel value typedef. */
  typedef typename TInputImage::PixelType   InputPixelType;
  typedef typename TOutputImage::PixelType   OutputPixelType;
  
  /** Image related typedefs. */
  typedef typename TInputImage::Pointer InputImagePointer;
  typedef typename TOutputImage::Pointer OutputImagePointer;

  typedef typename TInputImage::SizeType  InputSizeType;
  typedef typename TInputImage::IndexType  InputIndexType;
  typedef typename TInputImage::RegionType InputImageRegionType;
  typedef typename TOutputImage::SizeType  OutputSizeType;
  typedef typename TOutputImage::IndexType  OutputIndexType;
  typedef typename TOutputImage::RegionType OutputImageRegionType;


  /** Image related typedefs. */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension ) ;
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      TOutputImage::ImageDimension ) ;

protected:
  ImageToVectorImageFilter();
  ~ImageToVectorImageFilter(){};

  // the vector length must be set before allocating the output
  virtual void AllocateOutputs();

  // to check all the input images have the same size
  virtual void BeforeThreadedGenerateData();

  // the filter can be threaded
  virtual
  void ThreadedGenerateData(const OutputImageRegionType& outputRegionForThread,
                            int threadId );

private:
  ImageToVectorImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

} ; // end of class

} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkImageToVectorImageFilter.txx"
#endif

#endif
