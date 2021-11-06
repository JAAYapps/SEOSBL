gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\efimain.c -o efimain.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\UEFI_API\EFIStatus.c -o EFIStatus.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\UEFI_API\EFIProtocols.c -o EFIProtocols.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\UEFI_API\EFIMemory.c -o EFIMemory.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\EFICommon.c -o EFICommon.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\EFIKeyBoardInput.c -o EFIKeyBoardInput.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\EFIScreenOut.c -o EFIScreenOut.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\EFIGraphics.c -o EFIGraphics.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\Interval.c -o Interval.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\EFIPower.c -o EFIPower.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\EFIFS.c -o EFIFS.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\text.c -o text.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\Graphics.c -o Graphics.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\memory.c -o memory.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\String.c -o String.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\Date.c -o Date.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\GDT.c -o GDT.o
gcc -Wall -Werror -m64 -mabi=ms efimain.o EFIMemory.o EFICommon.o EFIProtocols.o EFIStatus.o EFIKeyBoardInput.o EFIScreenOut.o EFIGraphics.o Interval.o EFIPower.o EFIFS.o Graphics.o text.o memory.o String.o Date.o GDT.o -nostdlib -shared -Wl,-dll -Wl,--subsystem,10 -e efi_main -o BOOTX64.EFI

del *.o

gcc -m64 -mabi=ms -Wl,--oformat=binary -c loadertest\loader.c -e main -o loader.bin
gcc -fPIC -O0 -Wall -Werror -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes -Wunsafe-loop-optimizations -fno-builtin -fno-stack-protector -std=c17 -nostdinc -nostdlib -ffreestanding -Wno-unused-variable -m64 -mabi=ms -Wl,--oformat=binary -e main -c SomeBootloader\loader\loader.c -e main -o loader2.bin

pause
