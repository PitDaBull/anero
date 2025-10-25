# --------------------------------------------------
# Anero Docker Build
# --------------------------------------------------
FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libboost-all-dev \
    libssl-dev \
    libunbound-dev \
    libunwind-dev \
    libsodium-dev \
    liblzma-dev \
    libreadline-dev \
    git && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /opt/anero

# Copy source
COPY . .

# Build daemon + CLI
RUN cmake . && make -j$(nproc)

# Non-root runtime user
RUN useradd -ms /bin/bash anero
RUN chown -R anero:anero /opt/anero
USER anero

# Persistent chain data
VOLUME /opt/anero/.anero

# --------------------------------------------------
# Ports
#
# MAINNET:
#   P2P: 54374
#   RPC: 61323
#
# TESTNET:
#   P2P: 55374
#   RPC: 62323
# --------------------------------------------------
EXPOSE 54374 61323 55374 62323

# Default daemon launch
ENTRYPOINT ["./anero-daemon"]
CMD ["--rpc-bind-ip=0.0.0.0", "--confirm-external-bind"]
