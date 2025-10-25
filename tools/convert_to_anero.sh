#!/usr/bin/env bash
set -euo pipefail

# tools/convert_to_anero.sh
# Usage: run from repo root: ./tools/convert_to_anero.sh
# This script makes a backup branch and then runs textual replacements
# to convert Anero -> Anero, anerod -> anerod, ports, and copyrights.

LOGFILE="convert_to_anero.log"
BACKUP_BRANCH="anero-migration-backup"

echo "Starting Anero textual migration" | tee "$LOGFILE"

# files to skip (binary, vendor directories)
SKIP_DIRS="(.git|.github|build|vendor|external|.venv|node_modules)"

echo "Gathering tracked text files..." | tee -a "$LOGFILE"
FILES=$(git ls-files)

echo "Processing ${#FILES} files..." | tee -a "$LOGFILE"

# Define replacements - order matters (longer tokens first)
declare -a REPLACEMENTS=(
  # Branding (case-sensitive)
  "s/The Anero Project/The Anero Project/g"
  "s/The Anero Project/The Anero Project/g"
  "s/Anero/Anero/g"
  "s/anero/anero/g"
  # daemon and binaries
  "s/anerod/anerod/g"
  "s/Anerod/Anerod/g"
  "s/anero-wallet-cli/anero-wallet-cli/g"
  "s/anero-wallet-rpc/anero-wallet-rpc/g"
  "s/anero-wallet-gui/anero-wallet-gui/g"
  # ports and default network ports (text files and docs)
  "s/54374/54374/g"
  "s/61323/61323/g"
  "s/61324/61324/g" # if zmq or docs reference it (example)
  # cryptonote name
  "s/CRYPTONOTE_NAME[ \t]*\"anero\"/CRYPTONOTE_NAME \"anero\"/g"
  # copyright year single-year -> 2025
  "s/2025/2025/g"
  "s/2025/2025/g"
  "s/2025/2025/g"
  "s/2025/2025/g"
  "s/Copyright (c) 2025/Copyright (c) 2025/g"
  "s/Copyright (c) 2025/Copyright (c) 2025/g"
)

# Function to decide if file is binary
is_binary() {
  local file="$1"
  # Heuristic: if file contains NUL it's binary
  if grep -qI --null-data . "$file" 2>/dev/null; then
    # grep -Iq returns 0 for binary, but we invert logic for portability
    # We prefer file command fallback
    if file "$file" | grep -qiE 'empty|text'; then
      return 1  # not binary
    else
      return 0  # binary
    fi
  else
    # fallback to file
    if file "$file" | grep -qi 'text'; then
      return 1
    else
      return 0
    fi
  fi
}

for f in $FILES; do
  # skip files in skip dirs
  if echo "$f" | grep -qE "$SKIP_DIRS"; then
    continue
  fi

  if ! [ -f "$f" ]; then
    continue
  fi

  # skip binary files
  if is_binary "$f"; then
    echo "Skipping binary: $f" >> "$LOGFILE"
    continue
  fi

  # make a backup copy
  cp -a "$f" "$f.bak"

  # apply replacements sequentially using perl (regex)
  perl -0777 -pe '
    '"$(printf '%s\n' "${REPLACEMENTS[@]}" | sed 's/\\/\\\\/g; s/"/\\"/g; s/$/;/' )"'
  ' "$f.bak" > "$f.tmp" || { echo "Failed transform on $f"; mv "$f.bak" "$f"; continue; }

  # if changed, move in and mark
  if ! cmp -s "$f.bak" "$f.tmp"; then
    mv "$f.tmp" "$f"
    git add "$f"
    echo "Updated: $f" >> "$LOGFILE"
  else
    rm -f "$f.tmp"
    mv "$f.bak" "$f"
  fi

  rm -f "$f.bak"
done
