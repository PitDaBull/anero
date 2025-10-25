// Copyright (c) 2025, The Anero Project
//
// All rights reserved.
// Redistribution and use in source and binary forms...

#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <boost/uuid/uuid.hpp>

#define CRYPTONOTE_NAME                              "anero"

// Money unit (1e12)
#define CRYPTONOTE_DISPLAY_DECIMAL_POINT             12

namespace config
{
  // === Anero Mainnet ===
  uint64_t const CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX = 57; // 'A'
  uint64_t const CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX = 58;
  uint64_t const CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX = 59;

  // *** UPDATED PORTS ***
  uint16_t const P2P_DEFAULT_PORT = 54374;
  uint16_t const RPC_DEFAULT_PORT = 61323;

  boost::uuids::uuid const NETWORK_ID = { {
      0x41, 0x6e, 0x65, 0x72, 0x6f, 0x4d, 0x61, 0x69,
      0x6e, 0x4e, 0x65, 0x74, 0x05, 0x23, 0x45, 0x67
  } };

  // Placeholder Genesis TX
  std::string const GENESIS_TX = "0100008080c441808092a0d783...";
  uint32_t const GENESIS_NONCE = 10000;

  namespace testnet
  {
    // === Anero Testnet ===
    uint64_t const CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX = 157;
    uint64_t const CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX = 158;
    uint64_t const CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX = 159;

    // *** UPDATED TESTNET PORTS ***
    uint16_t const P2P_DEFAULT_PORT = 55374;
    uint16_t const RPC_DEFAULT_PORT = 62323;

    boost::uuids::uuid const NETWORK_ID = { {
        0x41, 0x6e, 0x65, 0x72, 0x6f, 0x54, 0x65, 0x73,
        0x74, 0x4e, 0x65, 0x74, 0x05, 0x23, 0x45, 0x67
    } };

    std::string const GENESIS_TX = "0100008080c441808092a0d783...";
    uint32_t const GENESIS_NONCE = 10001;
  }
}

namespace cryptonote
{
  enum network_type : uint8_t
  {
    MAINNET = 0,
    TESTNET,
    FAKECHAIN,
    UNDEFINED = 255
  };

  struct config_t
  {
    uint64_t const CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX;
    uint64_t const CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX;
    uint64_t const CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX;
    uint16_t const P2P_DEFAULT_PORT;
    uint16_t const RPC_DEFAULT_PORT;
    boost::uuids::uuid const NETWORK_ID;
    std::string const GENESIS_TX;
    uint32_t const GENESIS_NONCE;
  };

  inline const config_t& get_config(network_type nettype)
  {
    static const config_t mainnet = {
      ::config::CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX,
      ::config::CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX,
      ::config::CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX,
      ::config::P2P_DEFAULT_PORT,
      ::config::RPC_DEFAULT_PORT,
      ::config::NETWORK_ID,
      ::config::GENESIS_TX,
      ::config::GENESIS_NONCE
    };

    static const config_t testnet = {
      ::config::testnet::CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX,
      ::config::testnet::CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX,
      ::config::testnet::CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX,
      ::config::testnet::P2P_DEFAULT_PORT,
      ::config::testnet::RPC_DEFAULT_PORT,
      ::config::testnet::NETWORK_ID,
      ::config::testnet::GENESIS_TX,
      ::config::testnet::GENESIS_NONCE
    };

    switch (nettype)
    {
      case MAINNET: return mainnet;
      case TESTNET: return testnet;
      case FAKECHAIN: return mainnet;
      default: throw std::runtime_error("Invalid network type");
    }
  };
}
