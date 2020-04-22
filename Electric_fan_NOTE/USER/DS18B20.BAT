SET PATH=D:\keil5\ARM\ARMCC\Bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\;C:\Program Files\MySQL\%MySQL Server 5.7\bin;D:\MyJava\NewJdk\bin;D:\MyJava\NewJdk\jre\bin;D:\SDK\platform-tools;D:\SDK\;D:\SDK\platform-tools;;C:\Windows\system32\config\systemprofile\AppData\Local\Microsoft\WindowsApps;C:\Program Files\MySQL\MySQL Shell 8.0\bin\
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=DS18B20
SET CPU_CLOCK=0x007A1200
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\main.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_it.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\system_stm32f10x.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\led.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\key.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\oled.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\dht11.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\pwm.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\exti.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\delay.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\sys.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\usart.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\core_cm3.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmAsm" --Via "..\obj\startup_stm32f10x_md._ia"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\misc.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_fsmc.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_gpio.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_usart.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_rcc.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_tim.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_exti.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmLink" --Via "..\OBJ\electric_fan.lnp"
"D:\keil5\ARM\ARMCC\Bin\fromelf.exe" "..\OBJ\electric_fan.axf" --i32combined --output "..\OBJ\electric_fan.hex"
