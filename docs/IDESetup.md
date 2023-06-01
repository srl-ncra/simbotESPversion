# Introduction

> **Setup Arduino IDE for SIMBOT**

Install and configure the Arduino IDE for the SimBot

> After learning about the main parts of the SimBot board, we are ready to learn how to set up the Arduino IDE. Once we learn this, we will be ready to upload our program on the SimBot.

# Procedure

> In this section, we will learn in easy steps, how to set up the Arduino IDE on our computer and prepare the SimBot board to receive the program via USB cable.
> 
> **Step 1**: First you must have Simbot and a B-type USB cable.

![](media/image1.png)

# Step 2: Download Arduino IDE Software.

> You can get different versions of Arduino IDE on the Arduino Official website. <https://www.arduino.cc/en/Main/Software>.You must select your software, which is compatible with your operating system (Windows, IOS, or Linux). After your file download is complete, unzip the file.

![](media/image2.png)

# Step 3: Power up your SimBot.

> The SimBot automatically draw power from either, the USB connection to the computer or an external power supply. If you want to charge your battery then make sure you first power off the SimBot, connect the battery and then plug the USB cable.

//Image

> However, it is always recommended to first remove the battery before uploading the code. Now connect the SimBot to your computer using the USB cable. The Red power LED should glow.

# Step 4: Launch Arduino IDE.

> After your Arduino IDE software is downloaded, you need to unzip the folder. Inside the folder, you can find the application icon with an infinity label (application.exe). Double-click the icon to start the IDE.

![](media/image4.jpeg)

# Step 5: Open your first project.

> Once the software starts, you have two options −

  - Create a new project.

  - Open an existing project example.

> To create a new project, select File → **New**.

![](media/image5.jpeg)

# Step 6: Select your Arduino board.

> To avoid any error while uploading your program to the Simbot, you must select the correct board name, which matches with the Simbot board connected to your computer.

# Go to Tools → Board and select your board.

> Since we are using an Esp32 board in a Simbot, so first we have to install an Esp32 addon board on Arduino IDE.
> 
> **Esp32 Addon installation in Arduino IDE.**

# Installing ESP32 Add-on in Arduino IDE

> To install the ESP32 board in your Arduino IDE, follow these instructions:

1.  In your Arduino IDE, go to **File\> Preferences**

![](media/image6.png)

2.  Enter [**https://dl.espressif.com/dl/package\_esp32\_index.json**](https://dl.espressif.com/dl/package_esp32_index.json) into the “Additional Board Manager URLs” field as shown in the figure below. Then, click the “OK” button:

![](media/image7.png)

> **Note:** if you already have the ESP32 boards URL, you can separate the URLs with a comma as follows:
> 
> <https://dl.espressif.com/dl/package_esp32_index.json>, <http://arduino.esp8266.com/stable/package_esp8266com_index.json>

3.  Open the Boards Manager. Go to **Tools** \> **Board** \> **Boards Manager…**

![](media/image8.png)

4.  Search for **ESP32** and press install button for the “**ESP32 by Espressif Systems**“:

![](media/image9.png)

5.  That’s it. It should be installed after a few seconds.

![](media/image10.png)

# Step 7: Selecting the SimBot board

> Plug the SimBot to your computer. With your Arduino IDE open, follow these steps:

1)  Select your Board in **Tools** \> **Board** menu (in my case it’s the **DOIT ESP32 DEVKIT V1**)

![](media/image11.png)

2)  Select the Port (if you don’t see the COM Port in your Arduino IDE, you need to insta[ll the CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) from the given link:

> [https://www.silabs.com/products/development-tools/software/usb-](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) [to-uart-bridge-vcp-drivers](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)

![](media/image12.jpeg)

# Step 8: Upload the program to your Simbot.

> Before explaining how we can upload our program to the board, we must demonstrate the function of each symbol appearing in the Arduino IDE toolbar.

![](media/image13.png)

> **A** − Used to check if there is any compilation error. **B** − Used to upload a program to the Arduino board. **C** − Shortcut used to create a new sketch.
> 
> **D** − Used to directly open one of the example sketch.
> 
> **E** − Used to save your sketch.
> 
> **F** − Serial monitor used to receive serial data from the board and send the serial data to the board.
> 
> In the editing window that comes up, enter the following program, paying attention to where semi-colons appear at the end of command lines.
> 
> void setup()
> 
> {
> 
> Serial.begin(9600); Serial.println("Hello World");
> 
> }
> 
> void loop()
> 
> {}
> 
> Your window will look something like this
> 
> ![](media/image14.png)
> 
> Now, simply click the "Upload" button in the environment. Wait a few seconds; you will see the LEDs on the Simbot board, flashing. If the upload is successful, the message "Done uploading" will appear in the status bar. Click the Serial Monitor button. If all has gone well, the monitor window will show your message and look something like this

![](media/image15.png)

> Congratulations; you have created and run your first Arduino program\!
