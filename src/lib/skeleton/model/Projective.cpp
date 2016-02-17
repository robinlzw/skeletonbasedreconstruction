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
 *  \file Projective.cpp
 *  \brief Defines skeleton projective model
 *  \author Bastien Durix
 */

#include "Projective.h"

skeleton::model::Projective::Projective(const mathtools::affine::Frame<3>::Ptr frame) : m_frame(frame)
{}

skeleton::model::Projective::Projective(const Projective &model) : m_frame(model.m_frame)
{}

const mathtools::affine::Frame<3>::Ptr skeleton::model::Projective::getFrame() const
{
	return m_frame;
}

Eigen::Matrix<double,skeleton::model::meta<skeleton::model::Projective>::stordim,1> skeleton::model::Projective::toVec(
		const mathtools::geometry::euclidian::HyperSphere<2> &) const
{
	throw std::logic_error("skeleton::model::Projective::toVec: not implemented in that skeleton type");
}

mathtools::affine::Point<2> skeleton::model::Projective::toObj(
		const Eigen::Matrix<double,skeleton::model::meta<skeleton::model::Projective>::stordim,1> &,
		const mathtools::affine::Point<2> &) const
{
	throw std::logic_error("skeleton::model::Projective::toObj: not implemented in that skeleton type");
}

mathtools::geometry::euclidian::HyperSphere<2> skeleton::model::Projective::toObj(
		const Eigen::Matrix<double,skeleton::model::meta<skeleton::model::Projective>::stordim,1> &,
		const mathtools::geometry::euclidian::HyperSphere<2> &) const
{
	throw std::logic_error("skeleton::model::Projective::toObj: not implemented in that skeleton type");
}
