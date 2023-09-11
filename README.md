# mod-memset

This is a small test tool to verify a CPU scheduling bug on the MOD Dwarf.

By simply allocating a big pool of memory and non-stop calling `memset(mem, 0, size)` we can generate audio xruns.  
The same bug is also seen by running `cyclictest -S -p 80` and then starting this tool.  
It does not matter that `cycletest` is running with elevated/realtime privileges like `SCHED_FIFO`, or the priority of this tool, **there are always xruns and CPU scheduling issues regardless of priority levels**.

In order to have better control over the `memset` call, we copied it from the glibc repository in here, allowing us to tweak what it does and its optimization level too.

## Building

Project uses a simple regular Makefile, cross-compiling for Dwarf is as easy as:

```sh
make CC=aarch64-linux-gnu-gcc
```
