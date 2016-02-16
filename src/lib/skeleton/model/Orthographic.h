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
 *  \file Orthographic.h
 *  \brief Defines orthographic projective skeleton
 *  \author Bastien Durix
 */


#include <memory>
#include "MetaModel.h"
#include "Projective.h"

/**
 *  \brief Skeleton representations
 */
namespace skeleton
{
	/**
	 *  \brief Skeletal models
	 */
	namespace model
	{
		class Orthographic;
		
		/**
		 *  \brief Describe Orthographic model meta data
		 */
		template<>
		struct meta<Orthographic>
		{
			/**
			 *  \brief Describe storage dimension of the model
			 */
			static constexpr unsigned int stordim = 3;
		};

		/**
		 *  \brief Describe perspective skeleton model
		 */
		class Orthographic : public Projective
		{
			public:
				/**
				 *  \brief Shared pointer to the model
				 */
				using Ptr = std::shared_ptr<Orthographic>;
				
			public:
				/**
				 *  \brief Constructor
				 *
				 *  \param frame skeleton frame
				 */
				Orthographic(const mathtools::affine::Frame<3>::Ptr frame = mathtools::affine::Frame<3>::CanonicFrame());

				/**
				 *  \brief Copy constructor
				 *
				 *  \param model model to copy
				 */
				Orthographic(const Orthographic &model);

				/**
				 *  \brief Skeleton type getter
				 *
				 *  \return Skeleton type
				 */
				virtual Type getType() const;
		};
	}
}