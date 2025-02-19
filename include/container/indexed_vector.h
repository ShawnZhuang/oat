

/**
 * @file indexed_vector.h
 * @brief Header file for the indexed_vector class.
 *
 * This file contains the definition of the indexed_vector class, which is a
 * container that maintains a vector and an index for fast lookup. The class
 * ensures that each element is unique within the container and provides
 * functionality for adding elements, retrieving elements by index, and
 * checking for the existence of elements.
 *
 * @author Shawn
 * @date 2023
 */
#ifndef OAT_INDEXED_VECTOR_H
#define OAT_INDEXED_VECTOR_H

#include <unordered_map>
#include <vector>
#include <stdexcept>
namespace contaner {
/**
 * @class indexed_vector
 * @brief A container that maintains a vector and an index for fast lookup.
 *
 * This class combines the functionality of a vector and an unordered_map to
 * provide fast lookup of elements by their value while maintaining the order
 * of insertion. It ensures that each element is unique within the container.
 *
 * @tparam T The type of elements stored in the container.
 * @tparam Hash A hash function for the type T, defaults to std::hash<T>.
 * @tparam Equals A function for comparing two elements of type T, defaults to
 * std::equal_to<T>.
 *
 * @note This class throws exceptions if duplicate elements are added or if
 *       an element is not found during lookup.
 */

template <typename T, typename Hash = std::hash<T>,
          typename Equals = std::equal_to<T>>
class indexed_vector {
 private:
  std::unordered_map<T, size_t, Hash, Equals> index_;
  std::vector<T> vec_;

 public:
  indexed_vector() {}
  indexed_vector(const std::vector<T>& others) {
    for (const auto& value : others) {
      Add(value);
    }
  }

  ~indexed_vector() {}
  size_t GetIndex(const T& key) const {
    auto it = index_.find(key);
    if (it == index_.end()) {
      throw std::runtime_error("Key not found");
    }
    return it->second;
  }
  void Add(const T& value) {
    if (index_.find(value) != index_.end()) {
      throw std::runtime_error("Value already exists");
    }
    vec_.push_back(value);
    index_[value] = vec_.size() - 1;
  }

  const T& GetValue(size_t index) const {
    if (index >= vec_.size()) {
      throw std::out_of_range("Index out of range");
    }
    return vec_[index];
  }

  size_t Size() const { return vec_.size(); }

  bool Contains(const T& value) const {
    return index_.find(value) != index_.end();
  }
};
}  // namespace contaner

#endif  // OAT_INDEXED_VECTOR_H