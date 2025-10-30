# Anero Forking, Development and Launching Guide for Creating New Cryptonote Blockchains

### This guide instructs the reader on how to go about forking The Anero Project (Anero's source code), re-writing the codebase to reflect a new Cryptonote Coin,
and finally how to launch the newly created blockchain with or without a set PREMINE amount.

## Gather Required Materials:
We are going to need some digital/physical materials for this project.
1a.) Gather 3 laptop computers running Linux Mint or another Linux distro that supports apt-get commands.
1b.) If you cannot gather 3 laptops, you will need atleast 1, then you will need to signup with Amazon AWS and create 2 instances of Debian Linux and ensure the
available RAM for each instance is atleast 4GB and the storage/ROM for each instance is atleast 100GB.

## System Preparation
Begin by updating your system to ensure all packages are current:
```bash
sudo apt update
sudo apt upgrade -y
```

## Installing Dependencies
Your physical laptop will be where we store the source code, develop the codebase and handle other admin actions for your new coin. We will need these dependencies
to ensure proper development and binary compilation:
```bash
sudo apt install git miniupnpc build-essential cmake pkg-config libboost-all-dev libssl-dev libzmq3-dev libunbound-dev libsodium-dev libunwind8-dev liblzma-dev libreadline6-dev 
libldns-dev libexpat1-dev doxygen graphviz libpgm-dev qttools5-dev-tools libhidapi-dev libusb-1.0-0-dev libprotobuf-dev protobuf-compiler libudev-dev
```
## Obtaining Anero Source Code
To get started developing our own Cryptonote Coin we must obtain the latest release of The Anero Project's source code, you can use the direct link below or navigate
to the Anero Github Repo:
[Anero Source Code Direct Download Link](https://github.com/anero-project/anero/archive/refs/heads/master.zip)

# Developing the Codebase to Represent Your New Coin
Now we will start to make the necessary modifications to The Anero Project's source code to match the variables of your new coin:

## Step 1.) Edit /anero-master/src/cryptonote_config.h using your favorite text editor program, and you will be making the following changes to this file:

Find the line reading - define MONEY_SUPPLY ((uint64_t)10000000000ULL * COIN) and edit this amount to represent the total supply of your new coin. If you copy and
paste this line into gemini.google.com and tell it "rewrite this line of code to represent 1,000,000 coins" and it will give you the correct number to edit this value to.

AND

Find the line reading - define CRYPTONOTE_NAME "anero" and change anero to the name of your new coin.

AND

Find the line reading - define PREMINE_AMOUNT (100000000ULL * COIN) and remove this line as it is deprecated and no longer needed to define your PREMINE
(View "PREMINE Configuration" section of this guide for instructions on how to set a premine to your wallet).

AND

The following lines all need to be updated the first 3 need new Base58 Prefixes representing your new coin, the second 3 are the ports for P2P, RPC and ZMQ (Not
Required), these ports can be randomized but must not exceed 65000. The next section is for your seed nodes you can edit all 3 to 0.0.0.0:3030 temporarily until we make
our seed nodes, the next section is the Network ID, if you go to gemini.google.com and for example paste the original uuid from the cryptonote_config.h file, ask gemini
to rewrite the following uuid to represent the (yournewcoin) network. Then lastly is the Genesis TX section, simply delete the current tx number from inside the
parenthesis (leave the parenthesis only) and we will generate the Genesis TX later in this guide.

NOTE: Stagenet & Testnet sections can be ignored for now.

## Step 2.) Edit /anero-master/src/version.cpp.in and replace these 2 values below with your new coin's parameters:

define DEF_ANERO_VERSION "0.1.0.0"  -  Update 0.1.0.0 to your version number.
define DEF_ANERO_RELEASE_NAME "Fluorintine Vermi"  -  Update Flourintine Vermi to your desired version name.

## Step 3.) To be continued.
