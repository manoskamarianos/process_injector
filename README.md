# Process injector

A simple process injector that takes the pid of the target process, a payload from a file, and the target address that
the payload well be loaded, and injects it. A simple target program is also included for demonstrations.

## Build and Installation

By running `make` the executable `process_injector` will be created. You can also run `make target` in order to create the target file.

## Usage and Testing

You can use process_injector like this:
```bash
./process_injector <target_pid> <memory_addr> <payload>
```

You can also use the included bash file (`./test_injection.sh`) that attempts to inject the payload at the .text of the process of your choosing

## Further improvement

Functionality to be added:
- .so injection

