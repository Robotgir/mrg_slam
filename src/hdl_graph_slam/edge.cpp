// SPDX-License-Identifier: BSD-2-Clause

#include <hdl_graph_slam/edge.hpp>

#include <boost/filesystem.hpp>

#include <g2o/types/slam3d/edge_se3.h>


namespace hdl_graph_slam {

Edge::Edge(const g2o::EdgeSE3* edge, Type type) : edge(edge), type(type), gid(0), from_gid(0), to_gid(0) {
}

Edge::Edge(const g2o::EdgeSE3* edge, Type type, const GlobalIdGenerator &gid_generator) : edge(edge), type(type) {
  gid = gid_generator(id());
  from_gid = gid_generator(from_id());
  to_gid = gid_generator(to_id());
}

/*
Edge::Edge(const std::string& directory, g2o::HyperGraph* graph) {
  // TODO: implement
  // load(directory, graph);
}
*/


Edge::~Edge() {}


long Edge::id() const {
  return edge->id();
}


long Edge::from_id() const {
  return edge->vertices()[0]->id();
}


long Edge::to_id() const {
  return edge->vertices()[1]->id();
}


const Eigen::Isometry3d& Edge::relative_pose() const {
  return edge->measurement(); 
}


const Eigen::Matrix<double, 6, 6>& Edge::information() const {
  return edge->information();   
}


EdgeSnapshot::EdgeSnapshot(const Edge::Ptr& edge) : id(edge->id()), from_id(edge->from_id()), to_id(edge->to_id()), relative_pose(edge->relative_pose()), information(edge->information()) {}

}  // namespace hdl_graph_slam
