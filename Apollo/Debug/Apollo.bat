SET CURRENTDIR="%cd%"

"D:\Programas\Arduino\hardware\tools\avr\bin\avrdude.exe" -C "D:\Programas\Arduino\hardware\tools\avr\etc\avrdude.conf" -v -patmega328p -cwiring -PCOM1 -b115200 -D -U flash:w:"Apollo.hex":i

pause