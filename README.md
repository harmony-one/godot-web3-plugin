<img src="/logo.png" width="25%" />

# Godot Web3 Plugin

Godot plugin for building web3 games.

Currently supported under Ubuntu 22 and MacOS Platforms.

Windows builds are still WIP

## Building

### Godot 3.5

Clone `godot` and copy sources to `modules/web3`.
In godot,  Checkout branch 3.5

```
Directory Structure:
|-- godot
|-- modules
|   |-- web3
```

Build from `godot` root.

```bash
MACOS
scons custom_modules=../modules platform=osx arch=arm64 --jobs=$(sysctl -n hw.logicalcpu)

Ubuntu 22
scons custom_modules=../modules --jobs=$(sysctl -n hw.logicalcpu)
```

### Godot 4.2
Plugin is being updated to support godot 4.2
