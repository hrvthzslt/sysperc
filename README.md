# SysPerc

A collection of **Linux** commands for displaying system information as percentages, provided by a **Polymorphic Executable** written in C (inspired by BusyBox), for status bars and scripts.

## How It Works

The main executable `sysperc` determines which module to run based on the name it is invoked with (`cpup`, `memp`, etc.). Symlinks are created that point to the executable, this is how the commands are made. Each module is responsible for gathering specific system information and calculating the usage percentage.

```
/usr/local/bin/batp -> ~/sysperc/sysperc
/usr/local/bin/cpup -> ~/sysperc/sysperc
/usr/local/bin/dskp -> ~/sysperc/sysperc
/usr/local/bin/memp -> ~/sysperc/sysperc
```

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
| `-h`   | Display help message                          |

## Examples

Get your current CPU usage as a rounded percentage (no `%` sign):

```bash
cpup -rc
```

Get memory usage as fractional number with the percent sign:

```bash
memp
```

Get disk usage for your home directory, rounded:

```bash
dskp -r /home
```

Get battery usage for battery `BAT1`:

```bash
batp BAT1
```

Get CPU usage help:

```bash
cpup -h
```

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
| `format`    | Format all C and header files using clang-format   |
| `install`   | Install symlinks to /usr/local/bin (requires sudo) |
| `uninstall` | Remove symlinks and binary                         |
