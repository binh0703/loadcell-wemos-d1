@echo off

esptool.py write_flash 0x00000 .\bin\boot_v1.7.bin 0x01000 .\bin\upgrade\user1.4096.new.4.bin 0x3FB000 .\bin\blank.bin 0x3FC000 .\bin\esp_init_data_default.bin 0x3FE000 .\bin\blank.bin

pause