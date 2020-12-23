# project - Expensometer

 My attempt at creating something of an Excel sheet for keeping track of expenses.
 Using C language and gtk+ library.

 ![](https://i.imgur.com/EQMbdXK.png)
  

 # Installation
 On Linux: Should be very straightforward, in fact should required no effort at all

 Simply run this command in your console:
    ```
    ./main
    ```

And if you wish to contribute or modify the source code by yourself 
Firstly you will need to install gtk library on your distro:
```
sudo apt install libgtk-3-dev
```
And then to compily your modification run:
```
./compile.sh
```

# How to use the Expensometer?

You finally run the expensometer for the first time. Great!
Few things that you should bare in mind.

To start adding new standings you have to add new month first
![](https://i.imgur.com/AwBojZN.png)

Add as many standings as you need
![](https://i.imgur.com/r3KlqsL.png)

In order to save every standing and month you have to at the end of typing click ENTER button.
Month should be in format mm-yyyy.

In order to change expenses formula activate desired field by clicking it with mouse and click enter in order to
show the full formula. 
For example:
60, 
ENTER,
=10+10+10+10+20,
ENTER,
60

When you been using expensometer for over a month and want to continue on with financial responsibility journey
Just hit new month and the summing of the already finished month will be done automatically

![](https://i.imgur.com/HqiEELj.png)