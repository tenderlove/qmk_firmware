# Tenderlove's layout

It's the Norman layout, but targeted for programming / Vim / web browsing.

## Building for Infinity

These are just notes to remind myself how to build the firmware:

Install on the left side

```
$ pwd
/Users/aaron/git/qmk_firmware/keyboards/ergodox
$ make infinity-tenderlove
$ make infinity-tenderlove-dfu-util # This won't work, but you need the file it generates
$ dfu-util -D ../../.build/ergodox_infinity_tenderlove.bin -d 1c11:b007
```

Install on the right side

```
$ make infinity-tenderlove MASTER=right
$ make infinity-tenderlove-dfu-util MASTER=right
$ dfu-util -D ../../.build/ergodox_infinity_tenderlove.bin -d 1c11:b007
```

Plug Right side in to the computer, plug the left side in to the right side
