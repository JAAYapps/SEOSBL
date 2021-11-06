OSFMount -a -t file -f drive\drive.hdd -s 40M -o rw -m Z:

move /y BOOTX64.EFI "Z:\EFI\Boot\"
copy /y mytextfile.txt "Z:\"
move /y loader.bin "Z:\"
move /y loader2.bin "Z:\SEOSBL\loader.bin"

timeout 3

OSFMount -D -m Z:

pause

