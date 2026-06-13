# Simple TUI Text Editor

A minimalist terminal-based text editor written in C, using raw `termios` control and custom buffer management.

## Features

- Raw terminal mode (no line buffering, no echo)
- Insert/delete characters with real-time display
- Save file with `Ctrl+X`
- Quit with `q`
- Arrow key navigation (basic)
- Backspace deletion
- Enter key for new lines
- Persistent buffer (continuous memory layout)

## Key Bindings

| Key           | Action           |
|---------------|------------------|
| `q`           | Quit editor      |
| `Ctrl+X`      | Save file        |
| `Backspace`   | Delete character |
| `Enter`       | New line         |
| `↑/↓/←/→`     | Move cursor      |
| Printable chars | Insert text    |

## Requirements

- Linux / Unix-like OS
- GCC or any C compiler
- Standard POSIX libraries (termios, unistd, fcntl)

## Build & Run

```bash
make
./editor <filename>
