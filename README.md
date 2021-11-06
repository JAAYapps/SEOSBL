# UEFI-OS-Loader-to-Name-Later

<h1>Where the project is so far</h1> 
I think the name will eventually by SEOSBL (Simple Expandable Operating System Boot Loader)

Right now if you run the bat files with gcc and OSFmount installed on windows, the image file will be opened
and the compiled efi and bin files will be copied into the image. At some point I want to use a config file with SEOSBL.
I will have to see what happens, but the config file is not a high priority. 

I still need to code some other things like getting ACPI info for devices on the computer. 

I will have to see where I will end up.

<h1>What is working and not working</h1>
* So far the graphics and printf functions are working.
* printf and wprintf does not have any code for the format tags yet.

<h1>Anything else</h1>
If anyone has any suggestions, put them in the issues. 