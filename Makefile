process_injector: process_injector.c
	gcc process_injector.c -o process_injector

target: target.c
	gcc target.c -o target

all: process_injector target

clean:
	rm ./process_injector ./target
