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
 *  \file MarchingSquares.h
 *  \brief Extracts a boundary with marching square algorithm
 *  \author Bastien Durix
 */

#ifndef _MARCHINGSQUARES_H_
#define _MARCHINGSQUARES_H_

#include <shape/DiscreteShape.h>
#include <boundary/DiscreteBoundary2.h>

/**
 *  \brief Lots of algorithms
 */
namespace algorithm
{
	/**
	 *  \brief Boundary extraction
	 */
	namespace extractboundary
	{
		/**
		 *  \brief Extract boundary with marching squares algorithm
		 *
		 *  \param dissh discrete shape
		 *  \param step  step between each tested cell
		 *
		 *  \return boundary associated to dsicrete shape
		 */
		boundary::DiscreteBoundary<2>::Ptr MarchingSquare(const shape::DiscreteShape<2>::Ptr dissh, unsigned int step = 1);
	}
}

#endif //_MARCHINGSQUARES_H_
