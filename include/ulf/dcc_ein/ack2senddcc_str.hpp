// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert acknowledge to senddcc string
///
/// \file   ulf/dcc_ein/ack2senddcc_str.hpp
/// \author Vincent Hamp
/// \date   17/11/2023

#pragma once

#include <charconv>
#include <dcc/dcc.hpp>
#include <string_view>
#include "senddcc.hpp"

namespace ulf::dcc_ein {

/// Convert acknowledge to senddcc string
///
/// The returned string will have the pattern 'senddcc [a-z]([0-9a-f]{2})\r'.
/// This string is sent as acknowledge to received senddcc strings. Depending on
/// the transferred ID, the response byte has different meanings.
///
/// \param  id    'b' response byte indicates current buffer level in bytes
///               'p' response byte indicates current buffer level in packets
/// \param  byte  Response byte
/// \return senddcc string for acknowledge
constexpr std::array<char, size(senddcc_prefix) + 4uz>
ack2senddcc_str(char id, uint8_t byte) {
  // Prefix
  std::array<char, size(senddcc_prefix) + 4uz> str{};
  auto first{
    std::copy(cbegin(senddcc_prefix), cend(senddcc_prefix), data(str))};

  // ID
  *first++ = id;

  // Byte
  if (byte <= 0xFu) *first++ = '0';
  first = std::to_chars(first, end(str), byte, 16).ptr;

  *first = '\r';

  return str;
}

} // namespace ulf::dcc_ein