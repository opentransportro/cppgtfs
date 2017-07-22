// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_CONTAINER_H_
#define AD_CPPGTFS_GTFS_CONTAINER_H_

#include <string>
#include <unordered_map>

namespace ad {
namespace cppgtfs {
namespace gtfs {

template <typename T>
class Container {
 public:
  Container(){};
  ~Container();
  bool add(T* obj);
  bool remove(const std::string& id);
  const T* get(const std::string& id) const;
  T* get(const std::string& id);

  typename std::unordered_map<std::string, T*>::const_iterator begin() const;
  typename std::unordered_map<std::string, T*>::iterator begin();

  typename std::unordered_map<std::string, T*>::const_iterator end() const;
  typename std::unordered_map<std::string, T*>::iterator end();

 private:
  std::unordered_map<std::string, T*> _map;
};

#include "Container.tpp"

}  // namespace gtfs
}  // namespace cppgtfs
}  // namespace ad

#endif  // AD_CPPGTFS_GTFS_CONTAINER_H_
