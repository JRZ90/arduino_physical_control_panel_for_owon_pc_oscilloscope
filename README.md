This is a physical control panel for owon pc oscilloscopes, but can be used with any other brand and codel. The working principle is very simple, the software has some keyboard shortcuts for control some actions such the amplitude and time scale. When you press a button or turn the knob the arduino send a signal to python and this is who send a keystroke to the oscilloscope software emulating the keyboard.

## Requirements
### Hardware
* Arduino board with USB connection, any Arduino compatible board with CH340 chip work just fine, no HID capabilities required.
* One of the pcbs for mount the components and the arduino.

### Environment
* Windows
* Python 3
* Arduino

* The PCB (ver_mini) can be easily done  with the toner transfer mnethod. But the extended version is much more complex and was designed to be done by a pcb manufacturer such as JLCPCB or PCBWAY.
* All the components are very inexpensive and easy to find. Each PCB has a Bom file with all the required components.
