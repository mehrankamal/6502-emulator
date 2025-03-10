ensure_binary_exists() {
  if [ ! -f "$1" ]; then
    echo "Binary $1 not found. Please run build.sh script first."
    exit 1
  fi
}

ensure_binary_exists "build/Debug/Applications/Emulator/6502Emulator"

./build/Debug/Applications/Emulator/6502Emulator "$@"
