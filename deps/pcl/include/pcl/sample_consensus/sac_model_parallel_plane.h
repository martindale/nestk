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
 * $Id: sac_model_parallel_plane.h 35810 2011-02-08 00:03:46Z rusu $
 *
 */

#ifndef PCL_SAMPLE_CONSENSUS_MODEL_PARALLELPLANE_H_
#define PCL_SAMPLE_CONSENSUS_MODEL_PARALLELPLANE_H_

#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/common/common.h>

namespace pcl
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** \brief @b SampleConsensusModelParallelPlane defines a model for 3D plane segmentation using additional
    * angular constraints. The plane must be parallel to a user-specified axis within a user-specified angle threshold.
    * \author Radu Bogdan Rusu, Nico Blodow
    */
  template <typename PointT>
  class SampleConsensusModelParallelPlane : public SampleConsensusModelPlane<PointT>
  {
    public:
      typedef typename SampleConsensusModelPlane<PointT>::PointCloud PointCloud;
      typedef typename SampleConsensusModelPlane<PointT>::PointCloudPtr PointCloudPtr;
      typedef typename SampleConsensusModelPlane<PointT>::PointCloudConstPtr PointCloudConstPtr;

      typedef boost::shared_ptr<SampleConsensusModelParallelPlane> Ptr;

      /** \brief Constructor for base SampleConsensusModelParallelPlane.
        * \param cloud the input point cloud dataset
        */
      SampleConsensusModelParallelPlane (const PointCloudConstPtr &cloud) : SampleConsensusModelPlane<PointT> (cloud),
                                                                            eps_angle_ (0.0)
      {
        axis_.setZero ();
      }

      /** \brief Constructor for base SampleConsensusModelParallelPlane.
        * \param cloud the input point cloud dataset
        * \param indices a vector of point indices to be used from \a cloud
        */
      SampleConsensusModelParallelPlane (const PointCloudConstPtr &cloud, const std::vector<int> &indices) : SampleConsensusModelPlane<PointT> (cloud, indices),
                                                                                                             eps_angle_ (0.0)
      {
        axis_.setZero ();
      }

      /** \brief Set the axis along which we need to search for a plane perpendicular to.
        * \param ax the axis along which we need to search for a plane perpendicular to
        */
      inline void setAxis (const Eigen::Vector3f &ax) { axis_ = ax; }

      /** \brief Get the axis along which we need to search for a plane perpendicular to. */
      inline Eigen::Vector3f getAxis ()  { return (axis_); }

      /** \brief Set the angle epsilon (delta) threshold.
        * \param ea the maximum allowed difference between the plane normal and the given axis.
        */
      inline void setEpsAngle (double ea) { eps_angle_ = ea; }

      /** \brief Get the angle epsilon (delta) threshold. */
      inline double getEpsAngle () { return (eps_angle_); }

      /** \brief Select all the points which respect the given model coefficients as inliers.
        * \param model_coefficients the coefficients of a plane model that we need to compute distances to
        * \param inliers the resultant model inliers
        * \param threshold a maximum admissible distance threshold for determining the inliers from the outliers
        */
      void selectWithinDistance (const Eigen::VectorXf &model_coefficients, double threshold, std::vector<int> &inliers);

      /** \brief Compute all distances from the cloud data to a given plane model.
        * \param model_coefficients the coefficients of a plane model that we need to compute distances to
        * \param distances the resultant estimated distances
        */
      void getDistancesToModel (const Eigen::VectorXf &model_coefficients, std::vector<double> &distances);

      /** \brief Return an unique id for this model (SACMODEL_PARALLEL_PLANE). */
      virtual int getModelType () { return (SACMODEL_PARALLEL_PLANE); }

    protected:
      /** \brief Check whether a model is valid given the user constraints.
        * \param model_coefficients the set of model coefficients
        */
      bool isModelValid (const Eigen::VectorXf &model_coefficients);

      /** \brief The axis along which we need to search for a plane perpendicular to. */
      Eigen::Vector3f axis_;

      /** \brief The maximum allowed difference between the plane normal and the given axis. */
      double eps_angle_;
  };
}

#endif  //#ifndef PCL_SAMPLE_CONSENSUS_MODEL_PARALLELPLANE_H_
