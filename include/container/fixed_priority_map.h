#ifndef CONTAINER_FIXED_PRIORITY_MAP_H
#define CONTAINER_FIXED_PRIORITY_MAP_H
#include <unordered_map>
#include <vector>
#include <utility>
#include <cstddef>
#include <algorithm>
namespace container {
template <typename K, typename V, typename KeyHash, typename KeyEqual,
          typename ValueLess>
class fixed_priority_map {
 private:
  using Element = std::pair<K, V>;
  size_t capacity_;
  std::unordered_map<K, V, KeyHash, KeyEqual> umap_;
  using OrderVec = std::vector<Element>;
  using iterator = typename OrderVec::iterator;
  using const_iterator = typename OrderVec::const_iterator;
  std::vector<Element> priority_vec;

 public:
  fixed_priority_map(/* args */) {}
  fixed_priority_map(size_t capacity) : capacity_(capacity) {}
  bool insert(const K& key, const V& value) {
    auto it = umap_.find(key);
    if (it != umap_.end()) {
      if (!ValueLess(value, it->second)) {
        return false;
      }
      std::remove_if(priority_vec.begin(), priority_vec.end(),
                     [&key](const Element& elem) { return elem.first == key; });

    } else if (priority_vec.size() >= capacity_) {
      if (!ValueLess(value, priority_vec.back())) {
        return false;
      }
      umap_.erase(priority_vec.back().first);
      priority_vec.pop_back();
    }
    umap_[key] = value;
    binary_insert({key, value});
    return true;
  }
  size_t size() const { return priority_vec.size(); }
  bool empty() const { return priority_vec.empty(); }
  iterator begin() { return priority_vec.begin(); }
  iterator end() { return priority_vec.end(); }
  const_iterator begin() const { return priority_vec.begin(); }
  const_iterator end() const { return priority_vec.end(); }
  ~fixed_priority_map() {}

 private:
  void binary_insert(const Element& element) {
    size_t left = 0;
    size_t right = priority_vec.size();
    while (left < right) {
      size_t mid = left + (right - left) / 2;
      if (ValueLess()(element.second, priority_vec[mid].second)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    priority_vec.insert(priority_vec.begin() + left, element);
  }
};
}  // namespace container

#endif  // CONTAINER_FIXED_PRIORITY_MAP_H