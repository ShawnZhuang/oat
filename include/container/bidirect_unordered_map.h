#ifndef OAT_UNORDERED_BI_MAP_H
#define OAT_UNORDERED_BI_MAP_H

#include <unordered_map>
#include <stdexcept>

namespace oat {

template <typename Key, typename Value, typename KeyHash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>,
          typename ValueHash = std::hash<Value>,
          typename ValueEqual = std::equal_to<Value>>
class bidirect_unordered_map {
 public:
  bool insert(const Key& key, const Value& value) {
    if (key_to_value.find(key) != key_to_value.end() ||
        value_to_key.find(value) != value_to_key.end()) {
      return false;
    }
    key_to_value[key] = value;
    value_to_key[value] = key;
    return true;
  }

  bool erase_by_key(const Key& key) {
    auto it = key_to_value.find(key);
    if (it == key_to_value.end()) {
      return false;
    }
    value_to_key.erase(it->second);
    key_to_value.erase(it);
    return true;
  }

  bool erase_by_value(const Value& value) {
    auto it = value_to_key.find(value);
    if (it == value_to_key.end()) {
      return false;
    }
    key_to_value.erase(it->second);
    value_to_key.erase(it);
    return true;
  }

  Value get_value(const Key& key) const {
    auto it = key_to_value.find(key);
    if (it == key_to_value.end()) {
      throw std::out_of_range("Key not found");
    }
    return it->second;
  }

  Key get_key(const Value& value) const {
    auto it = value_to_key.find(value);
    if (it == value_to_key.end()) {
      throw std::out_of_range("Value not found");
    }
    return it->second;
  }

  bool contains_key(const Key& key) const {
    return key_to_value.find(key) != key_to_value.end();
  }

  bool contains_value(const Value& value) const {
    return value_to_key.find(value) != value_to_key.end();
  }

 private:
  std::unordered_map<Key, Value, KeyHash, KeyEqual> key_to_value;
  std::unordered_map<Value, Key, ValueHash, ValueEqual> value_to_key;
};

}  // namespace oat

#endif  // OAT_UNORDERED_BI_MAP_H