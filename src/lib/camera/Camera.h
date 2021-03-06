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
 *  \file  Camera.h
 *  \brief Defines a camera
 *  \author Bastien Durix
 */

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <memory>
#include "Intrinsics.h"
#include "Extrinsics.h"

/**
 *  \brief Camera tools
 */
namespace camera
{
	/**
	 *  \brief Defines camera object
	 */
	class Camera
	{
		public:
			/**
			 *  \brief Camera shared ponter
			 */
			using Ptr = std::shared_ptr<Camera>;
		protected:
			/**
			 *  \brief Camera intrinsic parameters
			 */
			Intrinsics::Ptr m_intrinsics;
			
			/**
			 *  \brief Camera extrinsic parameters
			 */
			Extrinsics::Ptr m_extrinsics;
		
		public:
			/**
			 *  \brief Constructor
			 *
			 *  \param intrinsics intrinsic parameters of the camera
			 *  \param extrinsics extrinsic parameters of the camera
			 */
			Camera(const Intrinsics::Ptr intrinsics, const Extrinsics::Ptr extrinsics);
			
			/**
			 *  \brief Intrinsics getter
			 *
			 *  \return intrinsic parameters
			 */
			const Intrinsics::Ptr getIntrinsics() const;
			
			/**
			 *  \brief Extrinsics getter
			 *
			 *  \return extrinsic parameters
			 */
			const Extrinsics::Ptr getExtrinsics() const;
	};
}


#endif //_CAMERA_H_
