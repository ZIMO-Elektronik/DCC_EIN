#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ulf/dcc_ein.hpp>

using namespace std::literals;

TEST(addressed_datagram2sendbidi_str, basic_loco_address) {
  ulf::dcc_ein::AddressedDatagram addressed_datagram{
    .addr = {.value = 3u, .type = dcc::Address::BasicLoco},
    .datagram = {0xF4u, 0x58u, 0x81u, 0x3Bu, 0xC4u, 0x79u, 0xF5u, 0xDFu}};

  EXPECT_TRUE(std::ranges::equal(
    ulf::dcc_ein::addressed_datagram2sendbidi_str(addressed_datagram),
    "sendbidi s0003 f4 58 81 3b c4 79 f5 df\r"sv));

  addressed_datagram.addr = {.value = 42u, .type = dcc::Address::BasicLoco};
  EXPECT_TRUE(std::ranges::equal(
    ulf::dcc_ein::addressed_datagram2sendbidi_str(addressed_datagram),
    "sendbidi s002a f4 58 81 3b c4 79 f5 df\r"sv));
}

TEST(addressed_datagram2sendbidi_str, extended_loco_address) {
  ulf::dcc_ein::AddressedDatagram addressed_datagram{
    .addr = {.value = 4217u, .type = dcc::Address::ExtendedLoco},
    .datagram = {0xF4u, 0x58u, 0x81u, 0x3Bu, 0xC4u, 0x79u}};
  EXPECT_TRUE(std::ranges::equal(
    ulf::dcc_ein::addressed_datagram2sendbidi_str(addressed_datagram),
    "sendbidi l1079 f4 58 81 3b c4 79 00 00\r"sv));
}

TEST(addressed_datagram2sendbidi_str, basic_accessory_address) {
  ulf::dcc_ein::AddressedDatagram addressed_datagram{
    .addr = {.value = 271u, .type = dcc::Address::BasicAccessory},
    .datagram = {0xF4u, 0x58u}};
  EXPECT_TRUE(std::ranges::equal(
    ulf::dcc_ein::addressed_datagram2sendbidi_str(addressed_datagram),
    "sendbidi a010f f4 58 00 00 00 00 00 00\r"sv));
}

TEST(addressed_datagram2sendbidi_str, extended_accessory_address) {
  ulf::dcc_ein::AddressedDatagram addressed_datagram{
    .addr = {.value = 271u, .type = dcc::Address::ExtendedAccessory},
    .datagram = {0xF4u, 0x58u}};
  EXPECT_TRUE(std::ranges::equal(
    ulf::dcc_ein::addressed_datagram2sendbidi_str(addressed_datagram),
    "sendbidi x010f f4 58 00 00 00 00 00 00\r"sv));
}
