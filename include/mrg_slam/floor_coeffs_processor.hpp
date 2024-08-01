// SPDX-License-Identifier: BSD-2-Clause

#ifndef FLOOR_COEFFS_PROCESSOR_HPP
#define FLOOR_COEFFS_PROCESSOR_HPP

#include <deque>
#include <mutex>
// mrg_slam
#include <mrg_slam/graph_database.hpp>
#include <mrg_slam/graph_slam.hpp>
#include <mrg_slam/keyframe.hpp>
#include <mrg_slam/ros_time_hash.hpp>
// ROS2
#include <builtin_interfaces/msg/time.hpp>
#include <mrg_slam_msgs/msg/floor_coeffs.hpp>
#include <rclcpp/rclcpp.hpp>

namespace mrg_slam {

class FloorCoeffsProcessor {
public:
    FloorCoeffsProcessor() {}

    void onInit( rclcpp::Node::SharedPtr _node );

    void floor_coeffs_callback( mrg_slam_msgs::msg::FloorCoeffs::ConstSharedPtr floor_coeffs_msg );

    bool flush( std::shared_ptr<GraphSLAM> &graph_slam, const std::vector<KeyFrame::Ptr> &keyframes,
                const std::unordered_map<builtin_interfaces::msg::Time, KeyFrame::Ptr, RosTimeHash> &keyframe_hash,
                const builtin_interfaces::msg::Time                                                 &latest_keyframe_stamp );

    bool flush( std::shared_ptr<GraphDatabase> graph_db, std::shared_ptr<GraphSLAM> &graph_slam );

    const g2o::VertexPlane *floor_plane_node() const { return floor_plane_node_ptr; }

private:
    rclcpp::Subscription<mrg_slam_msgs::msg::FloorCoeffs>::SharedPtr floor_sub;

    double                                                      floor_edge_stddev;
    std::string                                                 floor_edge_robust_kernel;
    double                                                      floor_edge_robust_kernel_size;
    std::mutex                                                  floor_coeffs_queue_mutex;
    std::deque<mrg_slam_msgs::msg::FloorCoeffs::ConstSharedPtr> floor_coeffs_queue;

    g2o::VertexPlane *floor_plane_node_ptr;
};

}  // namespace mrg_slam

#endif  // FLOOR_COEFFS_PROCESSOR_HPP