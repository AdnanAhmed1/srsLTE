/*
 * Copyright 2013-2019 Software Radio Systems Limited
 *
 * This file is part of srsLTE.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#ifndef SRSLTE_RRC_ASN1_UTILS_H
#define SRSLTE_RRC_ASN1_UTILS_H

#include <string>

// fwd decls
namespace asn1 {
namespace rrc {

struct plmn_id_s;
struct s_tmsi_s;
struct rlc_cfg_c;

} // namespace rrc
} // namespace asn1

namespace srslte {

bool plmn_is_valid(const asn1::rrc::plmn_id_s& asn1_type);

struct plmn_id_t {
  uint8_t mcc[3];
  uint8_t mnc[3];
  uint8_t nof_mnc_digits;

  plmn_id_t() : mcc(), mnc(), nof_mnc_digits(2) {}
  explicit plmn_id_t(const asn1::rrc::plmn_id_s& asn1_type);
  void        reset();
  int         from_asn1(const asn1::rrc::plmn_id_s& asn1_type);
  int         to_asn1(asn1::rrc::plmn_id_s* asn1_type) const;
  int         from_number(uint16_t mcc_num, uint16_t mnc_num);
  int         from_string(const std::string& plmn_str);
  std::string to_string() const;
  bool        operator==(const plmn_id_t& other);
};

struct s_tmsi_t {
  uint8_t  mmec   = 0;
  uint32_t m_tmsi = 0;

  s_tmsi_t() = default;
  explicit s_tmsi_t(const asn1::rrc::s_tmsi_s& asn1_type);
  void from_asn1(const asn1::rrc::s_tmsi_s& asn1_type);
  void to_asn1(asn1::rrc::s_tmsi_s* asn1_type) const;
};

enum class establishment_cause_t {
  emergency,
  high_prio_access,
  mt_access,
  mo_sig,
  mo_data,
  delay_tolerant_access_v1020,
  mo_voice_call_v1280,
  spare1,
  nulltype
};
std::string to_string(const establishment_cause_t& cause);

class srslte_rlc_config_t;
void convert_from_asn1(srslte_rlc_config_t* out, const asn1::rrc::rlc_cfg_c& asn1_type);
}

#endif // SRSLTE_RRC_ASN1_UTILS_H