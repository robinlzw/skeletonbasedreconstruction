/*
Copyright (c) 2016 Bastien Durix

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


/**
 *  \file Tracker.h
 *  \brief Provides methods to acquire calibrated images
 *  \author Bastien Durix
 */

#ifndef _TRACKER_H_
#define _TRACKER_H_

#include <AR/ar.h>
#include <camera/Camera.h>

/**
 *  \brief Tracking methods
 */
namespace tracking
{
	/**
	 *  \brief Tracker class to estimate the position of the camera
	 */
	class Tracker
	{
		protected:
			/**
 			 *  \brief main ARToolKit structure, storing informations about camera, patterns, etc...
 			 */
			ARHandle *m_arhandle;
			
			/**
 			 *  \brief ARToolKit structure containing camera calibration
 			 */
			ARParamLT *m_arparamlt;
		public:
			/**
 			 *  \brief Constructor
 			 */
			Tracker();

			/**
 			 *  \brief Method initialising the tracker
 			 *
 			 *  \param cam  Camera acquiring the scene
 			 */
			void Init(const camera::Camera::Ptr cam);

			/**
 			 *  \brief Cleaning method
 			 */
			void Clean();

			/**
 			 *  \brief Destructor
 			 */
			~Tracker();
	};
}

#endif //_TRACKER_H_
