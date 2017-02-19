//
// Created by Kampersanda on 2017/02/05.
//

#ifndef BONSAIS_BONSAIPR_HPP
#define BONSAIS_BONSAIPR_HPP

#include "Basics.hpp"

namespace bonsais {

/*
 * Very simple implementation of m-Bonsai (recursive) described in
 * - Poyias and Raman, Improved practical compact dynamic tries, SPIRE, 2015.
 * */
class BonsaiPlus {
public:
  BonsaiPlus(uint64_t num_slots, uint64_t alp_size, uint8_t width_1st);
  ~BonsaiPlus() {}

  template<typename T>
  bool search(const T* str, uint64_t len) const {
    static_assert(Is_pod<T>(), "T is not POD.");

    uint64_t node_id = root_id_;
    for (uint64_t i = 0; i < len; ++i) {
      if (!get_child_(node_id, static_cast<uint64_t>(str[i]))) {
        return false;
      }
    }
    return get_fbit_(node_id);
  }

  template<typename T>
  bool insert(const T* str, uint64_t len) {
    static_assert(Is_pod<T>(), "T is not POD.");

    uint64_t node_id = root_id_;
    bool is_tail = false;
    for (uint64_t i = 0; i < len; ++i) {
      is_tail = add_child_(node_id, static_cast<uint64_t>(str[i]), is_tail);
    }
    if (get_fbit_(node_id)) {
      assert(!is_tail);
      return false;
    }
    set_fbit_(node_id, true);
    return true;
  }

  std::string name() const { return "BonsaiPlus"; }
  void show_stat(std::ostream& os) const;

  BonsaiPlus(const BonsaiPlus&) = delete;
  BonsaiPlus& operator=(const BonsaiPlus&) = delete;

private:
  uint64_t num_slots_{};
  uint64_t num_nodes_{};
  uint64_t alp_size_{};
  uint8_t width_1st_{};

  uint64_t root_id_{};
  uint64_t empty_mark_{};
  uint64_t max_dsp1st_{}; // maximum displacement value in 1st layer

  uint64_t prime_{};
  uint64_t multiplier_{};

  sdsl::int_vector<> slots_{}; // with quotient value, displacement value, and final bit
  std::map<uint64_t, uint32_t> aux_map_{}; // for exceeding displacement values

  HashValue hash_(uint64_t node_id, uint64_t symbol) const;

  bool get_child_(uint64_t& node_id, uint64_t symbol) const;
  bool add_child_(uint64_t& node_id, uint64_t symbol, bool is_tail = false);

  uint64_t right_(uint64_t pos) const;

  uint64_t get_quo_(uint64_t pos) const;
  uint64_t get_dsp_(uint64_t pos) const;
  bool get_fbit_(uint64_t pos) const;
  void set_fbit_(uint64_t pos, bool bit);

  void update_slot_(uint64_t pos, uint64_t quo, uint64_t dsp, bool fbit);
};

} //bonsais

#endif //BONSAIS_BONSAIPR_HPP
