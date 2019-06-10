# LED Control for ErgoDox EZ

LED controls for the ErgoDox EZ require some firmware changes and some libraries
to be installed on the host system.

## Keyboard Firmware Changes

To add LED controls add `teelokb_hid_protocol.c` to your keymap.  Then in
`keyboards/ergodox_ez/rules.mk` add:

```
TEELOKB_ENABLE = yes   # enable the TeeloKB Raw HID protocol

ifeq ($(strip $(TEELOKB_ENABLE)), yes)
  RAW_ENABLE = yes
  SRC += teelokb_hid_protocol.c
endif
```

## System Changes

Install `hidapi` and the `myhidapi` Ruby gem.  On MacOS:

```
$ brew install hidapi
$ gem install myhidapi
```

## Running the control program

After the firmware has been uploaded to the keyboard, and the required libraries
installed, you can control the LEDs either from the command line or from the
browser.

### Control from the Command Line

Use the `ledctl.rb` program to control the LEDs from the command line.  Run
`ruby ledctl.rb -h` to see help.

### Control from the Browser

Run `ruby server.rb` and open `http://localhost:1234` to configure your LEDs.

Have fun!
