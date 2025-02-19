#ifndef CONTAINER_FIXED_PIORITY_MAP_H
#define CONTAINER_FIXED_PIORITY_MAP_H
#include <unordered_map>
#include <vector>
#include <utility>
#include <cstddef>

namespace container {
template <typename K, typename V, typename KeyHash, typename KeyEqual,
          typename ValueLess>
class fixed_piority_map {
 private:
  using Element = std::pair<K, V>;
  size_t capacity_;
  std::unordered_map<K, V, KeyHash, KeyEqual> umap_;
  std::vector<Element> piority_vec;

 public:
  fixed_piority_map(/* args */) {}
  fixed_piority_map(size_t capacity) : capacity_(capacity) {}
  bool insert(const K& key, const V& value) {
    ValueLess(,value)
  }
  ~fixed_piority_map() {}

 private:
  void binary_insert(const Element& element) {
    size_t left = 0;
    size_t right = piority_vec.size();
    while (left < right) {
      size_t mid = left + (right - left) / 2;
      if (ValueLess()(element.second, piority_vec[mid].second)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    piority_vec.insert(piority_vec.begin() + left, element);
  }
};
}  // namespace container

#endif  // CONTAINER_FIXED_PIORITY_MAP_H