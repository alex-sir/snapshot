# Snapshot

Generate a "snapshot" tarball of a running program for debugging.

## How To Use

``` bash
./snapshot [OPTIONS] ARCHIVE
```

## Options

* d: Run in debug mode
* ?: Display a help message

## Notes

Snapshot expects the core dump file it generates to be located in the directory where **snapshot()** is called. Depending on your system configuration settings, the core dump might be generated elsewhere.

**NOTICE: Snapshot will NOT work as expected if the core dump is not generated in the directory where snapshot() is called**.

Check the core dump configuration settings on your system with:

``` bash
cat /proc/sys/kernel/core_pattern
```

If the output is not ```core```, you can set your system to generate the core dump in the current directory with:

``` bash
sudo sysctl -w kernel.core_pattern=core
```
