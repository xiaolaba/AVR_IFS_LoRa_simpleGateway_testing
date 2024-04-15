# AVR_IFS_LoRa_simpleGateway_tseting  
LoRa SX1276 simpleGateway testing  
PCB version 2.0  
changed design for 3.3V supply rail  
![Invisiblefun.com_SX1276_board_sch.jpg](Invisiblefun.com_SX1276_board_sch.jpg)  
![OEM_base_board.JPG](OEM_base_board.JPG)  


### Disclaimer,

all those materials in presenting of this repository, either own creation or downloaded from the internet, no affiliation to the manufacturer or their designer.
hardware  
LED @ PD5, MCU pin9  
reed switch @ PB0, MCU pin12  
IO, PC3 / PC1 PC0 or ADC3 / ADC1 / ADC0  

the board and generic info.  
[https://github.com/xiaolaba/AVR_IFS_LoRa_328PB_testing?tab=readme-ov-file](https://github.com/xiaolaba/AVR_IFS_LoRa_328PB_testing)

ISP and serial port connection.
9600 baud, N81
5V supply and 3.3V to target board, a simple RED LED as voltage step down convertor.
![Invisiblefun.com_SX1276_board_pcb.jpg](Invisiblefun.com_SX1276_board_pcb.jpg)  
![Invisiblefun.com_SX1276_board_sch.jpg](Invisiblefun.com_SX1276_board_sch.jpg)  

### design/testing files  
![9600N81_test_done.JPG](9600N81_test_done.JPG)  
![burn.bat](burn.bat)  
![Frequency_A923-1.jpg](Frequency_A923-1.jpg)  
![github_link_build_filelist.bat](github_link_build_filelist.bat)  

![LoRaSimpleGateway_test.ino](LoRaSimpleGateway_test.ino)  
![LoRaSimpleGateway_test.ino_atmega328pb_1000000L.hex](LoRaSimpleGateway_test.ino_atmega328pb_1000000L.hex)  

![Terminal_ATmega328PB.bat](Terminal_ATmega328PB.bat) 
