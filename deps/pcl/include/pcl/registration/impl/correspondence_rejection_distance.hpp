/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2010, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *
 */
#ifndef PCL_REGISTRATION_IMPL_CORRESPONDENCE_REJECTION_DISTANCE_HPP_
#define PCL_REGISTRATION_IMPL_CORRESPONDENCE_REJECTION_DISTANCE_HPP_

void
pcl::registration::CorrespondenceRejectorDistance::applyRejection(pcl::registration::Correspondences &correspondences)
{
  unsigned int number_valid_correspondences = 0;
  correspondences.resize( input_correspondences_->size() );
  for ( unsigned int i = 0; i < input_correspondences_->size(); ++i )
  {
    if ( input_correspondences_->at(i).distance < max_distance_ )
    {
      correspondences[number_valid_correspondences] = input_correspondences_->at(i);
      ++number_valid_correspondences;
    }
  }
  correspondences.resize(number_valid_correspondences);
}

void
pcl::registration::CorrespondenceRejectorDistance::getCorrespondences(const pcl::registration::Correspondences& original_correspondences, pcl::registration::Correspondences& remaining_correspondences)
{
  unsigned int number_valid_correspondences = 0;
  remaining_correspondences.resize( original_correspondences.size() );
  for ( unsigned int i = 0; i < original_correspondences.size(); ++i )
  {
    if ( original_correspondences.at(i).distance < max_distance_ )
    {
      remaining_correspondences[number_valid_correspondences] = original_correspondences.at(i);
      ++number_valid_correspondences;
    }
  }
  remaining_correspondences.resize(number_valid_correspondences);
}

#endif /* PCL_REGISTRATION_IMPL_CORRESPONDENCE_REJECTION_DISTANCE_HPP_ */
