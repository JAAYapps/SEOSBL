gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\efimain.c -o efimain.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\UEFI_API\EFIStatus.c -o EFIStatus.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\UEFI_API\EFIProtocols.c -o EFIProtocols.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\UEFI_API\EFIMemory.c -o EFIMemory.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\EFICommon.c -o EFICommon.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\EFIKeyBoardInput.c -o EFIKeyBoardInput.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\EFIScreenOut.c -o EFIScreenOut.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\Graphics.c -o Graphics.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\Interval.c -o Interval.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\EFIPower.c -o EFIPower.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\EFI_LIBS\EFIFS.c -o EFIFS.o
gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -c SomeBootloader\text.c -o text.o
gcc -Wall -Werror -m64 -mabi=ms efimain.o EFIMemory.o EFICommon.o EFIProtocols.o EFIStatus.o EFIKeyBoardInput.o EFIScreenOut.o Graphics.o Interval.o EFIPower.o EFIFS.o text.o -nostdlib -shared -Wl,-dll -Wl,--subsystem,10 -e efi_main -o BOOTX64.EFI

del *.o

gcc -m64 -mabi=ms -Wl,--oformat=binary -c kernel\kernel.c -e main -o loader.bin

pause
