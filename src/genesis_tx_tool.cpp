#include "cryptonote_basic/cryptonote_format_utils.h"
#include "cryptonote_core/cryptonote_tx_utils.h"
#include "crypto/crypto.h"
#include "common/command_line.h"
#include "common/util.h"
#include "string_tools.h"
#include "device/device.hpp"
#include <iostream>
#include <cstdlib>

using namespace cryptonote;

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <Anero wallet address> <premine amount in ANR>" << std::endl;
        return 1;
    }

    std::string address_str = argv[1];
    std::string premine_str = argv[2];
    address_parse_info info;

    // Parse wallet address
    if (!get_account_address_from_str(info, cryptonote::network_type::MAINNET, address_str)) {
        std::cerr << "Invalid address format!" << std::endl;
        return 1;
    }

    // Convert premine amount from readable ANR to atomic units (10^12)
    double premine_amount = atof(premine_str.c_str());
    uint64_t block_reward = static_cast<uint64_t>(premine_amount * 1000000000000ULL); // COIN = 10^12

    std::cout << "Generating genesis transaction for " << premine_amount << " ANR ("
              << block_reward << " atomic units)" << std::endl;

    // Hardware device (default)
    hw::device &hwdev = hw::get_device("default");
    keypair txkey = keypair::generate(hwdev);

    transaction tx{};
    size_t height = 0;

    // Construct genesis miner transaction
    if (!construct_miner_tx(
            height,
            0,                    // median block weight
            0,                    // already generated coins
            0,                    // current block weight
            block_reward,         // premine reward
            info.address,         // destination address
            tx,                   // resulting transaction
            std::string(),        // extra_nonce
            1,                    // max_outs
            1                     // hard fork version
        )) {
        std::cerr << "Failed to construct genesis transaction" << std::endl;
        return 1;
    }

    // Serialize and print as hex
    std::string blob = epee::string_tools::buff_to_hex_nodelimer(t_serializable_object_to_blob(tx));
    std::cout << "\nGenesis TX Hex:\n" << blob << std::endl;

    return 0;
}
