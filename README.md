# SysPerc

A collection of **Linux** commands for displaying system information as percentages, provided by a **Polymorphic Executable** written in C (inspired by BusyBox), for status bars and scripts.

## How It Works

The main executable `sysperc` determines which module to run based on the name it is invoked with (`cpup`, `memp`, etc.). Each module is responsible for gathering specific system information and calculating the usage percentage.

## Commands

| Command          | Description                                                                | Argument                       |
| ---------------- | -------------------------------------------------------------------------- | ------------------------------ |
| `cpup -rch`      | Get overall CPU usage percentage, the current run uses previous run stats. |                                |
| `memp -rch`      | Get memory usage as a percentage.                                          |                                |
| `dskp -rch /`    | Get disk usage as a percentage.                                            | Disk path (default: `/`)       |
| `batp -rch BAT0` | Get battery usage as a percentage.                                         | Battery name (default: `BAT0`) |

## Common Command Options

| Option | Description                                   |
| ------ | --------------------------------------------- |
| `-r`   | Round the usage percentage                    |
| `-c`   | Output a raw number without a percentage sign |
| `-h`   | Display help message                     |

## Dependencies

- `gcc` is used for compilation.
- `clang-format` is used for formatting.

## Install

The executable will be built with `gcc`, and the commands will be symlinked to `/usr/local/bin`.

```
sudo make install
```

## Make Targets

| Target      | Description                                        |
| ----------- | -------------------------------------------------- |
| `build`     | Compile the sysperc binary with all the modules    |
| `clean`     | Remove compiled object files                       |
| `format`    | Format all C/H files using clang-format            |
| `install`   | Install symlinks to /usr/local/bin (requires sudo) |
| `uninstall` | Remove symlinks and binary                         |
