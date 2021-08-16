OSFMount -a -t file -f "vb\Name OS Later\drive.hdd" -s 40M -o rw -m Z:

mkdir "Z:\EFI\Boot\"

move /y BOOTX64.EFI "Z:\EFI\Boot\"
copy /y mytextfile.txt "Z:\"
move /y loader.bin "Z:\"

timeout 5

OSFMount -d -m Z:

pause

