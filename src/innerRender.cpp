/* GIMP Engine Plug-in Template
 * Copyright (C) 2000  Michael Natterer <mitch@gimp.org> (the "Author").
 * Copyright 2016 Lloyd Konneker
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the Author of the
 * Software shall not be used in advertising or otherwise to promote the
 * sale, use or other dealings in this Software without prior written
 * authorization from the Author.
 */

#include "/usr/local/include/libsaliency.hpp"
#include "innerRender.hpp"


void detectSaliency(cv::Mat matGrayscaleChar)	// In Out
{
  // Require
  assert(matGrayscaleChar.channels()==1);
  assert(matGrayscaleChar.depth()==CV_8UC1);

  // convert type of in mat from char to float expected by libsaliency
  // Allocates a new Mat since size is larger
  // Default is no scaling: 1-255 => 1.0-255.0 ??
  cv::Mat1f matFloat;
  matGrayscaleChar.convertTo(matFloat, CV_32F);

  assert(matFloat.channels()==1);
  assert(matFloat.depth()==CV_32F);
  assert(matFloat.size() == matGrayscaleChar.size() );
  assert(matFloat.total()*matFloat.elemSize() == 4*matGrayscaleChar.total()*matGrayscaleChar.elemSize());

  // invoke library
  sal::ImageSaliencyDetector detector(matFloat);
  detector.setSamplingPercentage(0.10f);
  detector.compute();
  detector.performPostProcessing();
  cv::Mat innermostResult = detector.getSaliencyMap();

  assert(innermostResult.type() == CV_32F);

  // Test: innermostResult all zeros
  // innermostResult.release();
  // innermostResult = cv::Mat(matGrayscaleChar.rows, matGrayscaleChar.cols, CV_32F, double(0));

  // matGrayscaleChar values are unchanged, so far (read only to algorithm.)
  // Convert innermostResult back to uchar into the input matGrayscaleChar.
  // Allocates new mat since size is reduced by four
  innermostResult.convertTo(matGrayscaleChar, CV_8UC1);

  // matGrayscaleChar = cv::Scalar(50);	// Test.  Set uniform pixelel.

  // Ensure matGrayscaleChar is a saliency map of one channel of depth uchar.
  assert(matGrayscaleChar.channels() == 1);
  assert(matGrayscaleChar.type() == CV_8UC1);
}
