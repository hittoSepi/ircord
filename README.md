# ircord CLI

Command-line management tool for IRCord server. Controls a running server via the admin socket.

## Features

- **Fire-and-forget commands** — status, users, shutdown, restart, kick, ban, update
- **Streaming commands** — logtail for real-time log viewing
- **Interactive mode** — launch TUI for full admin interface
- **Extensible** — Phase 4 will add QuickJS script commands

## Usage

```bash
# Show help
ircord help

# Show server status
ircord status

# List online users
ircord users

# Kick/ban users
ircord kick <username> [reason]
ircord ban <username> [reason]

# Stream logs in real-time
ircord logtail
ircord logtail --level error    # filter by level

# Shut down or restart server
ircord shutdown
ircord restart

# Update server (server-side)
ircord update

# Launch interactive TUI
ircord tui

# Custom socket path
ircord --socket /path/to/socket status
```

## Building

### Windows

```powershell
cmake -S ircord -B build/ircord `
  -DCMAKE_BUILD_TYPE=Release `
  -DCMAKE_PREFIX_PATH="ircord-client/vcpkg_installed/x64-windows/share"
  
cmake --build build/ircord --config Release
```

### Linux

```bash
cmake -S ircord -B build/ircord -DCMAKE_BUILD_TYPE=Release
cmake --build build/ircord
```

## Exit Codes

| Code | Meaning |
|------|---------|
| 0 | Success |
| 1 | Command error (unknown command, invalid args, server error) |
| 2 | Connection error (server not running) |

## Admin Socket

The CLI connects to the server's admin socket:

- **Windows**: `\\.\pipe\ircord-admin`
- **Linux**: `$XDG_RUNTIME_DIR/ircord-admin.sock` or `/tmp/ircord-admin.sock`

Use `--socket <path>` to override.

## Architecture

```
┌──────────────┐      admin socket      ┌──────────────┐
│  ircord CLI  │  ◄──────────────────►  │ ircord-server │
│              │    JSON protocol       │               │
│  - status    │   (named pipe /        │  AdminSocket  │
│  - kick/ban  │    unix socket)        │  Listener     │
│  - logtail   │                        │               │
│  - tui       │                        │  handle_admin │
└──────────────┘                        └──────────────┘
```

## Dependencies

| Dependency | Source | Purpose |
|------------|--------|---------|
| ircord-server-tui | `../ircord-server-tui` | AdminSocketClient, protocol |
| nlohmann/json | vcpkg / FetchContent | JSON |
| Boost.Asio | vcpkg | Async I/O |
| spdlog | vcpkg | Logging (via ircord-server-tui) |

## License

Same as [ircord-server](https://github.com/hittoSepi/ircord-server).
