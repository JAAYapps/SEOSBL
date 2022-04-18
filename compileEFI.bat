gcc -Wall -Werror -masm=intel -m64 -mabi=ms -pedantic -ffreestanding -DPRINT -Dexternal -c src\efimain.c -o efimain.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\UEFI_API\EFIStatus.c -o EFIStatus.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\UEFI_API\EFIProtocols.c -o EFIProtocols.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\UEFI_API\EFIMemory.c -o EFIMemory.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\EFI_LIBS\EFICommon.c -o EFICommon.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\EFI_LIBS\EFIKeyBoardInput.c -o EFIKeyBoardInput.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\EFI_LIBS\EFIScreenOut.c -o EFIScreenOut.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\EFI_LIBS\EFIGraphics.c -o EFIGraphics.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\EFI_LIBS\Interval.c -o Interval.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\EFI_LIBS\EFIPower.c -o EFIPower.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\EFI_LIBS\EFIFS.c -o EFIFS.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -Dexternal -c SimpleJSONtoC\JSON.c -o JSON.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\Graphics.c -o Graphics.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c Common-Code-For-C-Projects\memory.c -o memory.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\String.c -o String.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\Date.c -o Date.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\GDT.c -o GDT.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\tosdfont.c -o tosdfont.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms -ffreestanding -c src\SEOSBLMemory.c -o SEOSBLMemory.o
gcc -Wall -Werror -masm=intel -m64 -mabi=ms efimain.o EFIMemory.o EFICommon.o EFIProtocols.o EFIStatus.o EFIKeyBoardInput.o EFIScreenOut.o EFIGraphics.o Interval.o EFIPower.o EFIFS.o JSON.o Graphics.o memory.o SEOSBLMemory.o String.o Date.o tosdfont.o GDT.o -nostdlib -shared -Wl,-dll -Wl,--subsystem,10 -e efi_main -o BOOTX64.EFI

del *.o

gcc -fPIC -O0 -Wall -Werror -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes -Wunsafe-loop-optimizations -fno-builtin -fno-stack-protector -std=c17 -nostdinc -nostdlib -ffreestanding -Wno-unused-variable -m64 -mabi=ms -Wl,--oformat=binary -c src\loader\loader.c -e main -o loader.bin

pause
