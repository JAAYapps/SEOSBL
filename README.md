# SEOSBL

<h2>Where the project is so far</h2> 
SEOSBL (Simple Expandable Operating System Boot Loader) is now the name of the project.

Right now if you run the bat file with gcc and OSFmount installed on windows, a BOOTX64 efi file will be generated. The main application is able to generate a JSON structure in memory if given a config file. 

I will create some instructions for setting up a boot environment in the future. I still need to structure the layout of the evnironment first.

In concept, the loader should be able to grab a "boot driver", load it into memory, and call it's main function. The loader.bin is not programmed to do that yet and I still need a way to make a working keyboard driver from any usb keyboard. I don't want to make a legacy PS2 keyboard driver.

I still need to code some other things like getting ACPI info for devices on the computer. 

<h2>What is working and not working</h2>
<ul>
  <li>So far the graphics and printf functions are working.</li>
  <li>printf and wprintf does not have any code for the format tags yet.</li>
  <li>JSON config parser is working, will need to create methods for traversal of the configuration in memory.</li>
</ul>
  
<h2>Anything else</h2>
If anyone has any suggestions, put them in the issues. 
